#include "gamestartitems.h"
#include <qpixmap.h>
#include <QDebug>
StartButton::StartButton(bool _start) : start(_start)
{
}

QRectF StartButton::boundingRect() const
{
    return QRectF(-70 - 0.5, -32 - 0.5, 140 + 0.5, 64 + 0.5);
}

void StartButton::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QImage pix;
    if (start)
    {
        pix.load(":/image/image/ui/startgame.png");
    }
    else
    {
        pix.load(":/image/image/ui/course.png");
    }
    painter->drawImage(boundingRect(), pix);
}       

void StartButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit startButtonPressed();
}
