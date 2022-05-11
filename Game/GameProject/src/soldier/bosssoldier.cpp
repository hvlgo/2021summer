#include "bosssoldier.h"

BossSoldier::BossSoldier(int _x, int _y, qreal len, bool _player) : Soldier(_x, _y, len, _player)
{
    setLife(300);
    setMp(50);
    setDamage(25);
    setDefense(5);
    setAttackRange(3);
    setMoveRange(2);
}

QRectF BossSoldier::boundingRect() const
{
    return QRectF(-this->getLen() * sqrt(3) / 2, -this->getLen() * sqrt(3) / 2, this->getLen() * sqrt(3), this->getLen() * sqrt(3));
}

void BossSoldier::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QImage pix;
    QMovie * mov;
    switch (status)
        {
            case wait:
                pix.load(":image/image/soldier/boss.png");
                painter->drawImage(boundingRect(), pix);
                break;
            case choose:
                pix.load(":image/image/soldier/boss.png");
                painter->drawImage(boundingRect(), pix);
                break;
            case attack:
                mov = movie["bossSoldierAttack1"];
                label->setMovie(mov);
                mov->start();
                painter->drawImage(boundingRect(), mov->currentImage());
                break;
            case attackLeft:
                mov = movie["bossSoldierAttack1"];
                label->setMovie(mov);
                mov->start();
                painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                break;
            case walk:
                mov = movie["bossSoldierWalk1"];
                label->setMovie(mov);
                mov->start();
                painter->drawImage(boundingRect(), mov->currentImage());
                break;
            case walkLeft:
                mov = movie["bossSoldierWalk1"];
                label->setMovie(mov);
                mov->start();
                painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                break;
            case death:
                mov = movie["bossSoldierDeath1"];
                label->setMovie(mov);
                mov->start();
                painter->drawImage(boundingRect(), mov->currentImage());
                break;
        }
    return;

}

QPainterPath BossSoldier::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
