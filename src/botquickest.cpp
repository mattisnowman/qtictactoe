#include "botquickest.h"

#include "gamescene.h"

BotQuickest::BotQuickest(GameScene *game, int playerId,  QString name):
    Actor(game, name, playerId)
{

}

void BotQuickest::makeAMove()
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

    qDebug().noquote() << this->name << ": using quickest way to win:";
    qDebug().noquote() << printStepsToWin(player, opponent, playerId == 1);
    qDebug() << "-------------";
    move = quickestWinOrLatestLooseMove(player, opponent);


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

QString BotQuickest::getNote() const
{
    return this->getName() + " is thinking.";
}

int BotQuickest::minStepsToWin(Game::Boardstate player, Game::Boardstate opponent)
{
    int bestStepstoWin = 20;
    int bestStepstoNotLoose = 0;

    Game::Boardstate validMoves = Game::legalMoves(player, opponent);

    //This is a win. No more steps to win required: return 1
    if (Game::isWin(player))
        return 1;
    //This is a loss, Return negative -1.
    if (Game::isWin(opponent))
        return -1;
    // Rate a draw as a loss but at a later point (-2) than a straightout loss.
    // The sign for draw will iterate between +- but it will always be the latest loss or latest win.
    // Thus it will be prefered over all losses and all wins will be prefered over it
    if (validMoves == Game::empty)
        return 2;

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

    if (bestStepstoWin < 20)          // This means the game is winnable
        return bestStepstoWin+1;      // Return steps to finish from here + 1
    else                              // Game cannot be won
        return bestStepstoNotLoose-1; // Return - (steps until loose + 1)
}

Game::Boardstate BotQuickest::quickestWinOrLatestLooseMove(const Game::Boardstate &player, const Game::Boardstate &opponent)
{
    int bestStepstoWin = 20;
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
                    if (bestStepstoWin > 19)
                        bestMove = move;
                }
                else if (stepstoWin == bestStepstoNotLoose && rand() % 2)
                {
                    bestStepstoNotLoose = stepstoWin;
                    if (bestStepstoWin > 19)
                        bestMove = move;
                }
            }
        }
    }
    return bestMove;
}

QString BotQuickest::printStepsToWin(const Game::Boardstate &p1, const Game::Boardstate &p2, bool swap)
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
