#include "anchoritem.h"

#include <QPainter>
#include <graphicsmap.h>
#include <QDebug>
#include <QGraphicsScene>

const QString AnchorItem::ANCHOR_PATH = ":/resources/icons/anchor.png";

AnchorItem::AnchorItem(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{

}

AnchorItem::AnchorItem(Anchor anchor, QGraphicsItem *parent)
    :AnchorItem(parent)
{
    setAnchor(anchor);
}

QRectF AnchorItem::boundingRect() const
{
    return QRectF(-30, -10, 60, 30);
}

void AnchorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    static const QPointF points1[4] = {
        QPointF(-10, -10),
        QPointF(10, -10),
        QPointF(30, 10),
        QPointF(-30, 10)
    };
    QBrush bruch(Qt::yellow);     // 画刷
    painter->setBrush(bruch);            // 设置画刷
    painter->drawPolygon(points1, 4);

    static const QPointF points2[4] = {
        QPointF(-7, 10),
        QPointF(7, 10),
        QPointF(7, 15),
        QPointF(-7, 15)
    };
    painter->drawPolygon(points2, 4);

    QPen pen(Qt::black);
    QFont font("Times");
    font.setPixelSize(20);
    painter->setPen(pen);
    painter->setFont(font);
    QString id = QString::number(m_anchor.getId());
    painter->drawText(QRectF(-10, -10, 20, 20), Qt::AlignCenter, id);

    QString rssi = "*";
    if (m_anchor.getRssi() > 0.000001)
        rssi = QString::number(m_anchor.getRssi());
    qDebug() << "rssi is in item: " << m_anchor.getRssi();
    font.setPixelSize(18);
    painter->setFont(font);
    painter->drawText(QRectF(10, -30, 50, 20), Qt::AlignCenter, rssi);
}

void AnchorItem::setAnchor(Anchor anchor)
{
    if (anchor.isEmpty())
        throw QString("Anchor can not be empty!");
    else {
        m_anchor = anchor;
        setPoint(m_anchor.getLocation().point());
    }
}

void AnchorItem::setRssi(double rssi)
{
    m_anchor.setRssi(rssi);
    QRectF rect(scenePos().x()+10, scenePos().y()-30, 50, 20);
    scene()->update(rect);
//    update(QRectF(10, -30, 50, 20));
//    scene()->update();
}

Anchor AnchorItem::getAnchor()
{
    return m_anchor;
}

void AnchorItem::setPoint(QPointF point)
{
    QPointF location = QPointF(point.x()*1000 + GraphicsMap::EDGE,
                               -point.y()*1000 + GraphicsMap::HEIGHT - GraphicsMap::EDGE);
    setPos(location);
}

bool AnchorItem::isWithId(int id)
{
    return m_anchor.getId() == id;
}
