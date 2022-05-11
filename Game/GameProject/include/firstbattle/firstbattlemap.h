#ifndef FIRSTBATTLEMAP_H
#define FIRSTBATTLEMAP_H

#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QQueue>
#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QPushButton>
#include "battlemapcomp.h"
#include "soldier.h"
#include "archersoldier.h"
#include "humansoldier.h"
#include "meatshieldsoldier.h"
#include "bosssoldier.h"
#include "arrow.h"
#define INF 10000
#define AttackConst 200
#define MAPWIDTH 21
#define MAPHIGHT 14
#define SOLDIERNUM 10
#define OBSTACLE 3
#define LEN 10
#define PLEN 1
#define RoundMax 30
class FirstBattleMap : public QGraphicsScene
{
    Q_OBJECT
public:
    // * this is for the round
    explicit FirstBattleMap(qreal _len = LEN);
    ~FirstBattleMap();
    virtual void initNext();
signals:
    void updateRound(int);
    void showInformation(const BattleMapComp* , const Soldier*);
    void closeInformation();
    void ShowMenu(QPointF, int, int);
    // * this is for the round
    void Victory();
    void Defeat();
    void victory();
    void defeat();
    void myRoundOver();
    void roundOver();
    void IgnoreTheEvent();
    void RecoverTheEvent();
private slots:
    void focusIn(int, int);
    void focusOut(int, int);
    // * this is for the round
    void enemyAct();
public slots:
    void stopAllSoldier();
    void CancelMove();
    void attack(int, int);
    void skill(int, int);
    void stop(int, int);
protected:
    void init();
    void removeMoveRangeInArray();
    void toJudgeMoveRange(int, int);
    void removeMoveRangeInComp();
    void removeAttackRangeInArray();
    void toJudgeAttackRange(int, int);
    void removeAttackRangeInComp();
    Soldier* findSoldier(int, int) const;
    void findWay(QPoint, QPoint);
    void removeWayInArray();
    void handleShow(int, int);
    void handleClose();
    void mousePress(int, int);
    int oddDx[6] = {-1, 0, 1, 0, -1, -1};
    int oddDy[6] = {-1, -1, 0, 1, 1, 0};
    int evenDx[6] = {0, 1, 1, 1, 0, -1};
    int evenDy[6] = {-1, -1, 0, 1, 1, 0};
    QList<QPoint> theWay;
    QList<QPoint> theDirection;
    bool moveRangeVisited[MAPWIDTH][MAPHIGHT];
    int moveRangeTakes[MAPWIDTH][MAPHIGHT];
    bool attackRangeVisited[MAPWIDTH][MAPHIGHT];
    int attackRangeTakes[MAPWIDTH][MAPHIGHT];
    bool visited[MAPWIDTH][MAPHIGHT];
    QPoint fromWho[MAPWIDTH][MAPHIGHT];
    int takes[MAPWIDTH][MAPHIGHT];
    QPointF posMap[MAPWIDTH][MAPHIGHT];
    BattleMapComp * MousePre {nullptr};
    qreal len;
    BattleMapComp * firstBattleMap[MAPWIDTH][MAPHIGHT];
    Soldier * soldier[2][SOLDIERNUM];
    QPushButton * focusButton;
    // * this is for the round
    int round {0};
    bool isMyRound {true};
    bool isMyRoundOver {false};
    bool RoundOver {false};
    bool isVictory {false};
    bool isDefeat {false};
    bool recoverAttack {false};
    QTimer * myRoundOverTimer;
    QTimer * roundOverTimer;
    QTimer * refreshTimer;
    QTimer * deathTimer;
    QTimer * winTimer;
    QTimer * loseTimer;
    int moveStep = -1;
    int Pos = -1;
    int Xpos = -1, Ypos = -1; 
    qreal thedistance[SOLDIERNUM][SOLDIERNUM];
    Soldier * EnemySoldier {nullptr}; 
    Soldier * thePlayer {nullptr};
    QPoint moveRecord[2];
    Soldier * deathSoldier {nullptr};
    Arrow * arrow  {nullptr};
    QVector<Soldier*> skillSoldier;
    QVector<int> skillRound;
    void initMyRound();
    void handleRoundOver();
    void roundStart();
    void judgeAfterOperate(bool enemyAttack = false);
    void judgeVictory();
    void judgeDefeat();
    void MyRoundOver(bool enemyAttack = false);
    int findMin(int);
    void act(Soldier *, int);
    void enemyAttack(Soldier *, Soldier*, int);
    bool judgeLeft(int, int, int);
    void handleAttack(int);
    void damageCaculate(Soldier* , int, int);
    void Attack(Soldier* , int, int, int signal = 0);
    void actNext();
    void handleMove();
    void Move(Soldier* , int, int, int, int signal = 0);
    void actFinal();
    void handleSkill(Soldier *);
    void drawForeground(QPainter * painter, const QRectF & rect) override;
    void test();
};

#endif // FIRSTBATTLEMAP_H

