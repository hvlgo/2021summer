#ifndef HUMANSOLDIER_H
#define HUMANSOLDIER_H

#include <soldier.h>

class HumanSoldier : public Soldier
{
    Q_OBJECT
public:
    HumanSoldier(int _x, int _y, qreal len, bool _player);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    QPainterPath shape() const override;
};

#endif // HUMANSOLDIER_H
