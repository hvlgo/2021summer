#include "firstbattleview.h"
#include <QGraphicsItem>
#include <QDebug>
FirstBattleView::FirstBattleView()
{

}

void FirstBattleView::resizeEvent(QResizeEvent *event)
{
    emit FirstBattleResize();
    QGraphicsView::resizeEvent(event); // then call default implementation
}

void FirstBattleView::showMenu(QPointF posFromScene, int xpos, int ypos)
{
    menu = new QMenu;
    QPixmap pixFirst;
    QPixmap pixSecond;
    QPixmap pixThird;
    QPixmap pixFourth;
    pixFirst.load(":image/image/ui/attack.png");
    pixSecond.load(":image/image/ui/skill.png");
    pixThird.load(":image/image/ui/stop.png");
    pixFourth.load(":image/image/ui/back.png");
    QIcon iconFirst;
    QIcon iconSecond;
    QIcon iconThird;
    QIcon iconFourth;
    iconFirst.addPixmap(pixFirst);
    iconSecond.addPixmap(pixSecond);
    iconThird.addPixmap(pixThird);
    iconFourth.addPixmap(pixFourth);
    QAction * attackAction = menu->addAction(iconFirst, "攻击");
    QAction * skillAction = menu->addAction(iconSecond, "技能");
    QAction * stopAction = menu->addAction(iconThird, "待命");
    QAction * backAction = menu->addAction(iconFourth, "返回");
    QPointF posFromView = mapFromScene(posFromScene);
    const QPoint pos = QPoint(posFromView.x(), posFromView.y());
    menu->popup(mapToGlobal(pos));
    connect(attackAction, &QAction::triggered, this, [=]{ emit Attack(xpos, ypos); delete menu; });
    connect(skillAction, &QAction::triggered, this, [=]{ emit Skill(xpos, ypos); delete menu; });
    connect(stopAction, &QAction::triggered, this, [=] { emit Stop(xpos, ypos); delete menu;});
    connect(backAction, &QAction::triggered, this, [=] { menu->close(); delete menu;});
}

void FirstBattleView::ignoreTheEvent()
{
    this->setEnabled(false);
}

void FirstBattleView::recoverTheEvent()
{
    this->setEnabled(true);
}


