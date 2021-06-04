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

double Game::chanceOfWinning(const Boardstate &player, const Boardstate &opponent)
{
    if (isWin(player))
        return 1.;
    else if (isWin(opponent))
        return 0.;

    Boardstate validMoves = legalMoves(player, opponent);

    if (validMoves == empty)
        return 0.5;

    double sumofChance = 0.;
    int numberOfLegalMoves = 0;

    for (int i=0; i<9; i++)
    {
        Boardstate move = Boardstate(1 << i);

        if (move & validMoves)
        {
            sumofChance += 1.-chanceOfWinning(opponent, player | move);
            numberOfLegalMoves += 1;
        }
    }
    return sumofChance / numberOfLegalMoves;
}

int Game::minStepsToWin(Boardstate player, Boardstate opponent)
{
    int bestStepstoWin = 9;
    int bestStepstoNotLoose = 0;

    Boardstate validMoves = legalMoves(player, opponent);

    //This is a win. No more steps to win required: return 1
    if (isWin(player))
        return 1;
    //This is a loss, Return negative -1.
    if (isWin(opponent))
        return -1;
    //Rate a draw as a loose but at a later point (-2) than a straightout loss.
    if (validMoves == empty)
        return -2;

    // If game is not decided let players make moves recursivly until it is decided
    for (int i=0; i<9; i++)
    {
        // Generate moves by iterating over all 9 fields
        Boardstate move = Boardstate(1 << i);

        if (move & validMoves)
        {
            // Make the move and let the other player make a move.
            // Recursion until win or loose is reached
            // The (-) takes into account a perspective change from player to opponent
            int stepstoWin = -minStepsToWin(opponent, player | move);
            if (stepstoWin >= 0) // A win
            {
                bestStepstoWin = qMin(stepstoWin, bestStepstoWin);
            }
            else if  (stepstoWin < 0) //From here on only losses/draws
            {
                bestStepstoNotLoose = qMin(stepstoWin, bestStepstoNotLoose);
            }
        }
    }

    if (bestStepstoWin < 9)           // This means the game is winnable
        return bestStepstoWin+1;      // Return steps to finish from here + 1
    else                              // Game cannot be won
        return bestStepstoNotLoose-1; // Return - (steps until loose + 1)
}

Game::Boardstate Game::highestChanceOfWinningMove(const Boardstate &player, const Boardstate &opponent)
{
    double bestChance = -1.;
    Boardstate bestMove = empty;
    Boardstate validMoves = legalMoves(player, opponent);

    for (int i=0; i<9; i++)
    {
        Boardstate move = Boardstate(1 << i);

        if (move & validMoves)
        {
            double chancetoWin = 1-chanceOfWinning(opponent, player | move);
            if (chancetoWin > bestChance || bestMove == empty)
            {
                bestChance = chancetoWin;
                bestMove = move;
            }
        }
    }
    return bestMove;
}

Game::Boardstate Game::quickestWinOrLatestLooseMove(const Boardstate &player, const Boardstate &opponent)
{
    int bestStepstoWin = 9;
    int bestStepstoNotLoose = 0;

    Boardstate bestMove = empty;
    Boardstate validMoves = legalMoves(player, opponent);

    for (int i=0; i<9; i++)
    {
        Boardstate move = Boardstate(1 << i);

        if (move & validMoves)
        {
            if (bestMove == empty)
                bestMove = move;

            int stepstoWin = -minStepsToWin(opponent, player | move);
            if (stepstoWin > 0)
            {
                if (stepstoWin < bestStepstoWin)
                {
                    bestStepstoWin = stepstoWin;
                    bestMove = move;
                }
                else if (stepstoWin == bestStepstoWin && rand() % 2)
                {
                    bestStepstoWin = stepstoWin;
                    bestMove = move;
                }
            }
            else //if (stepstoWin < 0)
            {
                if (stepstoWin < bestStepstoNotLoose)
                {
                    bestStepstoNotLoose = stepstoWin;
                    if (bestStepstoWin > 8)
                        bestMove = move;
                }
                else if (stepstoWin == bestStepstoNotLoose && rand() % 2)
                {
                    bestStepstoNotLoose = stepstoWin;
                    if (bestStepstoWin > 8)
                        bestMove = move;
                }
            }
        }
    }
    return bestMove;
}

Game::Boardstate Game::randomMove(const Boardstate &player, const Boardstate &opponent)
{
    Boardstate validMoves = legalMoves(player, opponent);
    if (validMoves == empty)
        return validMoves;
    Boardstate move;
    do
    {
        move = Boardstate(1 << rand() % 9);
    }
    while (!(move & validMoves));
    return move;
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

QString Game::printChanceToWin(const Boardstate &p1, const Boardstate &p2, bool swap)
{
    QString s;
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (p1 & fromIndices(i,j))
                s += swap?"o":"x";
            else if (p2 & fromIndices(i,j))
                s +=swap?"x":"o";
            else
            {
                double chance = chanceOfWinning(p1 | fromIndices(i,j), p2);
                s += QString::number(chance);
            }
            if (j != 2)
                s += "|";
        }
        if (i != 2)
            s += "\n-+-+-\n";
    }
    return s;
}

QString Game::printStepsToWin(const Boardstate &p1, const Boardstate &p2, bool swap)
{
    QString s;
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (p1 & fromIndices(i,j))
                s += swap?"o":"x";
            else if (p2 & fromIndices(i,j))
                s +=swap?"x":"o";
            else
            {
                int steps = -minStepsToWin(p2, p1 | fromIndices(i,j));
                s += QString::number(steps);
            }
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
