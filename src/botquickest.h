#ifndef BOTQUICKEST_H
#define BOTQUICKEST_H


#include "actor.h"
#include "game.h"

/*
 * This bot will make the move that leads to the quickest win.
 * If no win is possible, the move that leads to a draw is made.
 * If no draw is possible (there should always be a draw possible),
 * the move that leads to the latest loss is made.
 *
 * For this algorithm to work, we need to predict the behaviour of the opponent.
 * It is assumed that the opponent uses the same strategy, which coincides with perfect strategy.
 *
 * The strategy will allways enforce a draw but lead to a win if the opponent makes an error.
 */

class BotQuickest : public Actor
{
public:

    BotQuickest(GameScene *game, int playerId, QString name);

    void makeAMove();

private:
    // Returns a positive number with the minimum steps to win +1
    // Returns a negative number with the maximum steps until loose -1, if no win is predicted
    // A draw generates a return value with undefined sign but with the largest absolute value
    static int minStepsToWin(Game::Boardstate player, Game::Boardstate opponent);

    // Return the move that leads to quickest win or to the latest loose if winning is not possible
    static Game::Boardstate quickestWinOrLatestLooseMove(const Game::Boardstate &player, const Game::Boardstate &opponent);

    static QString printStepsToWin(const Game::Boardstate &p1, const Game::Boardstate &p2, bool swap = false);
};


#endif // BOTQUICKEST_H
