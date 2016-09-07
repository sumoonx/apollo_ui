#ifndef POSITIONINGALGORITHM_H
#define POSITIONINGALGORITHM_H


#include <QObject>
#include <QList>
#include <location.h>
#include <anchor.h>

class PositioningWorker : public QObject
{
    Q_OBJECT

public:
    PositioningWorker(QObject *parent = Q_NULLPTR);

public slots:
    virtual void doWork(QList<Anchor> anchor) = 0;

signals:
    void resultReady(Location location);
};

#endif // POSITIONINGALGORITHM_H
