#ifndef GAMEMAPSCENE_H
#define GAMEMAPSCENE_H

#include <QGraphicsScene>

class GameMapScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameMapScene(QObject *parent = nullptr);
};

#endif // GAMEMAPSCENE_H
