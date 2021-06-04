#include "boardbase.h"

#include "colors.h"

#include <QPainter>

BoardBase::BoardBase(QGraphicsItem *parent):
    QGraphicsItem(parent)
{

}


QRectF BoardBase::boundingRect() const
{
    return QRectF(0, 0, 300, 300);
}

void BoardBase::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->setRenderHints(QPainter::HighQualityAntialiasing);
    painter->setPen(QPen(gray, 4, Qt::SolidLine, Qt::RoundCap));
    for (auto i : {100, 200})
    {
        painter->drawLine(QLineF(0, i, 300, i));
        painter->drawLine(QLineF(i, 0, i, 300));
    }
    painter->restore();
}
