#ifndef GAMEMAPITEMS_H
#define GAMEMAPITEMS_H

#include <QGraphicsObject>
#include <QMouseEvent>
#include <QPainter>

class FirstBattleGate : public QGraphicsObject
{
    Q_OBJECT
public:
    FirstBattleGate(int num);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
signals:
    void firstButtonPressed();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    int level {1};
};

#endif // GAMEMAPITEMS_H
