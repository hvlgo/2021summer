#ifndef BOSSSOLDIER_H
#define BOSSSOLDIER_H

#include <soldier.h>

class BossSoldier : public Soldier
{
    Q_OBJECT
public:
    BossSoldier(int _x, int _y, qreal len, bool _player);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    QPainterPath shape() const override;
};

#endif // BOSSSOLDIER_H
