#include "clientitem.h"

#include <graphicsmap.h>
#include <qdebug.h>
#include <QGraphicsScene>

ClientItem::ClientItem(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    m_flash = true;
    setFlag(ItemIsMovable);
    setZValue(1);
    startTimer(FLASH_INTERVAL);
}

QRectF ClientItem::boundingRect() const
{
    return QRectF(-5, -5, 10, 10);
}

void ClientItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-5, -5, 10, 10);

    painter->setPen(QPen(Qt::black, 0));
    painter->setBrush(m_flash ? Qt::red : Qt::yellow);
    painter->drawEllipse(-5, -5, 10, 10);

    QString location = m_location.toString();

    qDebug() << "location of this client: " << location;
    QFont font("Times");
    font.setPixelSize(18);
    painter->setFont(font);
    painter->drawText(QRectF(10, -5, 100, 20), Qt::AlignCenter, location);
}

void ClientItem::timerEvent(QTimerEvent *)
{
    m_flash = !m_flash;
    update();
}

void ClientItem::setLocation(Location location) {
    m_location = location;
    setPoint(m_location.point());
    QRectF rect(scenePos().x()+10, scenePos().y()-5, 100, 20);
    scene()->update(rect);
}

void ClientItem::setPoint(QPointF pos)
{
    QPointF location = QPointF(pos.x()*1000 + GraphicsMap::EDGE,
                               -pos.y()*1000 + GraphicsMap::HEIGHT - GraphicsMap::EDGE);
    setPos(location);
}

