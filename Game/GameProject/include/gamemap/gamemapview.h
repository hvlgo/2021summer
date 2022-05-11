#ifndef GAMEMAPVIEW_H
#define GAMEMAPVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
class GameMapView : public QGraphicsView
{
    Q_OBJECT
public:
    GameMapView();
signals:
    void GameMapResize();
protected:
    void resizeEvent(QResizeEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};

#endif // GAMEMAPVIEW_H
