#include "arrow.h"
#include <cmath>

Arrow::Arrow(bool _mirrored)
{
    mirrored = _mirrored;
}

QRectF Arrow::boundingRect() const
{
    return QRectF(- LENGTH * sqrt(3) / 2 - 5, - LENGTH * sqrt(3) / 2, LENGTH * sqrt(3) + 10, LENGTH * sqrt(3));
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QImage image;
    image.load(":image/image/ui/arrow.png");
    if (!mirrored)
    {
        painter->drawImage(boundingRect(), image);
    }
    else
    {
        painter->drawImage(boundingRect(), image.mirrored(true, false));
    }
}
