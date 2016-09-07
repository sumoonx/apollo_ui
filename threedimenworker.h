#ifndef THREEDIMENWORKER_H
#define THREEDIMENWORKER_H

#include <positioningworker.h>
#include <location.h>

class ThreeDimenWorker : public PositioningWorker
{

public:
    ThreeDimenWorker(QObject *parent = Q_NULLPTR);

public slots:
    void doWork(QList<Anchor> anchors);

private:
    QList<Anchor> pickThree(QList<Anchor> anchors);

    Location getLocation(QList<Anchor> anchors);

private:
    static const double v0;

    static const double a;

    static const double L;
};

#endif // THREEDIMENWORKER_H
