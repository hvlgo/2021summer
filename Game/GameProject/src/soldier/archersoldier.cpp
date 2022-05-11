#include "archersoldier.h"

ArcherSoldier::ArcherSoldier(int _x, int _y, qreal len, bool _player) : Soldier(_x, _y, len, _player)
{
    setLife(90);
    setMp(50);
    setDamage(18);
    setDefense(8);
    setAttackRange(5);
    setMoveRange(2);
}

QRectF ArcherSoldier::boundingRect() const
{
    return QRectF(-this->getLen() * sqrt(3) / 2, -this->getLen() * sqrt(3) / 2, this->getLen() * sqrt(3), this->getLen() * sqrt(3));
}

void ArcherSoldier::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
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
                    mov = movie["ArcherSoldierDeath1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    return;
                case attack:
                    mov = movie["ArcherSoldierAttack1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    return;
                case attackLeft:
                    mov = movie["ArcherSoldierAttack1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    return;
            }
            pix.load(":image/image/soldier/FantasyArcher_03_Attack1_0211_.png");
            painter->drawImage(boundingRect(), pix);
            return;
        }
        else
        {
            switch (status)
            {
                case wait:
                    mov = movie["ArcherSoldierWait1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case choose:
                    pix.load(":image/image/soldier/FantasyArcher_03_Attack1_0211.png");
                    painter->drawImage(boundingRect(), pix);
                    break;
                case attack:
                    mov = movie["ArcherSoldierAttack1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case attackLeft:
                    mov = movie["ArcherSoldierAttack1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    break;
                case walk:
                    mov = movie["ArcherSoldierWalk1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case walkLeft:
                    mov = movie["ArcherSoldierWalk1"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    break;
                case death:
                    mov = movie["ArcherSoldierDeath1"];
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
                    mov = movie["ArcherSoldierWait2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case choose:
                    pix.load(":image/image/soldier/FantasyArcher_02_Attack1_0211.png");
                    painter->drawImage(boundingRect(), pix);
                    break;
                case attack:
                    mov = movie["ArcherSoldierAttack2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case attackLeft:
                    mov = movie["ArcherSoldierAttack2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    break;
                case walk:
                    mov = movie["ArcherSoldierWalk2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
                case walkLeft:
                    mov = movie["ArcherSoldierWalk2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage().mirrored(true, false));
                    break;
                case death:
                    mov = movie["ArcherSoldierDeath2"];
                    label->setMovie(mov);
                    mov->start();
                    painter->drawImage(boundingRect(), mov->currentImage());
                    break;
            }
        return;
    }

}

QPainterPath ArcherSoldier::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
