#ifndef LOCATION_H
#define LOCATION_H

#include <QPointF>
#include <QString>

class Location
{
public:
    Location();
    Location(QPointF x_y, qreal z);
    Location(qreal x, qreal y, qreal z);

    qreal x();
    qreal y();
    qreal z();
    QPointF point();

    QString toString();

private:
    qreal m_x;
    qreal m_y;
    qreal m_z;
};

#endif // LOCATION_H
