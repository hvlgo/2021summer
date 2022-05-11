#ifndef BATTLEMAPCOMP_H
#define BATTLEMAPCOMP_H

#include <QGraphicsObject>
#include <QPainter>
#include <QPoint>
#include <QPolygonF>
#include <QRegion>
#include <QColor>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QTime>
#include <QWidget>

class BattleMapComp : public QGraphicsObject
{
    Q_OBJECT
public:
    BattleMapComp(int _x, int _y, qreal len, qreal penLen);

    QRectF  boundingRect()  const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    QPainterPath shape()  const override;
    const QPolygonF findOthers(qreal const len) const;

    void setObstacle(int);
    void setOccupied(bool);
    void setInMoveRange(bool);
    void setInAttackRange(bool);
    void setHarm(bool);
    void setHinder(bool);
    int getObstacle() const;
    bool getOccupied() const;
    bool getInMoveRange() const;
    bool getInAttackRange() const;
    bool getHarm() const;
    bool getHinder() const;
    qreal getLen() const;

    int x() const;
    int y() const;
signals:
    void FocusIn(int, int);
    void FocusOut(int, int);
    void MousePress(int, int);
private:
    int xpos, ypos;
    qreal m_len;
    qreal penLen;
    int Obstacle {0};
    bool Occupied {false};
    bool InMoveRange {false};
    bool InAttackRange {false};
    bool Harm {false};
    bool Hinder {false};
protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // BATTLEMAPCOMP_H
