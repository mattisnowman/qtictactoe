#include "brick.h"

#include <QPainter>
#include <QDebug>

#include "gamescene.h"

const QColor blue1(105, 136, 181);
const QColor red1(190, 108, 86);

Brick::Brick(int id, GameScene *scene):
    QGraphicsItem(), id(id), scene(scene)
{
    this->state=empty;
}


QRectF Brick::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    painter->setRenderHints(QPainter::HighQualityAntialiasing);

    if(this->state == player1)
    {
        painter->setPen(QPen(blue1, 8, Qt::SolidLine, Qt::RoundCap));
        painter->drawLine(QPoint(10, 10), QPoint(90, 90));
        painter->drawLine(QPoint(90, 10), QPoint(10, 90));
    }
    if(this->state == player2)
    {
        painter->setPen(QPen(red1, 8, Qt::SolidLine, Qt::RoundCap));
        painter->drawEllipse(QPoint(50,50), 41, 41);
    }

    painter->restore();
}

void Brick::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}


void Brick::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->scene->itemClicked(this->id);
}

