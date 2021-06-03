#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsItem>

class GameScene;

class Brick : public QGraphicsItem
{
public:

    enum State{
        empty   = 0x0,
        player1 = 0x1,
        player2 = 0x2
    };

    Brick(int id, GameScene *scene);

    inline void setState(const State &s){this->state = s; this->update();}

    inline State getState() const {return this->state;}

    inline void setId(const int &i){this->id = i;}

    inline int getId() const {return this->id;}

protected:

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private:

    int id;

    GameScene *scene;

    State state;
};

#endif // BRICK_H
