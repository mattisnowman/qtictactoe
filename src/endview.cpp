#include "endview.h"

#include <QPainter>
#include <QDebug>

#include "gamescene.h"


const QColor blue1(105, 136, 181);
const QColor blue2(81, 97, 104);
const QColor red1(190, 108, 86);
const QColor red2(148, 92, 91);
const QColor gray(80, 80, 80);


EndView::EndView(GameScene *scene, QString player1, QString player2, int player1wins, int player2wins):
    QGraphicsItem(), scene(scene), player1(player1), player2(player2), player1wins(player1wins), player2wins(player2wins)
{

}

QRectF EndView::boundingRect() const
{
    return QRectF(-100, -100, 500, 500);
}

void EndView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    painter->setRenderHints(QPainter::HighQualityAntialiasing);


    Game::Boardstate winpattern;
    if (this->scene->getGame().whoWon() == Game::player1win)
    {
        painter->setPen(QPen(blue1, 8, Qt::SolidLine, Qt::RoundCap));
        winpattern = this->scene->getGame().getPlayer1();
    }

    if (this->scene->getGame().whoWon() == Game::player2win)
    {
        painter->setPen(QPen(red1, 8, Qt::SolidLine, Qt::RoundCap));
        winpattern = this->scene->getGame().getPlayer2();
    }

    if((winpattern & Game::win_h1) == Game::win_h1)
        painter->drawLine(25, 50, 275, 50);
    if((winpattern & Game::win_h2) == Game::win_h2)
        painter->drawLine(25, 150, 275, 150);
    if((winpattern & Game::win_h3) == Game::win_h3)
        painter->drawLine(25, 250, 275, 250);
    if((winpattern & Game::win_v1) == Game::win_v1)
        painter->drawLine(50, 25, 50, 275);
    if((winpattern & Game::win_v2) == Game::win_v2)
        painter->drawLine(150, 25, 150, 275);
    if((winpattern & Game::win_v3) == Game::win_v3)
        painter->drawLine(250, 25, 250, 275);
    if((winpattern & Game::win_d1) == Game::win_d1)
        painter->drawLine(25, 25, 275, 275);
    if((winpattern & Game::win_d2) == Game::win_d2)
        painter->drawLine(25, 275, 275, 25);

    painter->fillRect(-100,-100,500,500, QColor(255, 255, 255, 150));

    QFont font = painter->font();
    font.setPointSize(25);
    painter->setFont(font);

    if (this->scene->getGame().whoWon() == Game::draw)
    {
        painter->setPen(gray);
        painter->drawText(QRect(0, 70, 300, 100), Qt::AlignCenter, "DRAW");
    }
    else if (this->scene->getGame().whoWon() == Game::player1win)
    {
        painter->drawText(QRect(0, 70, 300, 100), Qt::AlignCenter, QString("%1 wins!").arg(this->player1));
    }
    else if (this->scene->getGame().whoWon() == Game::player2win)
    {
        painter->setPen(red1);
        painter->drawText(QRect(0, 70, 300, 100), Qt::AlignCenter, QString("%1 wins!").arg(this->player2));
    }

    painter->setPen(blue1);
    painter->drawText(QRect(0, 140, 140, 40), Qt::AlignRight, QString("%1").arg(this->player1wins));

    painter->setPen(gray);
    painter->drawText(QRect(0, 140, 300, 40), Qt::AlignHCenter, QString(":"));

    painter->setPen(red1);
    painter->drawText(QRect(160, 140, 140, 40), Qt::AlignLeft, QString("%1").arg(this->player2wins));

    font.setPointSize(12);
    painter->setFont(font);
    painter->setPen(gray);
    painter->drawText(QRect(0, 180, 300, 30), Qt::AlignHCenter, QString("Click anywhere to continue."));



    painter->restore();
}

void EndView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->scene->newGame();
}


void EndView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

