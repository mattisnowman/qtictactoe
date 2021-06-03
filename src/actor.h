#ifndef GAMEACTOR_H
#define GAMEACTOR_H

#include <QString>

class GameScene;

class Actor
{
public:

    Actor(GameScene *game, QString name, int playerId);

    virtual ~Actor();

    virtual void makeAMove();

    virtual void itemClicked(int id);

    virtual QString getNote() const;

    const QString &getName() const;

    void finishedTurn();

    void setParent(GameScene *p);

protected:
    GameScene* game;

    QString name;

    int playerId;
};

#endif // GAMEACTOR_H
