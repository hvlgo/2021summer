#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHBoxLayout>
#include <QMainWindow>
#include <QSizePolicy>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "gamestartscene.h"
#include "gamestartview.h"
#include "gamestartitems.h"
#include "gamemapscene.h"
#include "gamemapview.h"
#include "gamemapitems.h"
#include "sidescene.h"
#include "firstbattleview.h"
#include "firstbattlemap.h"
#include "battlemapcomp.h"
#include "secondbattlemap.h"
#include "courseinterface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void GameExtrance();
    void Course();
    void GameMap();
    void FirstBattle();
    void SecondBattle();
private slots:
    void gameExtrance();
    void gameMap();
    void firstBattle();
    void secondBattle();
private:
    void handlePlay();
    void course();
    void MoveStart();
    void MoveMap();
    void MoveFirstBattle();
    Ui::MainWindow *ui;
    QMediaPlaylist * playList[5];
    QMediaPlayer * player[5];

    // * this is in the gamestart
    QWidget * startWindow {nullptr};
    StartButton * startButton {nullptr};
    StartButton * courseButton {nullptr};
    GameStartScene * startScene {nullptr};
    GameStartView * startView {nullptr};
    QHBoxLayout * startLayout {nullptr};

    // * this is the course
    CourseInterface * courseInterface {nullptr};
    // * this is in the map
    QWidget * mapWindow {nullptr};
    FirstBattleGate * firstBattleGate {nullptr};
    FirstBattleGate * secondBattleGate {nullptr};
    GameMapScene * mapScene {nullptr};
    GameMapView * mapView {nullptr};
    QHBoxLayout * mapLayout {nullptr};
    bool firstWin {true}; 
    bool secondWin {false};// ! this need to change back after finish

    // * this is in the firstBattle
    QWidget * firstBattleWindow {nullptr};
    FirstBattleMap * firstBattleMap {nullptr};
    FirstBattleView * firstBattleView {nullptr};
    QString roundInfo = QString("<p> 当前回合：第 <strong> %2 </strong> 回合 </p> <p> 胜利条件：%1 回合内击败敌方所有人物 </p>").arg(30);
    QLabel * roundLabel {nullptr};
    SideScene * sideScene {nullptr};
    FirstBattleView * sideView {nullptr};
    QPushButton * myRoundOver {nullptr};
    QPushButton * cancelMove {nullptr};
    QPushButton * backToMap {nullptr};
    QPushButton * Exit {nullptr};
    QGridLayout * buttonLayout {nullptr};
    QGridLayout * firstBattleLayout {nullptr};

    // * this is in the secondBattle
    QWidget * secondBattleWindow {nullptr};
    SecondBattleMap * secondBattleMap {nullptr};
    FirstBattleView * secondBattleView {nullptr};
    QString secondInfo = QString("<p> 当前回合：第 <strong> %2 </strong> 回合 </p> <p> 胜利条件：%1 回合内击败敌方所有人物 </p>").arg(30);
    QLabel * secondLabel {nullptr};
    SideScene * secondSideScene {nullptr};
    FirstBattleView * secondSideView {nullptr};
    QPushButton * secondMyRoundOver {nullptr};
    QPushButton * secondCancelMove {nullptr};
    QPushButton * secondBackToMap {nullptr};
    QPushButton * secondExit {nullptr};
    QGridLayout * secondButtonLayout {nullptr};
    QGridLayout * secondBattleLayout {nullptr};
};


#endif // MAINWINDOW_H
