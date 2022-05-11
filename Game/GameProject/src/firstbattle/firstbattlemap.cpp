#include "firstbattlemap.h"
#include <algorithm>
#include <cmath>
#include <QDebug>
#include <QRandomGenerator>
#include <QTime>

FirstBattleMap::FirstBattleMap(qreal _len) : len(_len)
{
    // * init the member and creat the map
    init();
}

void FirstBattleMap::initMyRound()
{
    // * init the soldier
    for (int i = 0; i < SOLDIERNUM; i++)
    {
        if (soldier[0][i]->getLife() != 0)
        {
            soldier[0][i]->setCanMove(true);
            soldier[0][i]->setCanUseMenu(true);
            soldier[0][i]->update();
        }
    }
    // * init the number annd point
    round++;
    emit updateRound(round);
    Pos = -1;
    Xpos = Ypos = -1;
    moveStep = -1;
    isMyRound = true;
    isMyRoundOver = false;
    RoundOver = false;
    EnemySoldier = nullptr;
    thePlayer = nullptr;

    // * init the array
    for (int i = 0; i < SOLDIERNUM; i++)
    {
        for (int j = 0; j < SOLDIERNUM; j++)
        {
            thedistance[i][j] = INF;
        }
    }
}

void FirstBattleMap::handleRoundOver()
{
    // * do this before roundOver
    int num = 0;
    for (int i = 0; i < skillRound.size(); i++)
    {
        if (skillRound[i] == round - 1)
        {
            Soldier * SkillSoldier = skillSoldier[i];
            if (SkillSoldier->inherits("ArcherSoldier"))
            {
                SkillSoldier->setAttackRange(SkillSoldier->getAttackRange() - 2);
            }
            else if (SkillSoldier->inherits("BossSoldier"))
            {
                SkillSoldier->setDefense(SkillSoldier->getDefense() - 10);
                SkillSoldier->setDamage(SkillSoldier->getDamage() - 10);
                SkillSoldier->setAttackRange(SkillSoldier->getAttackRange() - 1);
                SkillSoldier->setMoveRange(SkillSoldier->getMoveRange() - 1);
            }
            num++;
        }
    }
    skillRound.removeAll(round - 1);
    skillSoldier.remove(0, num);
    for (int i = 0; i < SOLDIERNUM; i++)
    {
        Soldier * MySoldier = soldier[0][i];
        if (MySoldier->getLife() == 0)
        {
            continue;
        }
        if (firstBattleMap[MySoldier->x()][MySoldier->y()]->getHarm())
        {
            MySoldier->setLife(MySoldier->getLife() - 15);
            judgeAfterOperate(true);
        }
    }
    for (int i = 0; i < SOLDIERNUM; i++)
    {
        Soldier * OtherSoldier = soldier[1][i];
        if (OtherSoldier->getLife() == 0)
        {
            continue;
        }
        if (firstBattleMap[OtherSoldier->x()][OtherSoldier->y()]->getHarm())
        {
            int life = OtherSoldier->getLife() - 15;
            if (life <= 0)
            {
                OtherSoldier->status = Soldier::Status::death;
                deathTimer->start(1000);
                OtherSoldier->setLife(0);
                firstBattleMap[OtherSoldier->x()][OtherSoldier->y()]->setOccupied(false);
                OtherSoldier->setX(-1);
                OtherSoldier->setY(-1);
                OtherSoldier->setCanMove(false);
                OtherSoldier->setCanUseMenu(false);
                OtherSoldier->setReadyToAttack(false);
                // * there may be the die animation
                deathSoldier = OtherSoldier;
            }
            OtherSoldier->setLife(life);
            judgeAfterOperate(true);
        }
    }
}

void FirstBattleMap::roundStart()
{
    // * do this when round start
    initMyRound();
    for (int i = 0; i < skillRound.size(); i++)
    {
        if (skillRound[i] == round - 1)
        {
            Soldier * SkillSoldier = skillSoldier[i];
            if (SkillSoldier->inherits("ArcherSoldier"))
            {
                SkillSoldier->setAttackRange(SkillSoldier->getAttackRange() + 2);
            }
            else if (SkillSoldier->inherits("BossSoldier"))
            {
                SkillSoldier->setDefense(SkillSoldier->getDefense() + 10);
                SkillSoldier->setDamage(SkillSoldier->getDamage() + 10);
                SkillSoldier->setAttackRange(SkillSoldier->getAttackRange() + 1);
                SkillSoldier->setMoveRange(SkillSoldier->getMoveRange() + 1);
            }
        }
    }
}

void FirstBattleMap::judgeAfterOperate(bool enemyAttack)
{
    // * judge if win or defeat or myround Over
    judgeVictory();
    judgeDefeat();
    MyRoundOver(enemyAttack);
}

void FirstBattleMap::judgeVictory()
{
    // * judge if win
    for (int i = 0; i < SOLDIERNUM; i++)
    {
        if (soldier[1][i]->getLife() != 0)
            return;
    }
    emit victory();
    return;
}

void FirstBattleMap::judgeDefeat()
{
    // * judge if defeat
    if (round > RoundMax)
    {
        emit defeat();
        return;
    }
    for (int i = 0; i < SOLDIERNUM; i++)
    {
        if (soldier[0][i]->getLife() != 0)
            return;
    }
    emit defeat();
    return;
}

