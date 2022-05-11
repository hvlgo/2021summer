#ifndef SECONDBATTLEMAP_H
#define SECONDBATTLEMAP_H
#define SECONDBATTLEMAP
#include "firstbattlemap.h"
class SecondBattleMap : public FirstBattleMap
{
    Q_OBJECT
public:
    SecondBattleMap();
    ~SecondBattleMap();
    void initNext() override;
protected:
    QPoint HinterMap[8] = {QPoint(3, 5), QPoint(1, 9), QPoint(4, 10), QPoint(9, 9), QPoint(11, 5), QPoint(12, 10), QPoint(16, 9), QPoint(18, 5)};
    QPoint HarmMap[8] = {QPoint(9, 5), QPoint(8, 4), QPoint(7, 5), QPoint(8, 7), QPoint(13, 5), QPoint(13, 4), QPoint(15, 5), QPoint(14, 7)};
};

#endif // SECONDBATTLEMAP_H
