#include "anchor.h"

Anchor::Anchor()
    :m_id(EMPTY_ID)
{

}

Anchor::Anchor(int id, double rssi)
    :m_id(id), m_rssi(rssi)
{

}

Anchor::Anchor(int id, qreal x, qreal y, qreal z)
    :m_id(id), m_location(Location(x, y, z))
{

}

Anchor::Anchor(int id, Location location)
    :m_id(id), m_location(location)
{

}

void Anchor::setId(int id)
{
    m_id = id;
}

void Anchor::setLocation(Location location)
{
    m_location = location;
}

void Anchor::setRssi(double rssi)
{
    m_rssi = rssi;
}

int Anchor::getId()
{
    return m_id;
}

Location Anchor::getLocation()
{
    return m_location;
}

QPointF Anchor::getPoint()
{
    return m_location.point();
}

qreal Anchor::getHeight()
{
    return m_location.z();
}

double Anchor::getRssi()
{
    return m_rssi;
}

bool Anchor::isEmpty()
{
    return m_id == 0;
}
