#ifndef BOTCHANCE_H
#define BOTCHANCE_H


#include "actor.h"
#include "game.h"


/*
 * This bot estimates the chance of winning by looking at all remaining possible cases
 * This bot will make the move with the highest estimated chance of winning
 */
class BotChance : public Actor
{
public:

    BotChance(GameScene *game, int playerId, QString name);

    void makeAMove();

private:

    // Calculate the chance of winning if all moves have the same probability
    static double chanceOfWinning(const Game::Boardstate &player, const Game::Boardstate &opponent);

    // Return the move with the highest chance of winning if all leagal moves have the same probability
    static Game::Boardstate highestChanceOfWinningMove(const Game::Boardstate &player, const Game::Boardstate &opponent);

    static QString printChanceToWin(const Game::Boardstate &p1, const Game::Boardstate &p2, bool swap = false);
};


#endif // BOTCHANCE_H
