#ifndef BOTGUESSING_H
#define BOTGUESSING_H


#include "actor.h"
#include "game.h"


class BotGuessing : public Actor
{
public:

    BotGuessing(GameScene *game, int playerId, QString name);

    void makeAMove();

    QString getNote() const;

private:
    // Return a random but valid move
    static Game::Boardstate randomMove(const Game::Boardstate &player, const Game::Boardstate &opponent);
};


#endif // BOTGUESSING_H
