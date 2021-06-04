#ifndef BOTCHANCE_H
#define BOTCHANCE_H


#include "actor.h"
#include "game.h"


class BotChance : public Actor
{
public:

    BotChance(GameScene *game, int playerId, QString name);

    void makeAMove();

    QString getNote() const;

private:

    // Calculate the chance of winning if all moves are randomized
    static double chanceOfWinning(const Game::Boardstate &player, const Game::Boardstate &opponent);

    // Return the move with the highest chance of winning if both players follow this strategy
    static Game::Boardstate highestChanceOfWinningMove(const Game::Boardstate &player, const Game::Boardstate &opponent);

    static QString printChanceToWin(const Game::Boardstate &p1, const Game::Boardstate &p2, bool swap = false);
};


#endif // BOTCHANCE_H
