#include "gamescene.h"

#include <QTimer>

#include "playeractor.h"
#include "botquickest.h"

GameScene::GameScene(QObject *parent):
    QGraphicsScene(parent), endItem(nullptr)
{
    this->base = new BoardBase();
    this->addItem(this->base);
    this->activePlayer = -1;
    this->startingPlayer = -1;

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            Brick *b = new Brick(i*3+j, this);
            b->setPos(j*100, i*100);
            this->bricks.append(b);
            this->addItem(b);
        }
    }
    this->actorNote = new ActorNote();
    this->actorNote->setPos(0, 300);
    this->actorNote->setZValue(2);
    this->addItem(this->actorNote);
    this->newSeries({new PlayerActor(this, 0, "Player"), new BotQuickest(this, 1, "GoodBot")});
}

void GameScene::newSeries(const QList<Actor*> &players)
{
    while(this->players.size())
    {
        delete this->players.takeFirst();
    }
    this->players.append(players);
    for (auto p : this->players)
    {
        p->setParent(this);
    }

    this->startingPlayer = 0;

    this->player1Wins = 0;
    this->player2Wins = 0;
    this->newGame();
}

void GameScene::nextTurn()
{

    for(auto b : this->bricks)
    {
        Game::Boardstate pos =Game::fromIndices(b->getId());
        if (game.getPlayer1() & pos)
            b->setState(Brick::player1);
        if (game.getPlayer2() & pos)
            b->setState(Brick::player2);
    }

    if (game.finished())
    {
        Game::Outcome result = game.whoWon();

        this->actorNote->setMessage(this->startingPlayer,
                                    this->players[this->startingPlayer]->getName() + " will start the next game.");

        if (result == Game::player1win)
            this->player1Wins++;
        if (result == Game::player2win)
            this->player2Wins++;

        endItem = new EndView(this,
                                 this->players[0]->getName(),
                                 this->players[1]->getName(),
                                 this->player1Wins,
                                 this->player2Wins);

        this->addItem(endItem);
        return;
    }

    this->activePlayer = !this->activePlayer;

    this->actorNote->setMessage(this->activePlayer, this->players[this->activePlayer]->getNote());

    //makeAMove();
    QTimer::singleShot(25, this, SLOT(makeAMove()));
}

void GameScene::makeAMove()
{
    this->players[this->activePlayer]->makeAMove();
}

void GameScene::itemClicked(int id)
{
    if (this->activePlayer > -1 && this->activePlayer < this->players.size())
    {
        this->players[this->activePlayer]->itemClicked(id);
    }
}

void GameScene::newGame()
{
    if (this->endItem)
    {
        delete this->endItem;
        this->endItem = nullptr;
    }

    this->game.clear();

    this->activePlayer = !this->startingPlayer;
    this->startingPlayer = !this->startingPlayer;

    for(auto b : this->bricks)
    {
        b->setState(Brick::empty);
    }

    this->nextTurn();
}
