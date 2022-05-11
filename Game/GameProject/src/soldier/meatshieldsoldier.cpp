#include "meatshieldsoldier.h"

MeatShieldSoldier::MeatShieldSoldier(int _x, int _y, qreal len, bool _player) : Soldier(_x, _y, len, _player)
{
    setLife(250);
    setMp(40);
    setDamage(15);
    setDefense(15);
    setAttackRange(2);
    setMoveRange(2);
}

QRectF MeatShieldSoldier::boundingRect() const
{
    return QRectF(-this->getLen() * sqrt(3) / 2, -this->getLen() * sqrt(3) / 2, this->getLen() * sqrt(3), this->getLen() * sqrt(3));
}

void MeatShieldSoldier::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
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
                    mov = movie["meatShieldSoldierDeath1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    return;
                case attack:
                    mov = movie["meatShieldSoldierAttack1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    return;
                case attackLeft:
                    mov = movie["meatShieldSoldierAttack1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    return;
            }
            pix.load(":image/image/soldier/meatShield_.png");
            painter->drawImage(boundingRect(), pix);
            return;
        }
        else
        {
            switch (status)
            {
                case wait:
                    mov = movie["meatShieldSoldierWait1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case choose:
                    pix.load(":image/image/soldier/meatShield.png");
                    painter->drawImage(boundingRect(), pix);
                    break;
                case attack:
                    mov = movie["meatShieldSoldierAttack1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case attackLeft:
                    mov = movie["meatShieldSoldierAttack1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    break;
                case walk:
                    mov = movie["meatShieldSoldierWalk1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case walkLeft:
                    mov = movie["meatShieldSoldierWalk1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    break;
                case death:
                    mov = movie["meatShieldSoldierDeath1"];
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
                    pix.load(":image/image/soldier/meatShield2.png");
                    painter->drawImage(boundingRect(), pix);
                    break;
                case choose:
                    pix.load(":image/image/soldier/meatShield2.png");
                    painter->drawImage(boundingRect(), pix);
                    break;
                case attack:
                    mov = movie["meatShieldSoldierAttack2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case attackLeft:
                    mov = movie["meatShieldSoldierAttack2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    break;
                case walk:
                    mov = movie["meatShieldSoldierWalk2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case walkLeft:
                    mov = movie["meatShieldSoldierWalk2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    break;
                case death:
                    pix.load(":image/image/soldier/meatShield2Death.png");
                    painter->drawImage(boundingRect(), pix);
                    break;
            }
        return;
    }

}

QPainterPath MeatShieldSoldier::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
