#include "actornote.h"

#include <QPainter>

const QColor blue1(105, 136, 181);
const QColor red1(190, 108, 86);

ActorNote::ActorNote(QGraphicsItem *parent):
    QGraphicsItem(parent), playerID(-1)
{

}

void ActorNote::setMessage(int player, const QString &m)
{
    this->playerID = player;
    this->message = m;
    this->update();
}


QRectF ActorNote::boundingRect() const
{
    return QRectF(0, 0, 400, 20);
}

void ActorNote::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (this->playerID == -1)
        return;

    painter->save();

    painter->setRenderHints(QPainter::HighQualityAntialiasing);

    if(this->playerID == 0)
    {
        painter->setPen(QPen(blue1, 2, Qt::SolidLine, Qt::RoundCap));
        painter->drawLine(QPoint(2, 2), QPoint(18, 18));
        painter->drawLine(QPoint(18, 2), QPoint(2, 18));
    }
    if(this->playerID == 1)
    {
        painter->setPen(QPen(red1, 2, Qt::SolidLine, Qt::RoundCap));
        painter->drawEllipse(QPointF(10,10), 9, 9);
    }
    painter->setPen(QPen(QColor(70, 70, 70), 2, Qt::SolidLine, Qt::RoundCap));
    painter->drawText(QRectF(22, 0, 400-22, 20), Qt::AlignLeft | Qt::AlignVCenter, this->message);

    painter->restore();
}
