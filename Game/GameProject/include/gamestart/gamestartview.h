#ifndef GAMESTARTVIEW_H
#define GAMESTARTVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QImage>

class GameStartView : public QGraphicsView
{
    Q_OBJECT
public:
    GameStartView();
    void drawBackground(QPainter *painter, const QRectF &rect) override;
signals:
    void GameStartResize();
protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // GAMESTARTVIEW_H