void FirstBattleMap::MyRoundOver(bool enemyAttack)
{
    // * judge if my round over
    if (enemyAttack)
    {
        return;
    }
    for (int i = 0; i < SOLDIERNUM; i++)
    {
        if (soldier[0][i]->getCanMove() || soldier[0][i]->getCanUseMenu())
            return;
    }
    emit IgnoreTheEvent();
    isMyRoundOver = true;
    isMyRound = false;
    this->update();
    myRoundOverTimer->start(1000);
}

void FirstBattleMap::enemyAct()
{
    // * start the ai
    act(soldier[1][0], 0);
}

int FirstBattleMap::findMin(int pos)
{
    // * find the closest soldier
    int position = -1;
    int min = 1000;
    for (int i = 0; i < SOLDIERNUM; i++)
    {
        if (thedistance[pos][i] < min)
        {
            min = thedistance[pos][i];
            position = i;
        }
    }
    return position;
}

void FirstBattleMap::act(Soldier * enemySoldier, int pos)
{
    // * ai start
    Pos = pos;
    EnemySoldier = enemySoldier;
    if (enemySoldier->getLife() == 0)
    {
        if (Pos == SOLDIERNUM - 1) 
        {
            removeWayInArray();
            emit IgnoreTheEvent();
            RoundOver = true;
            this->update();
            roundOverTimer->start(1000);
            return;
        }
        act(soldier[1][Pos + 1], Pos + 1);
        return;
    }
    // * find the close player
    Xpos = EnemySoldier->x();
    Ypos = EnemySoldier->y();
    for (int i = 0; i < SOLDIERNUM; i++)
    {
        thePlayer = soldier[0][i];
        if (thePlayer->getLife() == 0)
        {
            thedistance[pos][i] = INF;
            continue;
        }
        findWay(QPoint(Xpos, Ypos), QPoint(thePlayer->x(), thePlayer->y()));
        thedistance[pos][i] = theWay.length();
        removeWayInArray();
    }
    thePlayer = soldier[0][findMin(Pos)];
    findWay(QPoint(Xpos, Ypos), QPoint(thePlayer->x(), thePlayer->y()));
    // * there may judge the type of the soldier

    // * try attack
    enemyAttack(enemySoldier, thePlayer, 1);
}

void FirstBattleMap::enemyAttack(Soldier * enemySoldier, Soldier * thePlayer, int signal)
{
    // * for ai attack pre judgement
    if (theDirection.length() <= enemySoldier->getAttackRange())
    {
        Attack(enemySoldier, thePlayer->x(), thePlayer->y(), signal);
        return;
    }
    if (signal == 1)
    {
        removeWayInArray();
        actNext();
        return;
    }
    if (Pos == SOLDIERNUM - 1) 
    {
        removeWayInArray();
        RoundOver = true;
        this->update();
        roundOverTimer->start(1000);
        return;
    }
    else if (signal == 2)
    {
        removeWayInArray();
        act(soldier[1][Pos + 1], Pos + 1);
        return;
    }
}

bool FirstBattleMap::judgeLeft(int xpos, int ypos, int _xpos)
{
    // * judge the soldier face's direction
    if (ypos % 2 == 0)
    {
        if (_xpos <= xpos)
            return true;
    }
    else
    {
        if (_xpos < xpos)
        return true;
    }
    return false;
}

void FirstBattleMap::handleAttack(int signal)
{
    // * do some thing after the attack
    if (isDefeat)
    {
        return;
    }
    if (signal == 0)
    {
        judgeAfterOperate();
        return;
    }
    if (Pos == SOLDIERNUM - 1) 
    {
        removeWayInArray();
        emit IgnoreTheEvent();
        RoundOver = true;
        this->update();
        roundOverTimer->start(1000);
        return;
    }
    else if (signal == 1 || signal == 2)
    {
        removeWayInArray();
        act(soldier[1][Pos + 1], Pos + 1);
        return;
    }
}

void FirstBattleMap::damageCaculate(Soldier * preSoldier, int xpos, int ypos)
{
    // * caculate the damage
    Soldier * attackedSoldier = findSoldier(xpos, ypos);
    int damage = preSoldier->getDamage() * AttackConst / (attackedSoldier->getDefense() + AttackConst);
    if (attackedSoldier->inherits("BossSoldier"))
    {
        damage *= 1.2;
    }
    int attackedSoldierLife = attackedSoldier->getLife();
    if (damage >= attackedSoldierLife)
    {
        attackedSoldier->status = Soldier::Status::death;
        deathTimer->start(1000);
        attackedSoldier->setLife(0);
        firstBattleMap[xpos][ypos]->setOccupied(false);
        attackedSoldier->setX(-1);
        attackedSoldier->setY(-1);
        attackedSoldier->setCanMove(false);
        attackedSoldier->setCanUseMenu(false);
        attackedSoldier->setReadyToAttack(false);
        // * there may be the die animation
        deathSoldier = attackedSoldier;
    }
    else
    {
        attackedSoldier->setLife(attackedSoldierLife - damage);
    }
    judgeAfterOperate(true);
}

