#ifndef GAMEBASE_H
#define GAMEBASE_H

#include <QFlags>
#include <QString>


class Game
{
public:

    // An enum type to describe the state of the board for a single player
    enum boardstate{
        empty = 0b000000000,
        a00   = 0b000000001,
        a01   = 0b000000010,
        a02   = 0b000000100,
        a10   = 0b000001000,
        a11   = 0b000010000,
        a12   = 0b000100000,
        a20   = 0b001000000,
        a21   = 0b010000000,
        a22   = 0b100000000,
        full  = 0b111111111,
        win_h1 = a00 | a01 | a02,
        win_h2 = a10 | a11 | a12,
        win_h3 = a20 | a21 | a22,
        win_v1 = a00 | a10 | a20,
        win_v2 = a01 | a11 | a21,
        win_v3 = a02 | a12 | a22,
        win_d1 = a00 | a11 | a22,
        win_d2 = a02 | a11 | a20
    };

    Q_DECLARE_FLAGS(Boardstate, boardstate);

    enum Outcome{
        draw = 0x0,
        player1win  = 0x1,
        player2win  = 0x2,
    };

    Game();

    // Static functions to work with Boardstate

    // Return a boardstate with a single brick at position i
    static Boardstate fromIndices(const int &i);

    // Return a boardstate with a single brick at row i, column j
    static Boardstate fromIndices(const int &i, const int &j);

    // Return true if the boardstates of the 2 players is valid, i.e. not overlapping
    static bool isValidState(const Boardstate &p1, const Boardstate &p2);

    // Return all leagal moves for two Boardstates describing 2 players
    static Boardstate legalMoves(const Boardstate &p1, const Boardstate &p2);

    // Check if boardstate is a win */
    static bool isWin(const Boardstate &s);

    // Calculate the chance of winning if all moves are randomized
    static double chanceOfWinning(const Boardstate &player, const Boardstate &opponent);

    // Returns a positive number with the minimum steps to win +1
    // Returns a negative number with the maximum steps until loose -1, if no win is predicted
    // A draw counts as a loss (negative number) but with one additional step added (-2)
    static int minStepsToWin(Boardstate player, Boardstate opponent);

    // Return the move with the highest chance of winning if both players follow this strategy
    static Boardstate highestChanceOfWinningMove(const Boardstate &player, const Boardstate &opponent);

    // Return the move that leads to quickest win or to the latest loose if winning is not possible
    static Boardstate quickestWinOrLatestLooseMove(const Boardstate &player, const Boardstate &opponent);

    // Return a random but valid move
    static Boardstate randomMove(const Boardstate &player, const Boardstate &opponent);

    // Three functions to simplify output on the command line:
    static QString toString(const Boardstate &p1, const Boardstate &p2 = empty);

    static QString printChanceToWin(const Boardstate &p1, const Boardstate &p2, bool swap = false);

    static QString printStepsToWin(const Boardstate &p1, const Boardstate &p2, bool swap = false);



    void clear();

    Boardstate legalMoves() const;

    bool makeMovePlayer1(const Boardstate &move);

    bool makeMovePlayer2(const Boardstate &move);

    const Boardstate &getPlayer1() const {return player1;}

    const Boardstate &getPlayer2() const {return player2;}

    bool finished() const;

    Outcome whoWon() const;

private:

    Boardstate player1;

    Boardstate player2;
};

#endif // GAMEBASE_H
