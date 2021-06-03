#ifndef BOARDBACKGROUND_H
#define BOARDBACKGROUND_H

#include <QGraphicsItem>

class BoardBase : public QGraphicsItem
{
public:

    BoardBase(QGraphicsItem *parent = nullptr);

    virtual QRectF boundingRect() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // BOARDBACKGROUND_H
