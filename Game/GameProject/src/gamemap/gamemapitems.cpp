#include "gamemapitems.h"
#include <QDebug>
FirstBattleGate::FirstBattleGate(int num) : level(num)
{

}

QRectF FirstBattleGate::boundingRect() const
{
    return QRectF(-46 - 0.5, -16 - 0.5, 93 + 0.5, 32 + 0.5);
}

void FirstBattleGate::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    if (level == 1)
    {
        QPixmap pix;
        pix.load(":/image/image/ui/firstbattlegate.png");
        painter->drawPixmap(-pix.width() / 2, -pix.height() / 2, pix.width(), pix.height(), pix);
    }
    else if (level == 2)
    {
        QPixmap pix;
        pix.load(":/image/image/ui/secondbattlegate.png");
        painter->drawPixmap(-pix.width() / 2, -pix.height() / 2, pix.width(), pix.height(), pix);
    }
}

void FirstBattleGate::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    emit firstButtonPressed();
}
