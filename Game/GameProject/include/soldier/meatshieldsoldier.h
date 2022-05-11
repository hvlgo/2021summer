#ifndef MEATSHIELDSOLDIER_H
#define MEATSHIELDSOLDIER_H

#include <soldier.h>

class MeatShieldSoldier : public Soldier
{
    Q_OBJECT
public:
    MeatShieldSoldier(int _x, int _y, qreal len, bool _player);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    QPainterPath shape() const override;
};

#endif // MEATSHIELDSOLDIER_H
