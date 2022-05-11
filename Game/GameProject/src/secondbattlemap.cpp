#include "secondbattlemap.h"

SecondBattleMap::SecondBattleMap() : FirstBattleMap()
{
}

void SecondBattleMap::initNext()
{
    QRandomGenerator ran(QTime::currentTime().msecsSinceStartOfDay());
    QPoint ObstacleMap[30] = {
        QPoint(4, 2), QPoint(4, 3), QPoint(3, 4), QPoint(2, 6), QPoint(2, 7), QPoint(1, 8), QPoint(1, 10), QPoint(2, 10), QPoint(3, 10), QPoint(5, 10),
        QPoint(6, 10), QPoint(7, 10), QPoint(9, 10), QPoint(10, 10), QPoint(11, 10), QPoint(13, 10), QPoint(14, 10), QPoint(15, 10),
        QPoint(12, 2), QPoint(12, 3), QPoint(11, 4), QPoint(10, 6), QPoint(10, 7), QPoint(9, 8), 
        QPoint(19, 2), QPoint(19, 3), QPoint(18, 4), QPoint(17, 6), QPoint(17, 7), QPoint(16, 8),
    };
    for (int i = 0; i < 30; i++)
    {
        int select = ran.generate() % 3 + 1;
        firstBattleMap[ObstacleMap[i].x()][ObstacleMap[i].y()]->setObstacle(select);
    }
    for (int i = 0; i < 8; i++)
    {
        firstBattleMap[HinterMap[i].x()][HinterMap[i].y()]->setHinder(true);
    }
    for (int i = 0; i < 8; i++)
    {
        firstBattleMap[HarmMap[i].x()][HarmMap[i].y()]->setHarm(true);
    }
    // * init the soldier
    QPoint SoldierMap[2][SOLDIERNUM] = { {QPoint(1, 0), QPoint(0, 2), QPoint(5, 1), QPoint(0, 4), QPoint(2, 5), QPoint(5, 3), QPoint(3, 9), QPoint(4, 7), QPoint(5, 5), QPoint(6, 3)},
    {QPoint(12, 12), QPoint(19, 5), QPoint(19, 7), QPoint(16, 10), QPoint(14, 12), QPoint(14, 8), QPoint(15, 7), QPoint(20, 9), QPoint(18, 10), QPoint(17, 12)}};
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
            else if (j < 7) soldier[1][j] = new BossSoldier(x, y, len, false);
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
    //test();
    return;
}


SecondBattleMap::~SecondBattleMap()
{

}