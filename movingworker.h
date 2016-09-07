#ifndef MOVINGWORKER_H
#define MOVINGWORKER_H

#include <positioningworker.h>

class MovingWorker : public PositioningWorker
{

public:
    MovingWorker();

public slots:
    void doWork(QList<Anchor> anchor);
};

#endif // MOVINGWORKER_H
