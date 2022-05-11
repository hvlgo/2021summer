#include "battlemapcomp.h"
#include <QVector>
#include <cmath>
#include <QDebug>
#include <QGraphicsScene>

BattleMapComp::BattleMapComp(int _x, int _y, qreal len, qreal _penLen) : xpos(_x), ypos(_y), m_len(len), penLen(_penLen)
{
    setFlag(ItemIsFocusable);
}

QRectF BattleMapComp::boundingRect() const
{
    const QPointF topleft = (QPointF(-m_len * sqrt(3) / 2, -m_len));
    const QPointF bottomright = (QPointF(m_len * sqrt(3) / 2, m_len));
    return QRectF(topleft, bottomright);
}

void BattleMapComp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *parent)
{
    // * this only work in the first paint
    if (Obstacle != 0)
    {
        QPixmap pix;
        switch (Obstacle)
        {
            case 1:
                pix.load(":image/image/land/obstacle/ocean.png");
                break;
            case 2:
                pix.load(":image/image/land/obstacle/mountain.png");
                break;
            case 3:
                pix.load(":image/image/land/obstacle/castle.png");
                break;
            default:
                throw "Invalid";
        }
        painter->drawPixmap(-m_len * sqrt(3) / 2, -m_len, m_len * sqrt(3), m_len * 2, pix);
        return;
    }
    
    if (hasFocus() && Occupied)
    {
        QPen pen(QColor(111, 30, 168, 66), penLen, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
        painter->setPen(pen);
        painter->setBrush(QBrush(QColor(24, 168, 17, 66), Qt::SolidPattern));
        painter->drawConvexPolygon(findOthers(m_len));
        return;
    }
    else if (hasFocus() && !Occupied)
    {
        QPen pen(QColor(111, 30, 168, 66), penLen, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
        painter->setPen(pen);
        painter->setBrush(QBrush(QColor(172, 69, 245, 96), Qt::SolidPattern));
        painter->drawConvexPolygon(findOthers(m_len));
        return;
    }
    else if (!hasFocus())
    {
        if (InAttackRange && InMoveRange && !Occupied) // * this must be up
        {
            QPen pen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
            painter->setPen(pen);
            painter->setBrush(QBrush(QColor(172, 69, 245, 96), Qt::SolidPattern));
            painter->drawConvexPolygon(findOthers(m_len));
            return;
        }
        else if ((InAttackRange && !InMoveRange && !Occupied) || (InAttackRange && Occupied))
        {
            QPen pen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
            painter->setPen(pen);
            QPixmap pix;
            if (Harm)
            {
                pix.load(":/image/image/land/attack/volcano.png");
            }
            else if (Hinder)
            {
                pix.load(":/image/image/land/lower/winterForest.png");
            }
            else
            {
                pix.load(":image/image/land/ordinary/plains.png");
            }
            painter->setBrush(pix);
            painter->drawPixmap(-m_len * sqrt(3) / 2, -m_len, m_len * sqrt(3), m_len * 2, pix);
            painter->drawConvexPolygon(findOthers(m_len));
            return;
        }
        else if (InMoveRange && !Occupied)
        {
            QPen pen(QColor(111, 30, 168, 66), penLen, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);
            painter->setPen(pen);
            painter->setBrush(QBrush(QColor(172, 69, 245, 96), Qt::SolidPattern));
            painter->drawConvexPolygon(findOthers(m_len));
            return;
        }
        else
        {
            QPixmap pix;
            if (Harm)
            {
                pix.load(":/image/image/land/attack/volcano.png");
            }
            else if (Hinder)
            {
                pix.load(":/image/image/land/lower/winterForest.png");
            }
            else
            {
                pix.load(":image/image/land/ordinary/plains.png");
            }
            painter->drawPixmap(-m_len * sqrt(3) / 2, -m_len, m_len * sqrt(3), m_len * 2, pix);
            return;
        }
    }

}

QPainterPath BattleMapComp::shape() const
{
    QPainterPath path;
    path.addPolygon(findOthers(m_len));
    return path;
}

const QPolygonF BattleMapComp::findOthers(qreal const len) const
{
    QVector<QPointF> points;
    points.append(QPointF(0, -len));
    points.append(QPointF(len * sqrt(3) / 2, -len / 2));
    points.append(QPointF(len * sqrt(3) / 2, len / 2));
    points.append(QPointF(0, len));
    points.append(QPointF(-len * sqrt(3) / 2, len / 2));
    points.append(QPointF(-len * sqrt(3) / 2, -len / 2));
    return QPolygonF(points);
}


void BattleMapComp::focusInEvent(QFocusEvent *event)
{
    emit FocusIn(xpos, ypos);
}

void BattleMapComp::focusOutEvent(QFocusEvent *event)
{
    emit FocusOut(xpos, ypos);
}

void BattleMapComp::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit MousePress(xpos, ypos);
}

void BattleMapComp::setObstacle(int value)
{
    Obstacle = value;
}

void BattleMapComp::setOccupied(bool value)
{
    Occupied = value;
}

void BattleMapComp::setInMoveRange(bool value)
{
    InMoveRange = value;
}

void BattleMapComp::setInAttackRange(bool value)
{
    InAttackRange = value;
}

void BattleMapComp::setHarm(bool value)
{
    Harm = value;
}

void BattleMapComp::setHinder(bool value)
{
    Hinder = value;
}

int BattleMapComp::getObstacle() const
{
    return Obstacle;
}

bool BattleMapComp::getOccupied() const
{
    return Occupied;
}

bool BattleMapComp::getInMoveRange() const
{
    return InMoveRange;
}

bool BattleMapComp::getInAttackRange() const
{
    return InAttackRange;
}

int BattleMapComp::x() const
{
    return xpos;
}

int BattleMapComp::y() const
{
    return ypos;
}

qreal BattleMapComp::getLen() const
{
    return m_len;
}

bool BattleMapComp::getHarm() const
{
    return Harm;
}

bool BattleMapComp::getHinder() const
{
    return Hinder;
}