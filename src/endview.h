#ifndef ENDVIEW_H
#define ENDVIEW_H

#include <QGraphicsItem>

#include "game.h"

class GameScene;

class EndView : public QGraphicsItem
{
public:

    EndView(GameScene *scene, QString player1, QString player2, int player1wins, int player2wins);

protected:

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private:

    GameScene *scene;

    QString player1;

    QString player2;

    int player1wins;

    int player2wins;
};

#endif // ENDVIEW_H
