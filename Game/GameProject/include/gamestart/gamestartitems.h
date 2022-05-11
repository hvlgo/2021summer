#ifndef GAMESTARTITEMS_H
#define GAMESTARTITEMS_H

#include <QGraphicsObject>
#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

class StartButton : public QGraphicsObject
{
    Q_OBJECT
public:
    StartButton(bool start);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
signals:
    void startButtonPressed();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    bool start;

};

#endif // GAMESTARTITEMS_H
