#ifndef BOTACTOR_H
#define BOTACTOR_H

#include "actor.h"


class BotActor : public Actor
{
public:

    enum Strategy
    {
        quickestWin,
        highestProbability,
        random
    };

    BotActor(GameScene *game, int playerId, QString name, Strategy s=highestProbability);

    void makeAMove();

private:

    Strategy strategy;
};

#endif // PLAYERACTOR_H
