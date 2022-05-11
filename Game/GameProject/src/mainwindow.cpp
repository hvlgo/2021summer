#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // * to set the basic information of the window
    this->setWindowTitle(tr("Game"));
    this->setWindowIcon(QIcon(":/image/image/ui/icon.jpg"));

    QString musicList[5] = {QString("qrc:/audio/Audio/used/startmusic.wav"), QString("qrc:/audio/Audio/used/mapmusic.wav"),
    QString("qrc:/audio/Audio/used/firstbattlemusic.wav"), QString("qrc:/audio/Audio/used/secondbattlemusic.wav"), QString("qrc:/audio/Audio/used/coursemusic.wav"), };
    for (int i = 0; i < 5; i++)
    {
        player[i] = new QMediaPlayer;
        playList[i] = new QMediaPlaylist;
        playList[i]->addMedia(QUrl(musicList[i]));
        playList[i]->setPlaybackMode(QMediaPlaylist::Loop);
        player[i]->setPlaylist(playList[i]);
    }
    
    // * to set the extrance of the start interface and enter
    
    connect(this, &MainWindow::GameExtrance, this, [=]{ gameExtrance();});
    gameExtrance();
}


void MainWindow::gameExtrance()
{
    player[0]->play();
    // * to init the start interface or load the interface
    startWindow = new QWidget;
    startButton = new StartButton(true);
    courseButton = new StartButton(false);
    startScene = new GameStartScene;
    startScene->addItem(startButton);
    startButton->setPos(0, -40);
    startScene->addItem(courseButton);
    courseButton->setPos(0, 40);
    startView = new GameStartView;
    startView->setScene(startScene);
    startLayout = new QHBoxLayout;
    startLayout->addWidget(startView);
    startWindow->setLayout(startLayout);
    this->setCentralWidget(startWindow);

    // * to set the extrance of the map interface and connect the signals and slots relate to the start interface
    connect(this, &MainWindow::GameMap, [=]{ gameMap(); });
    connect(this, &MainWindow::Course, this, [=]{ course(); });
    connect(startButton, &StartButton::startButtonPressed, this, [=]{ startWindow->deleteLater(); startWindow = nullptr; player[0]->stop(); emit GameMap(); });
    connect(courseButton, &StartButton::startButtonPressed, this, [=]{ startWindow->deleteLater(); startWindow = nullptr; player[0]->stop(); emit Course(); });
    connect(startView, &GameStartView::GameStartResize, this, [=]{ startView->fitInView(QRectF(0, 0, 900, 700), Qt::KeepAspectRatio);} );
}

void MainWindow::course()
{
    player[4]->play();
    courseInterface = new CourseInterface();
    connect(courseInterface, &CourseInterface::outCourse, this, [=]{ courseInterface->deleteLater(); courseInterface = nullptr; player[4]->stop(); gameExtrance();});
    this->setCentralWidget(courseInterface);
}

void MainWindow::gameMap()
{
    player[1]->play();
    // * to init the map interface or load the interface
    mapWindow = new QWidget;
    firstBattleGate = new FirstBattleGate(1);
    secondBattleGate = new FirstBattleGate(2);
    mapScene = new GameMapScene;
    mapScene->addItem(firstBattleGate);
    mapScene->addItem(secondBattleGate);
    firstBattleGate->setPos(0, -25);
    secondBattleGate->setPos(0, 35);
    if (!firstWin)
    {
        secondBattleGate->hide();
    }
    mapView = new GameMapView;
    mapView->setScene(mapScene);
    mapLayout = new QHBoxLayout;
    mapLayout->addWidget(mapView);
    mapWindow->setLayout(mapLayout);
    this->setCentralWidget(mapWindow);
    // * to set the extrance of the firstBattle interface and connect the signals and slots relate to the map interface
    connect(this, &MainWindow::FirstBattle, this, [=]{ firstBattle(); });
    connect(this, &MainWindow::SecondBattle, this, [=]{ secondBattle();});
    connect(firstBattleGate, &FirstBattleGate::firstButtonPressed, this, [=]{  mapWindow->deleteLater(); mapWindow = nullptr; player[1]->stop(); emit FirstBattle(); });
    connect(secondBattleGate, &FirstBattleGate::firstButtonPressed, this, [=]{ mapWindow->deleteLater(); mapWindow = nullptr; player[1]->stop(); emit SecondBattle();});
    connect(mapView, &GameMapView::GameMapResize, this, [=]{ mapView->fitInView(QRectF(0, 0, 900, 700), Qt::KeepAspectRatio); } );
}