void FirstBattleMap::Attack(Soldier* attackSoldier, int xpos, int ypos, int signal)
{
    // * ai attack
    bool mirrored = judgeLeft(attackSoldier->x(), attackSoldier->y(), xpos);
    if (mirrored)
    {
        attackSoldier->status = Soldier::Status::attackLeft;
    }
    else
    {
        attackSoldier->status = Soldier::Status::attack;
    }
    QPropertyAnimation * animation;
    if (QString(attackSoldier->metaObject()->className()) == QString("ArcherSoldier"))
    {
        arrow = new Arrow(mirrored);
        this->addItem(arrow);
        arrow->setPos(posMap[attackSoldier->x()][attackSoldier->y()]);
        animation = new QPropertyAnimation(arrow, "pos");
        animation->setDuration(1000);
        animation->setKeyValueAt(0, arrow->pos());
        animation->setKeyValueAt(1, posMap[xpos][ypos]);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else
    {
        animation = new QPropertyAnimation(attackSoldier, "pos" );
        animation->setDuration(1000);
        animation->setKeyValueAt(0, attackSoldier->pos());
        animation->setKeyValueAt(0.8, posMap[xpos][ypos]);
        animation->setKeyValueAt(1, attackSoldier->pos());
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
    connect(animation, &QPropertyAnimation::finished, [=]{  if (arrow != nullptr) { delete arrow; arrow = nullptr;} attackSoldier->status = Soldier::Status::wait; handleClose(); firstBattleMap[xpos][ypos]->clearFocus(); damageCaculate(attackSoldier, xpos, ypos); handleShow(xpos, ypos);  handleAttack(signal);});
}

void FirstBattleMap::actNext()
{
    // * try move, the end can't be occupied
    findWay(QPoint(Xpos, Ypos), QPoint(thePlayer->x(), thePlayer->y()));
    int range = EnemySoldier->getMoveRange();
    if (firstBattleMap[Xpos][Ypos]->getHinder())
    {
        range -= 1;
    }
    bool foundStep = false;
    if (range < theDirection.length())
    {
        for (int i = range; i > 0; i--)
        {
            if (firstBattleMap[theWay[i].x()][theWay[i].y()]->getOccupied())
                continue;
            foundStep = true;
            moveStep = i;
            break;
        }
        // * there can optimize in the next battle
        if (!foundStep) 
        {
            removeWayInArray();
            actFinal();
            return;
        }
    }
    else if (range >= theDirection.length())
    {
        for (int i = theDirection.length() - 1; i > 0; i--)
        {
            if (firstBattleMap[theWay[i].x()][theWay[i].y()]->getOccupied())
                continue;
            foundStep = true;
            moveStep = i;
            break;
        }
        if (!foundStep) 
        {
            removeWayInArray();
            actFinal();
            return;
        }
    }
    bool foundWay = false;
    for (int i = 0; i < moveStep; i++)
    {
        if (firstBattleMap[theWay[moveStep - i].x()][theWay[moveStep - i].y()]->getObstacle())
            continue;
        foundWay = true;
        moveStep -= i;
        break;
    }
    if (!foundWay)
    {
        removeWayInArray();
        actFinal();
        return;
    }
    Move(EnemySoldier, moveStep, thePlayer->x(), thePlayer->y(), 1);
}

void FirstBattleMap::handleMove()
{
    // * fix the change due to move
    firstBattleMap[Xpos][Ypos]->setOccupied(false);
    Xpos = theWay[moveStep].x();
    Ypos = theWay[moveStep].y();
    EnemySoldier->setX(Xpos);
    EnemySoldier->setY(Ypos);
    firstBattleMap[Xpos][Ypos]->setOccupied(true);
    removeWayInArray();
    actFinal();
    return;
}

void FirstBattleMap::Move(Soldier* moveSoldier, int moveStep, int xpos, int ypos, int signal)
{
    // * ai move
    if (judgeLeft(moveSoldier->x(), moveSoldier->y(), xpos))
    {
        moveSoldier->status = Soldier::Status::walkLeft;
    }
    else
    {
        moveSoldier->status = Soldier::Status::walk;
    }
    QSequentialAnimationGroup * group = new QSequentialAnimationGroup;
    for (int i = 0; i < moveStep; i++)
    {
        QPropertyAnimation * animation = new QPropertyAnimation(moveSoldier, "pos" );
        animation->setDuration(500);
        animation->setStartValue(posMap[theWay[i].x()][theWay[i].y()]);
        animation->setEndValue(posMap[theWay[i + 1].x()][theWay[i + 1].y()]);
        group->addAnimation(animation);
    }
    group->start(QAbstractAnimation::DeleteWhenStopped);
    moveRecord[0] = QPoint(moveSoldier->x(), moveSoldier->y());
    moveRecord[1] = QPoint(xpos, ypos);
    connect(group, &QSequentialAnimationGroup::finished, [=]{ firstBattleMap[xpos][ypos]->clearFocus(); moveSoldier->status = Soldier::Status::wait; if (signal == 1) handleMove();});
}

void FirstBattleMap::actFinal()
{
    // * attack again
    findWay(QPoint(Xpos, Ypos), QPoint(thePlayer->x(), thePlayer->y()));
    enemyAttack(EnemySoldier, thePlayer, 2);
}

void FirstBattleMap::init()
{
    // * init the button and the array
    focusButton = new QPushButton;
    focusButton->setFixedSize(5, 5);
    this->addWidget(focusButton);
    focusButton->hide();
    for (int i = 0; i < MAPWIDTH; i++)
    {
        for (int j = 0; j < MAPHIGHT; j++)
        {
            moveRangeVisited[i][j] = false;
            moveRangeTakes[i][j] = 0;
            attackRangeVisited[i][j] = false;
            attackRangeTakes[i][j] = 0;
            visited[i][j] = false;
            fromWho[i][j] = QPoint(0, 0);
            takes[i][j] = 0;
        }
    }
    // * init the posMap
    QPointF Start(0, 0), Start1(0, 0);
    QPointF dx(len * sqrt(3), 0);
    QPointF dy(0, len * 3 / 2);
    for (int i = 0; i < MAPHIGHT; i++)
    {
        for (int j = 0; j < MAPWIDTH; j++)
        {
            posMap[j][i] = Start;
            Start += dx;
        }
        Start = Start1;
        if (i % 2 == 0)
            Start -= dx / 2;
        else
            Start += dx / 2;
        Start += dy;
        Start1 = Start;
    }
    // * init the map
    for (int i = 0; i < MAPWIDTH; i++)
    {
        for (int j = 0; j < MAPHIGHT; j++)
        {
            firstBattleMap[i][j] = new BattleMapComp(i, j, len, PLEN);
            connect(firstBattleMap[i][j], &BattleMapComp::FocusIn, this, &FirstBattleMap::focusIn);
            connect(firstBattleMap[i][j], &BattleMapComp::FocusOut, this, &FirstBattleMap::focusOut);
            connect(firstBattleMap[i][j], &BattleMapComp::MousePress, this, &FirstBattleMap::mousePress);
            firstBattleMap[i][j]->setPos(posMap[i][j]);
            firstBattleMap[i][j]->setToolTip("ordinary land");
            this->addItem(firstBattleMap[i][j]);
            firstBattleMap[i][j]->installEventFilter(this);
        }
    }
    // * this is about the battle round
    myRoundOverTimer = new QTimer(this);
    roundOverTimer = new QTimer(this);
    refreshTimer = new QTimer(this);
    deathTimer = new QTimer(this);
    winTimer = new QTimer(this);
    loseTimer = new QTimer(this);
    refreshTimer->start(20);
    connect(myRoundOverTimer, &QTimer::timeout, this, [=]{ isMyRoundOver = false; this->update(); myRoundOverTimer->stop(); emit myRoundOver();});
    connect(roundOverTimer, &QTimer::timeout, this, [=]{ RoundOver = false; this->update(); roundOverTimer->stop(); handleRoundOver(); emit roundOver(); emit RecoverTheEvent();});
    connect(this, &FirstBattleMap::myRoundOver, this, &FirstBattleMap::enemyAct);
    connect(this, &FirstBattleMap::roundOver, this, [=]{ roundStart();});
    connect(this, &FirstBattleMap::victory, this, [=]{ isVictory = true; this->update(); winTimer->start(1000);});
    connect(this, &FirstBattleMap::defeat, this, [=]{ isDefeat = true; this->update(); loseTimer->start(1000);});
    connect(refreshTimer, &QTimer::timeout, this, [=]{ this->update();});
    connect(deathTimer, &QTimer::timeout, this, [=]{ deathSoldier->status = Soldier::Status::choose; deathSoldier->hide(); deathTimer->stop(); });
    connect(winTimer, &QTimer::timeout, this, [=]{ winTimer->stop(); emit Victory(); });
    connect(loseTimer, &QTimer::timeout, this, [=]{ loseTimer->stop(); emit Defeat(); });
}

void FirstBattleMap::initNext()
{
    // * init the Obstacle
    QRandomGenerator ran(QTime::currentTime().msecsSinceStartOfDay());
    QPoint ObstacleMap[44] = {
        QPoint(1, 6), QPoint(2, 7), QPoint(2, 8), QPoint(2, 4), QPoint(3, 3), QPoint(3, 2), QPoint(3, 10),
        QPoint(5, 2), QPoint(6, 2), QPoint(7, 2), QPoint(4, 10), QPoint(5, 10), QPoint(6, 10), QPoint(7, 10), QPoint(7, 7), QPoint(8, 3),
        QPoint(8, 4), QPoint(8, 7), QPoint(8, 8), QPoint(9, 5), QPoint(9, 9), QPoint(9, 10), QPoint(11, 6), QPoint(12, 5), QPoint(2, 7), QPoint(12, 8),
        QPoint(12, 4), QPoint(13, 9), QPoint(13, 2), QPoint(13, 10), QPoint(14, 2), QPoint(15, 2), QPoint(16, 2), QPoint(17, 2),
        QPoint(15, 10), QPoint(16, 10), QPoint(17, 10), QPoint(15, 7), QPoint(15, 6), QPoint(17, 6), QPoint(18, 6),
        QPoint(19, 6), QPoint(19, 7), QPoint(18, 8)
    };
    for (int i = 0; i < 44; i++)
    {
        int select = ran.generate() % 3 + 1;
        firstBattleMap[ObstacleMap[i].x()][ObstacleMap[i].y()]->setObstacle(select);
    }
    // * init the soldier
    QPoint SoldierMap[2][SOLDIERNUM] = { {QPoint(1, 5), QPoint(3, 4), QPoint(3, 6), QPoint(3, 8), QPoint(5, 4), QPoint(5, 6), QPoint(5, 8), QPoint(7, 3), QPoint(7, 5), QPoint(7, 9)},
    {QPoint(13, 5), QPoint(13, 7), QPoint(14, 6), QPoint(15, 4), QPoint(15, 9), QPoint(16, 6), QPoint(17, 4), QPoint(18, 5), QPoint(18, 7), QPoint(17, 8)}};
    for (int i = 0; i < SOLDIERNUM * 2; i++)
    {
        if (i < SOLDIERNUM)
        {
            int x = SoldierMap[0][i].x();
            int y = SoldierMap[0][i].y();
            if (i < 4)  soldier[0][i] = new ArcherSoldier(x, y, len, true);
            else if (i < 7) soldier[0][i] = new HumanSoldier(x, y, len, true);
            else soldier[0][i] = new MeatShieldSoldier(x, y, len, true);
            soldier[0][i]->setPos(posMap[x][y]);
            this->addItem(soldier[0][i]);
            soldier[0][i]->setPlayer(true);
            soldier[0][i]->setZValue(1);
            firstBattleMap[x][y]->setOccupied(true);
        }
        else
        {
            int j = i - SOLDIERNUM;
            int x = SoldierMap[1][j].x();
            int y = SoldierMap[1][j].y();
            if (j < 2) soldier[1][j] = new MeatShieldSoldier(x, y, len,false);
            else if (j < 5) soldier[1][j] = new HumanSoldier(x, y, len, false);
            else if (j == 5) soldier[1][j] = new BossSoldier(x, y, len, false);
            else soldier[1][j] = new ArcherSoldier(x, y, len, false);
            soldier[1][j]->setPos(posMap[x][y]);
            this->addItem(soldier[1][j]);
            soldier[1][j]->setPlayer(false);
            soldier[1][j]->setCanMove(false);
            soldier[1][j]->setCanUseMenu(false);
            soldier[1][j]->setZValue(1);
            firstBattleMap[x][y]->setOccupied(true);
        }
    }// ! this need to be random after completing the way algorithm
    initMyRound();
    //test();
}

void FirstBattleMap::handleShow(int xpos, int ypos)
{
    // * show the side
    BattleMapComp * obj = firstBattleMap[xpos][ypos];
    Soldier * soldier = findSoldier(xpos, ypos);
    emit showInformation(obj, soldier);
}

void FirstBattleMap::handleClose()
{
    // * close the side
    emit closeInformation();
}

void FirstBattleMap::removeMoveRangeInArray()
{
    // * remove inrange in order to use again
    for (int i = 0; i < MAPWIDTH; i++)
    {
        for (int j = 0; j < MAPHIGHT; j++)
        {
            moveRangeTakes[i][j] = 0;
            moveRangeVisited[i][j] = false;
        }
    }
}

void FirstBattleMap::toJudgeMoveRange(int xpos, int ypos)
{
    // * judge in move range or not
    int range = -1;
    Soldier * moveSoldier;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < SOLDIERNUM; j++)
        {
            if (soldier[i][j]->x() == xpos && soldier[i][j]->y() == ypos)
            {
                range = soldier[i][j]->getMoveRange();
                moveSoldier = soldier[i][j];
            }
        }
    }
    if (firstBattleMap[xpos][ypos]->getHinder())
    {
        range -= 1;
    }

    QPoint start = QPoint(xpos, ypos);
    moveRangeVisited[start.x()][start.y()] = true;
    moveRangeTakes[start.x()][start.y()] = 0;
    QQueue<QPoint> que;
    que.push_back(start);
    while (!que.empty())
    {
        QPoint u = que.front();
        que.pop_front();
        int x = u.x();
        int y = u.y();

        if (moveRangeTakes[x][y] == range)
        {
            removeMoveRangeInArray();
            return;
        }
        for (int i = 0; i < 6; i++)
        {
            int newx;
            int newy;
            if (y % 2 == 0)
            {
                newx = x + evenDx[i];
                newy = y + evenDy[i];
                
            }
            else
            {
                newx = x + oddDx[i];
                newy = y + oddDy[i];
            }
            
            if (newx < 0 || newy < 0 || newx >= MAPWIDTH || newy >= MAPHIGHT)
                continue;
            if (moveRangeVisited[newx][newy])
                continue;
            if (moveSoldier->inherits("HumanSoldier"))
            {
                if (firstBattleMap[newx][newy]->getObstacle() != 2 && firstBattleMap[newx][newy]->getObstacle() != 0)
                    continue;
            }
            else if (moveSoldier->inherits("MeatShieldSoldier"))
            {
                if (firstBattleMap[newx][newy]->getObstacle() != 1 && firstBattleMap[newx][newy]->getObstacle() != 0)
                    continue;
            }
            else
            {
                if (firstBattleMap[newx][newy]->getObstacle())
                    continue;
            }
            moveRangeVisited[newx][newy] = true;
            moveRangeTakes[newx][newy] = moveRangeTakes[x][y] + 1;
            if (!firstBattleMap[newx][newy]->getObstacle())
            {
                firstBattleMap[newx][newy]->setInMoveRange(true);
            }
            firstBattleMap[newx][newy]->update();
            que.push_back(QPoint(newx, newy));
        }
    }
}

