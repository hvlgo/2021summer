#ifndef SIDESCENE_H
#define SIDESCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsObject>
#include <QPainter>
#include <QLabel>
#include <QGroupBox>
#include <QFormLayout>
#include <QMetaClassInfo>
#include "battlemapcomp.h"
#include "soldier.h"
#include "firstbattlemap.h"

class SideScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SideScene(QObject *parent = nullptr);
    ~SideScene();
public slots:
    void display(const BattleMapComp *, const Soldier *);
    void close();
private:
    QGroupBox * totalBox {nullptr};
    QVBoxLayout *layout;
    BattleMapComp * mapComp;
    QLabel * mapInfo;
    QGroupBox * mapBox;
    QHBoxLayout * mapLayout;
    QGraphicsView * mapView;
    QGraphicsScene * mapScene;

    Soldier * soldierEx;
    QLabel * soldierInfo;
    QGroupBox * soldierBox;
    QHBoxLayout * soldierLayout;
    QGraphicsView * soldierView;
    QGraphicsScene * soldierScene;
};

#endif // SIDESCENE_H
