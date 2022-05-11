#include "gamestartview.h"
#include "gamestartitems.h"
#include <QDebug>

#include <QGraphicsItem>

GameStartView::GameStartView()
{

}

void GameStartView::resizeEvent(QResizeEvent *event)
{
    emit GameStartResize();
    QGraphicsView::resizeEvent(event); // * then call default implementation
}

void GameStartView::drawBackground(QPainter *painter, const QRectF &rect)
{
    QImage image;
    image.load(":image/image/ui/startbackground.png");
    painter->drawImage(rect, image);
}
