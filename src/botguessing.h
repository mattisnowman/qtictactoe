#ifndef BOTGUESSING_H
#define BOTGUESSING_H


#include "actor.h"
#include "game.h"


class BotGuessing : public Actor
{
public:

    BotGuessing(GameScene *game, int playerId, QString name);

    void makeAMove();
};


#endif // BOTGUESSING_H
