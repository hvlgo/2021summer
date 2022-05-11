#include "soldier.h"

Soldier::Soldier(int _x, int _y, qreal len, bool _player) : xpos(_x), ypos(_y), m_len(len - 1), player(_player)
{
    label = new QLabel();
    movie["ArcherSoldierWait1"] = new QMovie();
    movie["ArcherSoldierAttack1"] = new QMovie();
    movie["ArcherSoldierWalk1"] = new QMovie();
    movie["ArcherSoldierDeath1"] = new QMovie();
    movie["ArcherSoldierWait2"] = new QMovie();
    movie["ArcherSoldierAttack2"] = new QMovie();
    movie["ArcherSoldierWalk2"] = new QMovie();
    movie["ArcherSoldierDeath2"] = new QMovie();
    movie["humanSoldierWait1"] = new QMovie();
    movie["humanSoldierAttack1"] = new QMovie();
    movie["humanSoldierWalk1"] = new QMovie();
    movie["humanSoldierDeath1"] = new QMovie();
    movie["humanSoldierWait2"] = new QMovie();
    movie["humanSoldierAttack2"] = new QMovie();
    movie["humanSoldierWalk2"] = new QMovie();
    movie["humanSoldierDeath2"] = new QMovie();
    movie["meatShieldSoldierWait1"] = new QMovie();
    movie["meatShieldSoldierAttack1"] = new QMovie();
    movie["meatShieldSoldierWalk1"] = new QMovie();
    movie["meatShieldSoldierDeath1"] = new QMovie();
    movie["meatShieldSoldierAttack2"] = new QMovie();
    movie["meatShieldSoldierWalk2"] = new QMovie();
    movie["bossSoldierAttack1"] = new QMovie();
    movie["bossSoldierWalk1"] = new QMovie();
    movie["bossSoldierDeath1"] = new QMovie();

    movie["ArcherSoldierWait1"]->setFileName(":/image/image/animation/wait/wait.gif");
    movie["ArcherSoldierAttack1"]->setFileName(":/image/image/animation/attack/attack.gif");
    movie["ArcherSoldierWalk1"]->setFileName(":/image/image/animation/walk/walk.gif");
    movie["ArcherSoldierDeath1"]->setFileName(":/image/image/animation/death/death.gif");
    movie["ArcherSoldierWait2"]->setFileName(":/image/image/animation/wait/wait2.gif");
    movie["ArcherSoldierAttack2"]->setFileName(":/image/image/animation/attack/attack2.gif");
    movie["ArcherSoldierWalk2"]->setFileName(":/image/image/animation/walk/walk2.gif");
    movie["ArcherSoldierDeath2"]->setFileName(":/image/image/animation/death/death2.gif");

    movie["humanSoldierWait1"]->setFileName(":/image/image/animation/wait/wait3.gif");
    movie["humanSoldierAttack1"]->setFileName(":/image/image/animation/attack/attack3.gif");
    movie["humanSoldierWalk1"]->setFileName(":/image/image/animation/walk/walk3.gif");
    movie["humanSoldierDeath1"]->setFileName(":/image/image/animation/death/death3.gif");
    movie["humanSoldierWait2"]->setFileName(":/image/image/animation/wait/wait3_.gif");
    movie["humanSoldierAttack2"]->setFileName(":/image/image/animation/attack/attack3_.gif");
    movie["humanSoldierWalk2"]->setFileName(":/image/image/animation/walk/walk3_.gif");
    movie["humanSoldierDeath2"]->setFileName(":/image/image/animation/death/death3_.gif");

    movie["meatShieldSoldierWait1"]->setFileName(":/image/image/animation/wait/wait5.gif");
    movie["meatShieldSoldierAttack1"]->setFileName(":/image/image/animation/attack/attack5.gif");
    movie["meatShieldSoldierWalk1"]->setFileName(":/image/image/animation/walk/walk5.gif");
    movie["meatShieldSoldierDeath1"]->setFileName(":/image/image/animation/death/death5.gif");

    movie["meatShieldSoldierAttack2"]->setFileName(":/image/image/animation/attack/attack4.gif");
    movie["meatShieldSoldierWalk2"]->setFileName(":/image/image/animation/walk/walk4.gif");

    movie["bossSoldierAttack1"]->setFileName(":/image/image/animation/attack/attackboss.gif");
    movie["bossSoldierWalk1"]->setFileName(":/image/image/animation/walk/walkboss.gif");
    movie["bossSoldierDeath1"]->setFileName(":/image/image/animation/death/deathboss.gif");
    status = wait;
}

QRectF Soldier::boundingRect() const
{
    return getBounding();
}

void Soldier::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QPen pen = QPen(Qt::NoPen);
    painter->setPen(pen);
    painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter->drawEllipse(-m_len * sqrt(3) / 2, -m_len * sqrt(3) / 2, m_len * sqrt(3), m_len * sqrt(3));
}

QPainterPath Soldier::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

QRectF Soldier::getBounding() const
{
    return QRectF(- m_len * sqrt(3) / 2, - m_len * sqrt(3) / 2, m_len * sqrt(3), m_len * sqrt(3));
}

void Soldier::setPlayer(bool _player)
{
    player = _player;
}

void Soldier::setLife(int life)
{
    lifeValue = life;
}

void Soldier::setMp(int _mp)
{
    mp = _mp;
}

void Soldier::setDamage(int _damage)
{
    damage = _damage;
}

void Soldier::setDefense(int _defense)
{
    defense = _defense;
}

void Soldier::setAttackRange(int _range)
{
    attackRange = _range;
}

void Soldier::setMoveRange(int _range)
{
    moveRange = _range;
}

void Soldier::setCanMove(bool _canMove)
{
    canMove = _canMove;
}

void Soldier::setCanUseMenu(bool _canUseMenu)
{
    canUseMenu = _canUseMenu;
}

void Soldier::setX(int _x)
{
    xpos = _x;
}

void Soldier::setY(int _y)
{
    ypos = _y;
}

void Soldier::setReadyToAttack(bool _readyToAttack)
{
    readyToAttack = _readyToAttack;
}

bool Soldier::getPlayer() const
{
    return player;
}

int Soldier::getLife() const
{
    return lifeValue;
}

int Soldier::getMp() const
{
    return mp;
}

int Soldier::getDamage() const
{
    return damage;
}

int Soldier::getDefense() const
{
    return defense;
}

int Soldier::getAttackRange() const
{
    return attackRange;
}

int Soldier::getMoveRange() const
{
    return moveRange;
}

bool Soldier::getCanMove() const
{
    return canMove;
}

bool Soldier::getCanUseMenu() const
{
    return canUseMenu;
}

int Soldier::x() const
{
    return xpos;
}

int Soldier::y() const
{
    return ypos;
}

qreal Soldier::getLen() const
{
    return m_len;
}

bool Soldier::getReadyToAttack() const
{
    return readyToAttack;
}
