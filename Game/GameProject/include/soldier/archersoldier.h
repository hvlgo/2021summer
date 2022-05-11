#ifndef ARCHERSOLDIER_H
#define ARCHERSOLDIER_H

#include "soldier.h"

class ArcherSoldier : public Soldier
{
    Q_OBJECT
public:
    ArcherSoldier(int _x, int _y, qreal len, bool _player);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    QPainterPath shape() const override;
};

#endif // ARCHERSOLDIER_H
