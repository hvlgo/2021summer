#include "gamemapview.h"
#include <QGraphicsItem>
#include <QDebug>
GameMapView::GameMapView()
{

}


void GameMapView::resizeEvent(QResizeEvent *event)
{
    emit GameMapResize();
    QGraphicsView::resizeEvent(event); // then call default implementation
}

void GameMapView::drawBackground(QPainter *painter, const QRectF &rect)
{
    QImage image;
    image.load(":image/image/ui/startbackground.png");
    painter->drawImage(rect, image);
}
