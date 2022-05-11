#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsObject>
#include <QPainter>
#define LENGTH 3

class Arrow : public QGraphicsObject
{
    Q_OBJECT
public:
    Arrow(bool _mirrored);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
private:
    bool mirrored;
};

#endif // ARROW_H
