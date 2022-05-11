#include "sidescene.h"
#include <QDebug>
SideScene::SideScene(QObject *parent) : QGraphicsScene(parent)
{

}

void SideScene::display(const BattleMapComp * map, const Soldier * soldier)
{
    if (!totalBox) totalBox = new QGroupBox("Info");
    layout = new QVBoxLayout();

    QString soldierInfomation;
    if (soldier != nullptr)
    {
        if (soldier->inherits("ArcherSoldier"))
        {
            QString typeName;
            if (soldier->getPlayer())
            {
                typeName = "我方弓箭手";
            }
            else
            {
                typeName = "敌方弓箭手";
            }
            QString skill = "鸟瞰 下回合攻击距离+2 Mp -6";
            QString characteristic = "远程攻击可越障碍";
            soldierEx = new ArcherSoldier(-1, -1, LEN * 3.5, soldier->getPlayer());
            soldierInfomation = QString("<p> 角色：%1 </p> <p> 生命值：%2 </p> <p> MP： %3 </p> <p> 攻击力：%4 </p> <p> 防御力：%5 </p> <p> 攻击范围：%6 </p> <p> 移动范围： %7 </p> <p> 技能：%8 </p> <p> 特点：%9 </p>")
            .arg(typeName).arg(soldier->getLife()).arg(soldier->getMp()).arg(soldier->getDamage()).arg(soldier->getDefense()).arg(soldier->getAttackRange()).arg(soldier->getMoveRange()).arg(skill).arg(characteristic);
        }
        else if (soldier->inherits("HumanSoldier"))
        {
            QString typeName;
            if (soldier->getPlayer())
            {
                typeName = "我方攀登者";
            }
            else
            {
                typeName = "敌方攀登者";
            }
            QString skill = "包扎 回复自己30生命值 Mp -6";
            QString characteristic = "攀登能手，视高山于无物";
            soldierEx = new HumanSoldier(-1, -1, LEN * 3.5, soldier->getPlayer());
            soldierInfomation = QString("<p> 角色：%1 </p> <p> 生命值：%2 </p> <p> MP： %3 </p> <p> 攻击力：%4 </p> <p> 防御力：%5 </p> <p> 攻击范围：%6 </p> <p> 移动范围： %7 </p> <p> 技能：%8 </p> <p> 特点：%9 </p>")
            .arg(typeName).arg(soldier->getLife()).arg(soldier->getMp()).arg(soldier->getDamage()).arg(soldier->getDefense()).arg(soldier->getAttackRange()).arg(soldier->getMoveRange()).arg(skill).arg(characteristic);
        }
        else if (soldier->inherits("MeatShieldSoldier"))
        {
            QString typeName;
            if (soldier->getPlayer())
            {
                typeName = "我方武术家";
            }
            else
            {
                typeName = "敌方武术家";
            }
            QString skill = "修养 防御力永久+4 Mp -6";
            QString characteristic = "皮糙肉厚，擅长游泳";
            soldierEx = new MeatShieldSoldier(-1, -1, LEN * 3.5, soldier->getPlayer());
            soldierInfomation = QString("<p> 角色：%1 </p> <p> 生命值：%2 </p> <p> MP： %3 </p> <p> 攻击力：%4 </p> <p> 防御力：%5 </p> <p> 攻击范围：%6 </p> <p> 移动范围： %7 </p> <p> 技能：%8 </p> <p> 特点：%9 </p>")
            .arg(typeName).arg(soldier->getLife()).arg(soldier->getMp()).arg(soldier->getDamage()).arg(soldier->getDefense()).arg(soldier->getAttackRange()).arg(soldier->getMoveRange()).arg(skill).arg(characteristic);
        }
        else if (soldier->inherits("BossSoldier"))
        {
            QString typeName = "??";
            QString skill = "狂暴 下一回合攻击防御上升10移动攻击范围增加1 Mp -6";
            QString characteristic = "天生神力，攻击附带额外20%伤害";
            soldierEx = new BossSoldier(-1, -1, LEN * 3.5, soldier->getPlayer());
            soldierInfomation = QString("<p> BOSS：%1 </p> <p> 生命值：%2 </p> <p> MP： %3 </p> <p> 攻击力：%4 </p> <p> 防御力：%5 </p> <p> 攻击范围：%6 </p> <p> 移动范围： %7 </p> <p> 技能：%8 </p> <p> 特点：%9 </p>")
            .arg(typeName).arg(soldier->getLife()).arg(soldier->getMp()).arg(soldier->getDamage()).arg(soldier->getDefense()).arg(soldier->getAttackRange()).arg(soldier->getMoveRange()).arg(skill).arg(characteristic);
        }
        // ! there should judge the type of soldier in the future
        soldierInfo = new QLabel(soldierInfomation);

        soldierScene = new QGraphicsScene;
        soldierScene->addItem(soldierEx);
        soldierView = new QGraphicsView;
        soldierView->setScene(soldierScene);
        soldierLayout = new QHBoxLayout;
        soldierLayout->addWidget(soldierView, 1);
        soldierLayout->addWidget(soldierInfo, 1);
        soldierBox = new QGroupBox("soldier");
        soldierBox->setLayout(soldierLayout);
        layout->addWidget(soldierBox);
    }

    QString mapInformation;
    mapComp = new BattleMapComp(-1, -1, LEN * 3.5, PLEN * 6);

    switch (map->getObstacle())
    {
        case 0:
            if (map->getHinder())
            {
                mapComp->setHinder(true);
                mapInformation = "<p> 地形：冬林 迟缓地形 </p> <p> 效果：从此处出发移动距离-1 </p>";
            }
            else if (map->getHarm())
            {
                mapComp->setHarm(true);
                mapInformation = "<p> 地形：火山 损伤地形 </p> <p> 效果：每停留一回合损失生命值15 </p>";
            }
            else
            {
                mapInformation = "<p> 地形：平原 普通地形 </p> <p> 效果：无 </p>";
            }
            break;
        case 1:
            mapComp->setObstacle(1);
            mapInformation = "<p> 地形：海洋 阻挡地形 </p> <p> 效果：无法到达，非远程攻击不可越过 </p>";
            break;
        case 2:
            mapComp->setObstacle(2);
            mapInformation = "<p> 地形：高山 阻挡地形 </p> <p> 效果：无法到达，非远程攻击不可越过 </p>";
            break;
        case 3:
            mapComp->setObstacle(3);
            mapInformation = "<p> 地形：城堡 阻挡地形 </p> <p> 效果：无法到达，非远程攻击不可越过 </p>";
            break;
        default:
            throw "invalid";
    }
    mapInfo = new QLabel(mapInformation);
    mapScene = new QGraphicsScene;
    mapScene->addItem(mapComp);
    mapView = new QGraphicsView;
    mapView->setScene(mapScene);
    mapLayout = new QHBoxLayout;
    mapLayout->addWidget(mapView, 1);
    mapLayout->addWidget(mapInfo, 1);
    mapBox = new QGroupBox("map");
    mapBox->setLayout(mapLayout);
    layout->addWidget(mapBox);

    totalBox->setLayout(layout);
    this->addWidget(totalBox);
}

void SideScene::close()
{
    if (totalBox != nullptr)
    {
        delete totalBox;
        totalBox = nullptr;
    }
}

SideScene::~SideScene()
{

}
