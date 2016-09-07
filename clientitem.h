#ifndef CLIENTITEM_H
#define CLIENTITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <location.h>

class ClientItem
        : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    ClientItem(QGraphicsItem *parent = Q_NULLPTR);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void timerEvent(QTimerEvent *);

    void setLocation(Location location);
    void setPoint(QPointF point);

private:
    const int FLASH_INTERVAL = 500;

    Location m_location;

    QString m_userName;
    bool m_flash;
};

#endif // CLIENTITEM_H
