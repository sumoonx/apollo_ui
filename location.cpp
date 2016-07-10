#include "location.h"

Location::Location()
{

}

Location::Location(QPointF x_y, qreal z)
    :Location(x_y.x(), x_y.y(), z)
{

}

Location::Location(qreal x, qreal y, qreal z)
    :m_x(x), m_y(y), m_z(z)
{

}

qreal Location::x()
{
    return m_x;
}

qreal Location::y()
{
    return m_y;
}

qreal Location::z()
{
    return m_z;
}

QPointF Location::point()
{
    return QPointF(m_x, m_y);
}

