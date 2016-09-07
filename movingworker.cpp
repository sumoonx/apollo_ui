#include "movingworker.h"

MovingWorker::MovingWorker()
{

}

void MovingWorker::doWork(QList<Anchor> anchor)
{
    Location location;
    emit resultReady(location);
}
