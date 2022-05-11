#ifndef SOLDIER_H
#define SOLDIER_H

#include <QGraphicsObject>
#include <QPainter>
#include <QPoint>
#include <QPolygonF>
#include <QColor>
#include <QMouseEvent>
#include <cmath>
#include <QMovie>
#include <QMap>
#include <QLabel>


class Soldier : public QGraphicsObject
{
    Q_OBJECT
public:
    Soldier(int _x, int _y, qreal len, bool _player);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget) override;
    QPainterPath shape() const override;
    QRectF getBounding() const;
    enum Status {wait, choose, attack, attackLeft, walk, walkLeft, death} status;

    void setPlayer(bool);
    void setLife(int);
    void setMp(int);
    void setDamage(int);
    void setDefense(int);
    void setAttackRange(int);
    void setMoveRange(int);
    void setCanMove(bool);
    void setCanUseMenu(bool);
    void setX(int);
    void setY(int);
    void setReadyToAttack(bool);
    bool getPlayer() const;
    int getLife() const;
    int getMp() const;
    int getDamage() const;
    int getDefense() const;
    int getAttackRange() const;
    int getMoveRange() const;
    bool getCanMove() const;
    bool getCanUseMenu() const;
    qreal getLen() const;
    int x() const;
    int y() const;
    bool getReadyToAttack() const;
private:
    int xpos, ypos;
    qreal m_len;
    bool player;
    int lifeValue;
    int mp;
    int damage;
    int defense;
    int attackRange;
    int moveRange;
    bool canMove {true};
    bool canUseMenu {true};
    bool readyToAttack {false};
protected:
    QMap<QString, QMovie*> movie;
    QLabel * label;
};

#endif // SOLDIER_H