void MainWindow::firstBattle()
{
    player[2]->play();
    // * to init the firstBattle interface of load the interface
    firstBattleWindow = new QWidget;
    firstBattleMap = new FirstBattleMap();
    firstBattleMap->initNext();
    firstBattleView = new FirstBattleView();
    firstBattleView->setScene(firstBattleMap);
    firstBattleView->setFocusPolicy(Qt::ClickFocus);
    roundLabel = new QLabel(roundInfo.arg(1));
    sideScene = new SideScene();
    sideView = new FirstBattleView();
    sideView->setScene(sideScene);
    sideView->setFocusPolicy(Qt::NoFocus);
    myRoundOver = new QPushButton;
    myRoundOver->setText("结束我方回合");
    cancelMove = new QPushButton;
    cancelMove->setText("撤销移动");
    backToMap = new QPushButton;
    backToMap->setText("返回地图");
    Exit = new QPushButton;
    Exit->setText("退出游戏");
    buttonLayout = new QGridLayout();
    buttonLayout->addWidget(myRoundOver, 0, 0);
    buttonLayout->addWidget(cancelMove, 0, 1);
    buttonLayout->addWidget(backToMap, 1, 0);
    buttonLayout->addWidget(Exit, 1, 1);
    firstBattleLayout = new QGridLayout();
    firstBattleLayout->setColumnStretch(0, 3);
    firstBattleLayout->setColumnStretch(1, 1);
    firstBattleLayout->setRowStretch(0, 1);
    firstBattleLayout->setRowStretch(1, 20);
    firstBattleLayout->setRowStretch(2, 1);
    firstBattleLayout->addWidget(firstBattleView, 0, 0, 3, 1);
    firstBattleLayout->addWidget(roundLabel, 0, 1, 1, 1);
    firstBattleLayout->addWidget(sideView, 1, 1, 1, 1);
    firstBattleLayout->addLayout(buttonLayout, 2, 1, 1, 1);
    firstBattleWindow->setLayout(firstBattleLayout);
    this->setCentralWidget(firstBattleWindow);

    // * connect the signals and slots relate to the firstBattle interface 
    // ! need to add judge success and fail
    connect(firstBattleMap, &FirstBattleMap::Victory, this, [=] { firstWin = true;  player[2]->stop(); firstBattleWindow->deleteLater(); firstBattleWindow = nullptr; emit GameMap(); });
    connect(firstBattleMap, &FirstBattleMap::Defeat, this, [=] { firstWin = false;  player[2]->stop(); firstBattleWindow->deleteLater(); firstBattleWindow = nullptr; emit GameMap(); });
    connect(firstBattleMap, &FirstBattleMap::updateRound, this, [=](int x) { roundLabel->setText(roundInfo.arg(x)); });
    connect(myRoundOver, &QPushButton::clicked, firstBattleMap, &FirstBattleMap::stopAllSoldier);
    connect(cancelMove, &QPushButton::clicked, firstBattleMap, &FirstBattleMap::CancelMove);
    connect(backToMap, &QPushButton::clicked, this, [=]{ firstBattleWindow->deleteLater(); firstBattleWindow = nullptr;  player[2]->stop(); emit GameMap(); });
    connect(Exit, &QPushButton::clicked, this, []{ QApplication::quit(); });
    connect(firstBattleMap, &FirstBattleMap::showInformation, sideScene, &SideScene::display);
    connect(firstBattleMap, &FirstBattleMap::closeInformation, sideScene, &SideScene::close);
    connect(firstBattleMap, &FirstBattleMap::ShowMenu, firstBattleView, &FirstBattleView::showMenu);
    connect(firstBattleMap, &FirstBattleMap::IgnoreTheEvent, firstBattleView, &FirstBattleView::ignoreTheEvent);
    connect(firstBattleMap, &FirstBattleMap::RecoverTheEvent, firstBattleView, &FirstBattleView::recoverTheEvent);
    connect(firstBattleView, &FirstBattleView::Attack, firstBattleMap, &FirstBattleMap::attack);
    connect(firstBattleView, &FirstBattleView::Skill, firstBattleMap, &FirstBattleMap::skill);
    connect(firstBattleView, &FirstBattleView::Stop, firstBattleMap, &FirstBattleMap::stop);
    connect(firstBattleView, &FirstBattleView::FirstBattleResize, this, [=]{ firstBattleView->fitInView( firstBattleMap->itemsBoundingRect(), Qt::KeepAspectRatio);} );
    connect(sideView, &FirstBattleView::FirstBattleResize, this, [=]{ sideView->fitInView( sideScene->itemsBoundingRect(), Qt::KeepAspectRatio);} );
}

