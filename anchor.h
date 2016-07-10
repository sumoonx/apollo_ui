#ifndef ANCHOR_H
#define ANCHOR_H

#include <location.h>

class Anchor
{
public:
    Anchor();   //empty default
    Anchor(int id, double rssi);
    Anchor(int id, qreal x, qreal y, qreal z);
    Anchor(int id, Location location);

    void setId(int id);
    void setLocation(Location location);
    void setRssi(double rssi);

    int getId();
    Location getLocation();
    QPointF getPoint();
    qreal getHeight();
    double getRssi();

    bool isEmpty();

private:
    static const int EMPTY_ID = 0;

    int m_id;
    Location m_location;
    double m_rssi;
};

#endif // ANCHOR_H
