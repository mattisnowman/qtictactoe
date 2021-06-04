#include "botguessing.h"

#include "gamescene.h"

BotGuessing::BotGuessing(GameScene *game, int playerId,  QString name):
    Actor(game, name, playerId)
{

}

void BotGuessing::makeAMove()
{
    Game &g = this->game->getGame();

    Game::Boardstate move;

    Game::Boardstate player = g.getPlayer(playerId);
    Game::Boardstate opponent = g.getPlayer(!playerId);

    qDebug().noquote() << this->name << ": making random move";

    Game::Boardstate validMoves = Game::legalMoves(player, opponent);
    Q_ASSERT(validMoves != Game::empty);

    do
    {
        move = Game::Boardstate(1 << rand() % 9);
    }
    while (!(move & validMoves));

    this->game->getGame().makeMove(playerId, move);
    this->finishedTurn();
}
