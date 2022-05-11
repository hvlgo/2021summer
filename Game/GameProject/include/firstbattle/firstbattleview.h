#ifndef FIRSTBATTLEVIEW_H
#define FIRSTBATTLEVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include "firstBattleMap.h"
class FirstBattleView : public QGraphicsView
{
    Q_OBJECT
public:
    FirstBattleView();
signals:
    void FirstBattleResize();
    void Attack(int, int);
    void Skill(int, int);
    void Stop(int, int);
public slots:
    void showMenu(QPointF, int, int);
    void ignoreTheEvent();
    void recoverTheEvent();
private:
    QMenu * menu {nullptr};
protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // FIRSTBATTLEVIEW_H
