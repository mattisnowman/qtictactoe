#include "actor.h"

#include "gamescene.h"

Actor::Actor(GameScene *parent, QString name, int playerId):
    game(parent), name(name), playerId(playerId)
{

}

Actor::~Actor()
{

}

void Actor::makeAMove()
{

}

void Actor::itemClicked(int id)
{
    Q_UNUSED(id);
}

const QString &Actor::getName() const
{
    return this->name;
}

void Actor::finishedTurn()
{
    this->game->nextTurn();
}

void Actor::setParent(GameScene *p)
{
    this->game = p;
}
