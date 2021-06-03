#include "playeractor.h"

#include "gamescene.h"
#include "game.h"

PlayerActor::PlayerActor(GameScene *parent, int playerId, QString name):
    Actor(parent, name, playerId)
{

}

void PlayerActor::itemClicked(int id)
{
    Game::Boardstate move = Game::fromIndices(id);
    if (playerId == 0)
    {
        if (this->game->getGame().makeMovePlayer1(move))
            this->finishedTurn();
    }
    if (playerId == 1)
    {
        if (this->game->getGame().makeMovePlayer2(move))
            this->finishedTurn();
    }
}

QString PlayerActor::getNote() const
{
    return this->name + "s turn";
}