void FirstBattleMap::removeMoveRangeInComp()
{
    // * remove all range in order to next judge
    for (int i = 0; i < MAPWIDTH; i++)
    {
        for (int j = 0; j < MAPHIGHT; j++)
        {
            firstBattleMap[i][j]->setInMoveRange(false);
            firstBattleMap[i][j]->update();
        }
    }
}

void FirstBattleMap::removeAttackRangeInArray()
{
    // * remove inrange in order to use again
    for (int i = 0; i < MAPWIDTH; i++)
    {
        for (int j = 0; j < MAPHIGHT; j++)
        {
            attackRangeTakes[i][j] = 0;
            attackRangeVisited[i][j] = false;
        }
    }
}

void FirstBattleMap::toJudgeAttackRange(int xpos, int ypos)
{
    // * get the attack range and the selected soldier
    int range = -1;
    Soldier * selected = nullptr;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < SOLDIERNUM; j++)
        {
            if (soldier[i][j]->x() == xpos && soldier[i][j]->y() == ypos)
                {
                    range = soldier[i][j]->getAttackRange();
                    selected = soldier[i][j];
                }
        }
    }
    // * judge the type of the soldier and select the way of judge attack range
    if (selected->inherits("ArcherSoldier"))
    {
        for (int i = 0; i < MAPWIDTH; i++)
        {
            for (int j = 0; j < MAPHIGHT; j++)
            {
                QPointF start = firstBattleMap[xpos][ypos]->pos();
                QPointF end = firstBattleMap[i][j]->pos();
                if (pow(start.x() - end.x(), 2) + pow(start.y() - end.y(), 2) <= 3 * pow(len * range, 2) + 3)
                    {
                        firstBattleMap[i][j]->setInAttackRange(true);
                        firstBattleMap[i][j]->update();
                    }
            }
        }
    }
    else
    {
        QPoint start = QPoint(xpos, ypos);
        attackRangeVisited[start.x()][start.y()] = true;
        attackRangeTakes[start.x()][start.y()] = 0;
        QQueue<QPoint> que;
        que.push_back(start);
        while (!que.empty())
        {
            QPoint u = que.front();
            que.pop_front();
            int x = u.x();
            int y = u.y();

            if (attackRangeTakes[x][y] == range)
            {
                removeAttackRangeInArray();
                return;
            }
            for (int i = 0; i < 6; i++)
            {
                int newx;
                int newy;
                if (y % 2 == 0)
                {
                    newx = x + evenDx[i];
                    newy = y + evenDy[i];
                    
                }
                else
                {
                    newx = x + oddDx[i];
                    newy = y + oddDy[i];
                }
                
                if (newx < 0 || newy < 0 || newx >= MAPWIDTH || newy >= MAPHIGHT)
                    continue;
                if (attackRangeVisited[newx][newy])
                    continue;
                if (selected->inherits("HumanSoldier"))
                {
                    if (firstBattleMap[newx][newy]->getObstacle() != 2 && firstBattleMap[newx][newy]->getObstacle() != 0)
                        continue;
                }
                else if (selected->inherits("MeatShieldSoldier"))
                {
                    if (firstBattleMap[newx][newy]->getObstacle() != 1 && firstBattleMap[newx][newy]->getObstacle() != 0)
                        continue;
                }
                else
                {
                    if (firstBattleMap[newx][newy]->getObstacle())
                        continue;
                }
                attackRangeVisited[newx][newy] = true;
                attackRangeTakes[newx][newy] = attackRangeTakes[x][y] + 1;
                if (!firstBattleMap[newx][newy]->getObstacle())
                {
                    firstBattleMap[newx][newy]->setInAttackRange(true);
                }
                firstBattleMap[newx][newy]->update();
                que.push_back(QPoint(newx, newy));
            }
        }
    }
}

