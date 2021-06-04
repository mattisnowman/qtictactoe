#include "botactor.h"

#include "gamescene.h"

BotActor::BotActor(GameScene *game, int playerId,  QString name, Strategy s):
    Actor(game, name, playerId), strategy(s)
{

}

void BotActor::makeAMove()
{
    Game &g = this->game->getGame();

    Game::Boardstate move;
    Game::Boardstate player, opponent;

    if (playerId == 0)
    {
        player = g.getPlayer1();
        opponent = g.getPlayer2();
    }
    if (playerId == 1)
    {
        player = g.getPlayer2();
        opponent = g.getPlayer1();
    }

    if (strategy == quickestWin)
    {
        qDebug() << "-------------";
        qDebug().noquote() << this->name << ": using quickest way to win:";
        qDebug().noquote() << printStepsToWin(player, opponent, playerId == 1);
        qDebug() << "-------------";
        move = quickestWinOrLatestLooseMove(player, opponent);
    }
    else if (strategy == highestProbability)
    {
        qDebug() << "-------------";
        qDebug().noquote() << this->name << ": using highest probability to win:";
        qDebug().noquote() << printChanceToWin(player, opponent, playerId == 1);
        qDebug() << "-------------";
        move = highestChanceOfWinningMove(player, opponent);
    }
    else if (strategy == random)
    {
        qDebug().noquote() << this->name << ": making random move";
        move = randomMove(player, opponent);
    }


    if (playerId == 0)
    {
        this->game->getGame().makeMovePlayer1(move);
    }
    if (playerId == 1)
    {
        this->game->getGame().makeMovePlayer2(move);
    }
    this->finishedTurn();
}

QString BotActor::getNote() const
{
    return this->getName() + " is thinking.";
}

double BotActor::chanceOfWinning(const Game::Boardstate &player, const Game::Boardstate &opponent)
{
    if (Game::isWin(player))
        return 1.;
    else if (Game::isWin(opponent))
        return 0.;

    Game::Boardstate validMoves = Game::legalMoves(player, opponent);

    if (validMoves == Game::empty)
        return 0.5;

    double sumofChance = 0.;
    int numberOfLegalMoves = 0;

    for (int i=0; i<9; i++)
    {
        Game::Boardstate move = Game::Boardstate(1 << i);

        if (move & validMoves)
        {
            sumofChance += 1.-chanceOfWinning(opponent, player | move);
            numberOfLegalMoves += 1;
        }
    }
    return sumofChance / numberOfLegalMoves;
}

int BotActor::minStepsToWin(Game::Boardstate player, Game::Boardstate opponent)
{
    int bestStepstoWin = 12;
    int bestStepstoNotLoose = 0;

    Game::Boardstate validMoves = Game::legalMoves(player, opponent);

    //This is a win. No more steps to win required: return 1
    if (Game::isWin(player))
        return 1;
    //This is a loss, Return negative -1.
    if (Game::isWin(opponent))
        return -1;
    //Rate a draw as a loss but at a later point (-2) than a straightout loss.
    if (validMoves == Game::empty)
        return -2;

    // If game is not decided let players make moves recursivly until it is decided
    for (int i=0; i<9; i++)
    {
        // Generate moves by iterating over all 9 fields
        Game::Boardstate move = Game::Boardstate(1 << i);

        if (move & validMoves)
        {
            // Make the move and let the other player make a move.
            // Recursion until win or loose is reached
            // The (-) takes into account a perspective change from player to opponent
            int stepstoWin = -minStepsToWin(opponent, player | move);

            if (stepstoWin >= 0) // A win
            {
                bestStepstoWin = qMin(stepstoWin, bestStepstoWin);
            }
            else if  (stepstoWin < 0) //From here on only losses/draws
            {
                bestStepstoNotLoose = qMin(stepstoWin, bestStepstoNotLoose);
            }
        }
    }

    if (bestStepstoWin < 11)           // This means the game is winnable
        return bestStepstoWin+1;      // Return steps to finish from here + 1
    else                              // Game cannot be won
        return bestStepstoNotLoose-1; // Return - (steps until loose + 1)
}

