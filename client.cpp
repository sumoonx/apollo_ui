#include "client.h"

Client::Client(int id, QPointF location)
    :m_id(id), m_location(location)
{

}

void Client::setId(int id)
{
    m_id = id;
}

void Client::setLocation(QPointF location)
{
    m_location = location;
}

int Client::getId()
{
    return m_id;
}

QPointF Client::getLocation()
{
    return m_location;
}

