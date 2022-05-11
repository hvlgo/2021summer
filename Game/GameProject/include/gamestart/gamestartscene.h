#ifndef GAMESTARTSCENE_H
#define GAMESTARTSCENE_H

#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPainter>

class GameStartScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameStartScene(QObject *parent = nullptr);
};

#endif // GAMESTARTSCENE_H
