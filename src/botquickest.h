#ifndef BOTQUICKEST_H
#define BOTQUICKEST_H


#include "actor.h"
#include "game.h"


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