void MainWindow::secondBattle()
{
    player[3]->play();
    // * to init the secondBattle interface of load the interface
    secondBattleWindow = new QWidget;
    secondBattleMap = new SecondBattleMap();
    secondBattleMap->initNext();
    secondBattleView = new FirstBattleView();
    secondBattleView->setScene(secondBattleMap);
    secondBattleView->setFocusPolicy(Qt::ClickFocus);
    secondLabel = new QLabel(secondInfo.arg(1));
    secondSideScene = new SideScene();
    secondSideView = new FirstBattleView();
    secondSideView->setScene(secondSideScene);
    secondSideView->setFocusPolicy(Qt::NoFocus);
    secondMyRoundOver = new QPushButton;
    secondMyRoundOver->setText("结束我方回合");
    secondCancelMove = new QPushButton;
    secondCancelMove->setText("撤销移动");
    secondBackToMap = new QPushButton;
    secondBackToMap->setText("返回地图");
    secondExit = new QPushButton;
    secondExit->setText("退出游戏");
    secondButtonLayout = new QGridLayout();
    secondButtonLayout->addWidget(secondMyRoundOver, 0, 0);
    secondButtonLayout->addWidget(secondCancelMove, 0, 1);
    secondButtonLayout->addWidget(secondBackToMap, 1, 0);
    secondButtonLayout->addWidget(secondExit, 1, 1);
    secondBattleLayout = new QGridLayout();
    secondBattleLayout->setColumnStretch(0, 3);
    secondBattleLayout->setColumnStretch(1, 1);
    secondBattleLayout->setRowStretch(0, 1);
    secondBattleLayout->setRowStretch(1, 20);
    secondBattleLayout->setRowStretch(2, 1);
    secondBattleLayout->addWidget(secondBattleView, 0, 0, 3, 1);
    secondBattleLayout->addWidget(secondLabel, 0, 1, 1, 1);
    secondBattleLayout->addWidget(secondSideView, 1, 1, 1, 1);
    secondBattleLayout->addLayout(secondButtonLayout, 2, 1, 1, 1);
    secondBattleWindow->setLayout(secondBattleLayout);
    this->setCentralWidget(secondBattleWindow);

    // * connect the signals and slots relate to the secondBattle interface 
    // ! need to add judge success and fail
    connect(secondBattleMap, &SecondBattleMap::Victory, this, [=] { secondWin = true; player[3]->stop(); emit GameMap(); });
    connect(secondBattleMap, &SecondBattleMap::Defeat, this, [=] { secondWin = false; player[3]->stop(); emit GameMap(); });
    connect(secondBattleMap, &SecondBattleMap::updateRound, this, [=](int x) { secondLabel->setText(secondInfo.arg(x)); });
    connect(secondMyRoundOver, &QPushButton::clicked, secondBattleMap, &SecondBattleMap::stopAllSoldier);
    connect(secondCancelMove, &QPushButton::clicked, secondBattleMap, &SecondBattleMap::CancelMove);
    connect(secondBackToMap, &QPushButton::clicked, this, [=]{ secondBattleWindow->deleteLater(); secondBattleWindow = nullptr;  player[3]->stop(); emit GameMap(); });
    connect(secondExit, &QPushButton::clicked, this, []{ QApplication::quit(); });
    connect(secondBattleMap, &SecondBattleMap::showInformation, secondSideScene, &SideScene::display);
    connect(secondBattleMap, &SecondBattleMap::closeInformation, secondSideScene, &SideScene::close);
    connect(secondBattleMap, &SecondBattleMap::ShowMenu, secondBattleView, &FirstBattleView::showMenu);
    connect(secondBattleMap, &SecondBattleMap::IgnoreTheEvent, secondBattleView, &FirstBattleView::ignoreTheEvent);
    connect(secondBattleMap, &SecondBattleMap::RecoverTheEvent, secondBattleView, &FirstBattleView::recoverTheEvent);
    connect(secondBattleView, &FirstBattleView::Attack, secondBattleMap, &SecondBattleMap::attack);
    connect(secondBattleView, &FirstBattleView::Skill, secondBattleMap, &SecondBattleMap::skill);
    connect(secondBattleView, &FirstBattleView::Stop, secondBattleMap, &SecondBattleMap::stop);
    connect(secondBattleView, &FirstBattleView::FirstBattleResize, this, [=]{ secondBattleView->fitInView( secondBattleMap->itemsBoundingRect(), Qt::KeepAspectRatio);} );
    connect(secondSideView, &FirstBattleView::FirstBattleResize, this, [=]{ secondSideView->fitInView( secondSideScene->itemsBoundingRect(), Qt::KeepAspectRatio);} );

}

MainWindow::~MainWindow()
{
    // * this is in the gamestart
    if (startWindow != nullptr)
    {
        startWindow->deleteLater();
    } 
    // * this is in the course
    if (courseInterface != nullptr)
    {
        courseInterface->deleteLater();
    }
    // * this is in the map
    if (mapWindow != nullptr)
    {
        mapWindow->deleteLater();
    }

    // * this is in the firstBattle
    if (firstBattleWindow != nullptr)
    {
        firstBattleWindow->deleteLater();
    } 

    for (int i = 0; i < 4; i++)
    {
        player[i]->deleteLater();
        playList[i]->deleteLater();
    }
    delete ui;
}

