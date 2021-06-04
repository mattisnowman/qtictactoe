#include "botchance.h"

#include "gamescene.h"

BotChance::BotChance(GameScene *game, int playerId,  QString name):
    Actor(game, name, playerId)
{

}

void BotChance::makeAMove()
{
    Game &g = this->game->getGame();

    Game::Boardstate move;

    Game::Boardstate player = g.getPlayer(playerId);
    Game::Boardstate opponent = g.getPlayer(!playerId);

    qDebug() << "-------------";
    qDebug().noquote() << this->name << ": using highest probability to win:";
    qDebug().noquote() << printChanceToWin(player, opponent, playerId == 1);

    move = highestChanceOfWinningMove(player, opponent);

    this->game->getGame().makeMove(playerId, move);
    this->finishedTurn();
}

double BotChance::chanceOfWinning(const Game::Boardstate &player, const Game::Boardstate &opponent)
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

Game::Boardstate BotChance::highestChanceOfWinningMove(const Game::Boardstate &player, const Game::Boardstate &opponent)
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

QString BotChance::printChanceToWin(const Game::Boardstate &p1, const Game::Boardstate &p2, bool swap)
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