void FirstBattleMap::removeAttackRangeInComp()
{
    // * remove all range in order to next judge
    for (int i = 0; i < MAPWIDTH; i++)
    {
        for (int j = 0; j < MAPHIGHT; j++)
        {
            firstBattleMap[i][j]->setInAttackRange(false);
            firstBattleMap[i][j]->update();
        }
    }
}

void FirstBattleMap::findWay(QPoint start, QPoint end)
{
    // * bfs to find the right way to the end
    Soldier * findWaySoldier = findSoldier(start.x(), start.y());
    QQueue<QPoint> que;
    visited[start.x()][start.y()] = true;
    takes[start.x()][start.y()] = 0;
    que.push_back(start);

    while (!que.empty())
    {
        QPoint u = que.front();
        que.pop_front();
        int x = u.x();
        int y = u.y();

        if (x == end.x() && y == end.y())
        {
            while(u != start)
            {
                theWay.push_front(u);
                QPoint newu = fromWho[u.x()][u.y()];
                theDirection.push_front(newu - u);
                u = newu;
            }
            theWay.push_front(u);
            return;
        }

        for (int i = 0; i < 6; i++)
        {
            int newx;
            int newy;
            if (y % 2 == 0)
            {
                newx = x + evenDx[i];
                newy = y + evenDy[i];
                
            }
            else
            {
                newx = x + oddDx[i];
                newy = y + oddDy[i];
            }
            
            if (newx < 0 || newy < 0 || newx >= MAPWIDTH || newy >= MAPHIGHT)
                continue;
            if (visited[newx][newy])
                continue;
            if (findWaySoldier->inherits("HumanSoldier"))
            {
                if (firstBattleMap[newx][newy]->getObstacle() != 2 && firstBattleMap[newx][newy]->getObstacle() != 0)
                    continue;
            }
            else if (findWaySoldier->inherits("MeatShieldSoldier"))
            {
                if (firstBattleMap[newx][newy]->getObstacle() != 1 && firstBattleMap[newx][newy]->getObstacle() != 0)
                    continue;
            }
            else
            {
                if (firstBattleMap[newx][newy]->getObstacle())
                    continue;
            }
            takes[newx][newy] = takes[x][y] + 1;
            visited[newx][newy] = true;
            fromWho[newx][newy] = u;
            que.push_back(QPoint(newx, newy));
        }
    }
}

