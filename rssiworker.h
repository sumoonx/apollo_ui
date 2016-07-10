#ifndef RSSIWORKER_H
#define RSSIWORKER_H

#include <QObject>
#include <QList>
#include <anchor.h>

class RssiWorker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(QByteArray bytes);

signals:
    void resultReady(QList<Anchor> anchors);

public:
    RssiWorker(QObject *parent = Q_NULLPTR);

private:
    int valueOf(char c);
    int valueOfTwo(char a, char b);
};

#endif // RSSIWORKER_H
