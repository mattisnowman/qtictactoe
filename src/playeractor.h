#ifndef PLAYERACTOR_H
#define PLAYERACTOR_H

#include "actor.h"

class PlayerActor : public Actor
{
public:

    PlayerActor(GameScene *game, int playerId, QString name);

    void itemClicked(int id);

    QString getNote() const;

};

#endif // PLAYERACTOR_H