void FirstBattleMap::removeWayInArray()
{
    // * remove the way in order to use again
    theWay.clear();
    theDirection.clear();
    for (int i = 0; i < MAPWIDTH; i++)
    {
        for (int j = 0; j < MAPHIGHT; j++)
        {
            visited[i][j] = false;
            fromWho[i][j] = QPoint(0, 0);
            takes[i][j] = 0;
        }
    }
}

Soldier* FirstBattleMap::findSoldier(int xpos, int ypos) const
{
    // * use to xpos and ypos in map to find the soldier on it
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < SOLDIERNUM; j++)
        {
            if (soldier[i][j]->x() == xpos && soldier[i][j]->y() == ypos)
                return soldier[i][j];
        }
    }
    return nullptr;
}

void FirstBattleMap::focusIn(int xpos, int ypos)
{
    // * show and other things when focus in
    handleClose();
    handleShow(xpos, ypos);
    if (firstBattleMap[xpos][ypos]->getObstacle())
        return;
    if (firstBattleMap[xpos][ypos]->getOccupied() && (MousePre == nullptr || !findSoldier(MousePre->x(), MousePre->y())->getReadyToAttack()))
    {
        Soldier * soldier = findSoldier(xpos, ypos);
        soldier->status = Soldier::Status::choose;
        if (soldier->getPlayer())
        {
            if (soldier->getCanMove())
            toJudgeMoveRange(xpos, ypos);
            if (soldier->getCanUseMenu())
            toJudgeAttackRange(xpos, ypos);
        }
        else
        {
            toJudgeMoveRange(xpos, ypos);
            toJudgeAttackRange(xpos, ypos);
        }
    }
    firstBattleMap[xpos][ypos]->update();
}

