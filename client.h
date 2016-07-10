#ifndef CLIENT_H
#define CLIENT_H

#include <QPointF>

class Client
{
public:
    Client(int id, QPointF location);

    void setId(int id);
    void setLocation(QPointF location);

    int getId();
    QPointF getLocation();

private:
    int m_id;
    QPointF m_location;
};

#endif // CLIENT_H
