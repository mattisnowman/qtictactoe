#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <QString>
#include <QDebug>

#include "boardbase.h"
#include "brick.h"
#include "game.h"
#include "actor.h"
#include "endview.h"
#include "actornote.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GameScene(QObject *parent=nullptr);

    const Game &getGame() const {return this->game;}

    Game &getGame() {return this->game;}

    void newSeries(const QList<Actor *> &players);

    void nextTurn();

    void itemClicked(int id);

    void newGame();

public slots:

    void makeAMove();


private:

    Game game;

    BoardBase *base;

    EndView *endItem;

    QList<Brick*> bricks;

    ActorNote *actorNote;

    QList<Actor*> players;

    int activePlayer;

    int player1Wins;

    int player2Wins;
};

#endif // BOARD_H