void FirstBattleMap::focusOut(int xpos, int ypos)
{
    // * close and other thinds when focus out
    handleClose();
    if (firstBattleMap[xpos][ypos]->getObstacle())
        return;
    if (firstBattleMap[xpos][ypos]->getOccupied())
    {
        Soldier * soldier = findSoldier(xpos, ypos);
        soldier->status = Soldier::Status::wait;
        removeMoveRangeInComp();
        removeAttackRangeInComp();
    }
    firstBattleMap[xpos][ypos]->update();
}

void FirstBattleMap::mousePress(int xpos, int ypos)
{
    judgeAfterOperate();
    // * judge if the first time to click, and record
    if (MousePre == nullptr && !firstBattleMap[xpos][ypos]->getOccupied())
    {
        return;
    }
    if (MousePre == nullptr && firstBattleMap[xpos][ypos]->getOccupied())
    {
        MousePre = firstBattleMap[xpos][ypos];
        return;
    }
    Soldier *  preSoldier = findSoldier(MousePre->x(), MousePre->y());

    // * judge the second click
    if (!firstBattleMap[xpos][ypos]->getOccupied())
    {
        if (preSoldier->getReadyToAttack())
        {
            preSoldier->setReadyToAttack(false);
            MousePre = nullptr;
            return;
        }
        // * judge the move ability
        if (!preSoldier->getCanMove())
        {
            MousePre = nullptr;
            return;
        }
        // * judge the move range 
        toJudgeMoveRange(MousePre->x(), MousePre->y());
        if (!firstBattleMap[xpos][ypos]->getInMoveRange())
        {
            removeMoveRangeInComp();
            MousePre = nullptr;
            QMessageBox error;
            error.setText(tr("不在移动范围内"));
            error.exec();
            this->focusButton->click();
            return;
        }
        removeMoveRangeInComp();

        // * move and the animation
        findWay(QPoint(MousePre->x(), MousePre->y()), QPoint(xpos, ypos));
        Move(preSoldier, theDirection.length(), xpos, ypos);

        // * fix the change due to move
        removeWayInArray();
        preSoldier->setX(xpos);
        preSoldier->setY(ypos);
        preSoldier->setCanMove(false);
        preSoldier->update();
        MousePre->setOccupied(false);
        firstBattleMap[xpos][ypos]->setOccupied(true);
        MousePre = nullptr;
    }
    else if (firstBattleMap[xpos][ypos]->getOccupied() && (MousePre->x() != xpos || MousePre->y() != ypos))
    {
        if (!preSoldier->getReadyToAttack())
        {
            MousePre = nullptr;
            return;
        }
        else
        {
            // * judge the camp
            if (findSoldier(xpos, ypos)->getPlayer())
            {
                MousePre = nullptr;
                return;
            }
            // * judge the attack range
            toJudgeAttackRange(MousePre->x(), MousePre->y());
            if (!firstBattleMap[xpos][ypos]->getInAttackRange())
            {
                removeAttackRangeInComp();
                MousePre = nullptr;
                QMessageBox error;
                error.setText(tr("不在攻击范围内"));
                error.exec();
                this->focusButton->click();
                return;
            }
            removeAttackRangeInComp();
            
            Attack(preSoldier, xpos, ypos);
            
            // * fix the change due to attack
            preSoldier->setCanMove(false);
            preSoldier->setCanUseMenu(false);
            preSoldier->update();
            preSoldier->setReadyToAttack(false);
            MousePre = nullptr;
            return;
        }
    }
    else if (xpos == MousePre->x() && ypos == MousePre->y())
    {
        // * judge the attack ability
        if (!preSoldier->getCanUseMenu())
        {
            MousePre = nullptr;
            return;
        }
        if (preSoldier->getReadyToAttack())
        {
            MousePre = nullptr;
            preSoldier->setReadyToAttack(false);
            return;
        }
        emit ShowMenu(posMap[xpos][ypos], xpos, ypos);
        return;
    }
}

