#ifndef ANCHORITEM_H
#define ANCHORITEM_H

#include <QObject>
#include <QGraphicsItem>

#include <anchor.h>

class AnchorItem
        :public QGraphicsItem
{
public:
    AnchorItem(QGraphicsItem *parent = Q_NULLPTR);
    AnchorItem(Anchor anchor, QGraphicsItem *parent = Q_NULLPTR);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setAnchor(Anchor anchor);
    Anchor getAnchor();
    void setPoint(QPointF point);
    void setRssi(double rssi);
    bool isWithId(int id);

private:
    static const QString ANCHOR_PATH;

    Anchor m_anchor;
};

#endif // ANCHORITEM_H
