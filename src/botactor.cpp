#include "botactor.h"

#include "gamescene.h"
#include "game.h"

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
        qDebug().noquote() << Game::printStepsToWin(player, opponent);
        qDebug() << "-------------";
        move = Game::quickestWinOrLatestLooseMove(player, opponent);
    }
    else if (strategy == highestProbability)
    {
        qDebug() << "-------------";
        qDebug().noquote() << this->name << ": using highest probability to win:";
        qDebug().noquote() << Game::printChanceToWin(player, opponent);
        qDebug() << "-------------";
        move = Game::highestChanceOfWinningMove(player, opponent);
    }
    else if (strategy == random)
    {
        qDebug().noquote() << this->name << ": making random move";
        move = Game::randomMove(player, opponent);
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