void FirstBattleMap::attack(int xpos, int ypos)
{
    // * attack in menu
    removeMoveRangeInComp();
    Soldier* soldier = findSoldier(xpos, ypos);
    soldier->setReadyToAttack(true);
    this->focusButton->click();
}

void FirstBattleMap::handleSkill(Soldier * SkillSoldier)
{
    // * do some thing after use skill and attack or stop
    removeMoveRangeInComp();
    removeAttackRangeInComp();
    SkillSoldier->setCanMove(false);
    SkillSoldier->setCanUseMenu(false);
    SkillSoldier->update();
    MousePre = nullptr;
    this->focusButton->click();
    judgeAfterOperate();
    return;
}

void FirstBattleMap::skill(int xpos, int ypos)
{
    // * skill in menu
    Soldier * SkillSoldier = findSoldier(xpos, ypos);
    int mp = SkillSoldier->getMp() - 6;
    if (mp < 0) return;
    SkillSoldier->setMp(mp);

    if (SkillSoldier->inherits("HumanSoldier"))
    {
        int life = SkillSoldier->getLife() + 30;
        if (life >= 100) life = 100;
        SkillSoldier->setLife(life);
        handleClose();
        handleShow(xpos, ypos);
        handleSkill(SkillSoldier);
        return;
    }
    else if (SkillSoldier->inherits("MeatShieldSoldier"))
    {
        SkillSoldier->setDefense(SkillSoldier->getDefense() + 4);
        handleClose();
        handleShow(xpos, ypos);
        handleSkill(SkillSoldier);
        return;
    }
    handleClose();
    handleShow(xpos, ypos);
    skillSoldier.push_back(SkillSoldier);
    skillRound.push_back(round);
    handleSkill(SkillSoldier);
}

void FirstBattleMap::stop(int xpos, int ypos)
{
    // * stop in menu
    Soldier* soldier = findSoldier(xpos, ypos);
    handleSkill(soldier);
}

void FirstBattleMap::drawForeground(QPainter * painter, const QRectF & rect)
{
    // * handle the foreground change
    if (isMyRoundOver)
    {
        QImage image;
        image.load(":/image/image/ui/myRoundOver.png");
        painter->drawImage(rect, image);
    }
    if (RoundOver)
    {
        QImage image;
        image.load(":/image/image/ui/roundOver.png");
        painter->drawImage(rect, image);
    }
    if (isVictory)
    {
        QImage image;
        image.load(":/image/image/ui/victory.png");
        painter->drawImage(rect, image);
    }
    if (isDefeat)
    {
        QImage image;
        image.load(":/image/image/ui/defeat.png");
        painter->drawImage(rect, image);
    }
    return;
}

void FirstBattleMap::stopAllSoldier()
{
    // * the stop myround button
    if (isMyRound == true)
    {
        for (int i = 0; i < SOLDIERNUM; i++)
        {
            soldier[0][i]->setCanMove(false);
            soldier[0][i]->setCanUseMenu(false);
            soldier[0][i]->update();
        }
        judgeAfterOperate();
    }
}

void FirstBattleMap::CancelMove()
{
    // * the cancel move button
    if (moveRecord[0] == QPoint(-1, -1) && moveRecord[1] == QPoint(-1, -1))
        return;
    Soldier * cancelSoldier = findSoldier(moveRecord[1].x(), moveRecord[1].y());
    if (!cancelSoldier->getCanMove() && cancelSoldier->getCanUseMenu())
    {
        cancelSoldier->setPos(posMap[moveRecord[0].x()][moveRecord[0].y()]);
        cancelSoldier->setCanMove(true);
        firstBattleMap[moveRecord[1].x()][moveRecord[1].y()]->setOccupied(false);
        cancelSoldier->setX(moveRecord[0].x());
        cancelSoldier->setY(moveRecord[0].y());
        firstBattleMap[moveRecord[0].x()][moveRecord[0].y()]->setOccupied(true);
        cancelSoldier->update();
        moveRecord[0] = QPoint(-1, -1);
        moveRecord[1] = QPoint(-1, -1);
        MousePre = nullptr;
        return;
    }
}

FirstBattleMap::~FirstBattleMap()
{
    for (int i = 0; i < MAPWIDTH; i++)
    {
        for (int j = 0; j < MAPHIGHT; j++)
        {
            firstBattleMap[i][j]->deleteLater();
        }
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < SOLDIERNUM; j++)
        {
            soldier[i][j]->deleteLater();
        }
    }
    if (focusButton != nullptr)
    {
        delete focusButton;
        delete focusButton;
    }
    if (myRoundOverTimer != nullptr)
    {
        delete myRoundOverTimer;
        myRoundOverTimer = nullptr;
    }
    if (roundOverTimer != nullptr)
    {
        delete roundOverTimer;
        roundOverTimer = nullptr;
    }
    if (refreshTimer != nullptr)
    {
        delete refreshTimer;
        refreshTimer = nullptr;
    }
    if (deathTimer != nullptr)
    {
        delete deathTimer;
        deathTimer = nullptr;
    }
    if (arrow != nullptr)
    {
        delete arrow;
        arrow = nullptr;
    }
}


void FirstBattleMap::test()
{
    // * only for test
    for (int i = 0; i < SOLDIERNUM; i++)
    {
        soldier[0][i]->setLife(1);
    }
}