Game::Boardstate BotActor::highestChanceOfWinningMove(const Game::Boardstate &player, const Game::Boardstate &opponent)
{
    double bestChance = -1.;
    Game::Boardstate bestMove = Game::empty;
    Game::Boardstate validMoves = Game::legalMoves(player, opponent);

    for (int i=0; i<9; i++)
    {
        Game::Boardstate move = Game::Boardstate(1 << i);

        if (move & validMoves)
        {
            double chancetoWin = 1-chanceOfWinning(opponent, player | move);
            if (chancetoWin > bestChance || bestMove == Game::empty)
            {
                bestChance = chancetoWin;
                bestMove = move;
            }
        }
    }
    return bestMove;
}

Game::Boardstate BotActor::quickestWinOrLatestLooseMove(const Game::Boardstate &player, const Game::Boardstate &opponent)
{
    int bestStepstoWin = 11;
    int bestStepstoNotLoose = 0;

    Game::Boardstate bestMove = Game::empty;
    Game::Boardstate validMoves = Game::legalMoves(player, opponent);

    for (int i=0; i<9; i++)
    {
        Game::Boardstate move = Game::Boardstate(1 << i);

        if (move & validMoves)
        {
            if (bestMove == Game::empty)
                bestMove = move;

            int stepstoWin = -minStepsToWin(opponent, player | move);
            if (stepstoWin > 0)
            {
                if (stepstoWin < bestStepstoWin)
                {
                    bestStepstoWin = stepstoWin;
                    bestMove = move;
                }
                else if (stepstoWin == bestStepstoWin && rand() % 2)
                {
                    bestStepstoWin = stepstoWin;
                    bestMove = move;
                }
            }
            else //if (stepstoWin < 0)
            {
                if (stepstoWin < bestStepstoNotLoose)
                {
                    bestStepstoNotLoose = stepstoWin;
                    if (bestStepstoWin > 10)
                        bestMove = move;
                }
                else if (stepstoWin == bestStepstoNotLoose && rand() % 2)
                {
                    bestStepstoNotLoose = stepstoWin;
                    if (bestStepstoWin > 10)
                        bestMove = move;
                }
            }
        }
    }
    return bestMove;
}

Game::Boardstate BotActor::randomMove(const Game::Boardstate &player, const Game::Boardstate &opponent)
{
    Game::Boardstate validMoves = Game::legalMoves(player, opponent);
    if (validMoves == Game::empty)
        return validMoves;
    Game::Boardstate move;
    do
    {
        move = Game::Boardstate(1 << rand() % 9);
    }
    while (!(move & validMoves));
    return move;
}


QString BotActor::printChanceToWin(const Game::Boardstate &p1, const Game::Boardstate &p2, bool swap)
{
    QString s;
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (p1 & Game::fromIndices(i,j))
                s += swap?"o":"x";
            else if (p2 & Game::fromIndices(i,j))
                s +=swap?"x":"o";
            else
            {
                double chance = chanceOfWinning(p1 | Game::fromIndices(i,j), p2);
                s += QString::number(chance);
            }
            if (j != 2)
                s += "|";
        }
        if (i != 2)
            s += "\n-+-+-\n";
    }
    return s;
}

QString BotActor::printStepsToWin(const Game::Boardstate &p1, const Game::Boardstate &p2, bool swap)
{
    QString s;
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (p1 & Game::fromIndices(i,j))
                s += swap?"o":"x";
            else if (p2 & Game::fromIndices(i,j))
                s +=swap?"x":"o";
            else
            {
                int steps = -minStepsToWin(p2, p1 | Game::fromIndices(i,j));
                s += QString::number(steps);
            }
            if (j != 2)
                s += "|";
        }
        if (i != 2)
            s += "\n-+-+-\n";
    }
    return s;
}
