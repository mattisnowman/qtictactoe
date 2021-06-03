#ifndef ACTORNOTE_H
#define ACTORNOTE_H

#include <QGraphicsItem>

class ActorNote : public QGraphicsItem
{
public:

    ActorNote(QGraphicsItem *parent = nullptr);

    void setMessage(int playerID, const QString &m);

protected:
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

private:
    int playerID;

    QString message;
};

#endif // ACTORNOTE_H
