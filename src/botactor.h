#ifndef BOTACTOR_H
#define BOTACTOR_H

#include "actor.h"
#include "game.h"


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

    QString getNote() const;

private:

    // Calculate the chance of winning if all moves are randomized
    static double chanceOfWinning(const Game::Boardstate &player, const Game::Boardstate &opponent);

    // Returns a positive number with the minimum steps to win +1
    // Returns a negative number with the maximum steps until loose -1, if no win is predicted
    // A draw counts as a loss (negative number) but with one additional step added (-2)
    static int minStepsToWin(Game::Boardstate player, Game::Boardstate opponent);

    // Return the move with the highest chance of winning if both players follow this strategy
    static Game::Boardstate highestChanceOfWinningMove(const Game::Boardstate &player, const Game::Boardstate &opponent);

    // Return the move that leads to quickest win or to the latest loose if winning is not possible
    static Game::Boardstate quickestWinOrLatestLooseMove(const Game::Boardstate &player, const Game::Boardstate &opponent);

    // Return a random but valid move
    static Game::Boardstate randomMove(const Game::Boardstate &player, const Game::Boardstate &opponent);

    static QString printChanceToWin(const Game::Boardstate &p1, const Game::Boardstate &p2, bool swap = false);

    static QString printStepsToWin(const Game::Boardstate &p1, const Game::Boardstate &p2, bool swap = false);


    Strategy strategy;
};

#endif // PLAYERACTOR_H
