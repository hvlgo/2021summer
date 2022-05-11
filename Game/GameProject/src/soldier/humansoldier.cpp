#include "humansoldier.h"

HumanSoldier::HumanSoldier(int _x, int _y, qreal len, bool _player) : Soldier(_x, _y, len, _player)
{
    setLife(100);
    setMp(50);
    setDamage(20);
    setDefense(10);
    setAttackRange(2);
    setMoveRange(4);
}

QRectF HumanSoldier::boundingRect() const
{
    return QRectF(-this->getLen() * sqrt(3) / 2, -this->getLen() * sqrt(3) / 2, this->getLen() * sqrt(3), this->getLen() * sqrt(3));
}

void HumanSoldier::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QImage pix;
    QMovie * mov;
    if (this->getPlayer())
    {
        if (!this->getCanMove() && !this->getCanUseMenu())
        {
            switch (status)
            {
                case death:
                    mov = movie["humanSoldierDeath1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    return;
                case attack:
                    mov = movie["humanSoldierAttack1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    return;
                case attackLeft:
                    mov = movie["humanSoldierAttack1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    return;
            }
            pix.load(":image/image/soldier/human_.png");
            painter->drawImage(boundingRect(), pix);
            return;
        }
        else
        {
            switch (status)
            {
                case wait:
                    mov = movie["humanSoldierWait1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case choose:
                    pix.load(":image/image/soldier/human.png");
                    painter->drawImage(boundingRect(), pix);
                    break;
                case attack:
                    mov = movie["humanSoldierAttack1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case attackLeft:
                    mov = movie["humanSoldierAttack1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    break;
                case walk:
                    mov = movie["humanSoldierWalk1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case walkLeft:
                    mov = movie["humanSoldierWalk1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    break;
                case death:
                    mov = movie["humanSoldierDeath1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
            }
            return;
        }
    }
    else
    {
        switch (status)
            {
                case wait:
                    mov = movie["humanSoldierWait2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case choose:
                    pix.load(":image/image/soldier/human2.png");
                    painter->drawImage(boundingRect(), pix);
                    break;
                case attack:
                    mov = movie["humanSoldierAttack2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case attackLeft:
                    mov = movie["humanSoldierAttack2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    break;
                case walk:
                    mov = movie["humanSoldierWalk2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case walkLeft:
                    mov = movie["humanSoldierWalk2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    break;
                case death:
                    mov = movie["humanSoldierDeath2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
            }
        return;
    }

}

QPainterPath HumanSoldier::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
