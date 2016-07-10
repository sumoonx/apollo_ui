#include "graphicsmap.h"

#include <QPainter>

const qreal GraphicsMap::EDGE = 25;
const qreal GraphicsMap::WIDTH = 800;
const qreal GraphicsMap::HEIGHT = 700;

const QString GraphicsMap::MAP_PATH = ":/resources/maps/map3.png";

GraphicsMap::GraphicsMap(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{

}

QRectF GraphicsMap::boundingRect() const
{
    return QRectF(0, 0, WIDTH, HEIGHT);
}

void GraphicsMap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QLineF lines[16];
    for (int i = 0; i < 16; ++i) {
        lines[i].setP1(QPointF(EDGE + i*2*EDGE, 0));
        lines[i].setP2(QPointF(EDGE + i*2*EDGE, 700));
    }
    painter->drawLines(lines, 16);
    for (int i = 0; i < 14; ++i) {
        lines[i].setP1(QPointF(0, EDGE + i*2*EDGE));
        lines[i].setP2(QPointF(800, EDGE + i*2*EDGE));
    }
    painter->drawLines(lines, 14);
}

