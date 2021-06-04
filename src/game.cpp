#include "game.h"

Game::Boardstate Game::fromIndices(const int &i)
{
    return Boardstate(1 << i);
}

Game::Boardstate Game::fromIndices(const int &i, const int &j)
{
    return Boardstate(1 << (3*i+j));
}

bool Game::isValidState(const Boardstate &p1, const Boardstate &p2)
{
    return !(p1 & p2);
}

Game::Boardstate Game::legalMoves(const Boardstate &p1, const Boardstate &p2)
{
    return Boardstate(full & ~(p1 | p2));
}

bool Game::isWin(const Boardstate &s)
{
    return ((s & win_h1) == win_h1) ||
           ((s & win_h2) == win_h2) ||
           ((s & win_h3) == win_h3) ||
           ((s & win_v1) == win_v1) ||
           ((s & win_v2) == win_v2) ||
           ((s & win_v3) == win_v3) ||
           ((s & win_d1) == win_d1) ||
           ((s & win_d2) == win_d2);
}


QString Game::toString(const Boardstate &p1, const Boardstate &p2)
{
    QString s;
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (p1 & fromIndices(i,j))
                s += "x";
            else if (p2 & fromIndices(i,j))
                s += "o";
            else
                s += " ";
            if (j != 2)
                s += "|";
        }
        if (i != 2)
            s += "\n-+-+-\n";
    }
    return s;
}

Game::Game()
{

}

void Game::clear()
{
    player1 = empty;
    player2 = empty;
}

Game::Boardstate Game::legalMoves() const
{
    return legalMoves(player1, player2);
}

bool Game::makeMovePlayer1(const Boardstate &move)
{
    if (legalMoves() & move)
    {
        player1 |= move;
        return true;
    }
    return false;
}

bool Game::makeMovePlayer2(const Boardstate &move)
{
    if (legalMoves() & move)
    {
        player2 |= move;
        return true;
    }
    return false;
}

bool Game::finished() const
{
    if (legalMoves() == empty)
        return true;
    if (isWin(player1))
        return true;
    if (isWin(player2))
        return true;
    return false;
}

Game::Outcome Game::whoWon() const
{
    if (isWin(player1))
        return player1win;
    if (isWin(player2))
        return player2win;
    return draw;
}
