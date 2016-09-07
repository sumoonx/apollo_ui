#include "location.h"

Location::Location()
    :m_x(0), m_y(0), m_z(0)
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

QString Location::toString() {
//    QString ret;
//    ret << "(x=" << x << ", y=" << y << ", z=" << z << ")";
    return QString("(%1,%2,%3)").arg(m_x).arg(m_y).arg(m_z);
//    return QString("(" + x + "," + y + "," + z + ")");
}
