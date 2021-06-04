#include "botguessing.h"

#include "gamescene.h"

BotGuessing::BotGuessing(GameScene *game, int playerId,  QString name):
    Actor(game, name, playerId)
{

}

void BotGuessing::makeAMove()
{
    Game &g = this->game->getGame();

    Game::Boardstate move;
    Game::Boardstate player, opponent;

    if (playerId == 0)
    {
        player = g.getPlayer1();
        opponent = g.getPlayer2();
    }
    if (playerId == 1)
    {
        player = g.getPlayer2();
        opponent = g.getPlayer1();
    }

    qDebug().noquote() << this->name << ": making random move";
    move = randomMove(player, opponent);

    if (playerId == 0)
    {
        this->game->getGame().makeMovePlayer1(move);
    }
    if (playerId == 1)
    {
        this->game->getGame().makeMovePlayer2(move);
    }
    this->finishedTurn();
}

QString BotGuessing::getNote() const
{
    return this->getName() + " is thinking.";
}

Game::Boardstate BotGuessing::randomMove(const Game::Boardstate &player, const Game::Boardstate &opponent)
{
    Game::Boardstate validMoves = Game::legalMoves(player, opponent);
    if (validMoves == Game::empty)
        return validMoves;
    Game::Boardstate move;
    do
    {
        move = Game::Boardstate(1 << rand() % 9);
    }
    while (!(move & validMoves));
    return move;
}
