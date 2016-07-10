#ifndef GRAPHICSMAP_H
#define GRAPHICSMAP_H

#include <QObject>
#include <QGraphicsItem>

class GraphicsMap
        :public QGraphicsItem
{
public:
    GraphicsMap(QGraphicsItem *parent = Q_NULLPTR);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    static const qreal EDGE;
    static const qreal WIDTH;
    static const qreal HEIGHT;
private:
    static const QString MAP_PATH;
};

#endif // GRAPHICSMAP_H
