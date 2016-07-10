#include "rssiworker.h"

#include <QDebug>

RssiWorker::RssiWorker(QObject *parent)
    :QObject(parent)
{

}

void RssiWorker::doWork(QByteArray bytes)
{
    int lenght = 2*bytes.size();
    if (lenght < 6)   return;
    int anchors[16] = {0};
    int cnt[16] = {0};
    char *data = bytes.toHex().data();
    char tail,lrssi, urssi, leid, head;
    for (int i = 6; i < lenght; ++i) {
        tail = data[i-1];
        lrssi = data[i-3];
        urssi = data[i-4];
        leid = data[i-5];
        head = data[i-6];
        if (valueOf(tail) == 15 && valueOf(head) == 15) {
            int id = valueOf(leid);
            anchors[id] += valueOfTwo(urssi, lrssi);
            cnt[id]++;
            i = i + 5;
        }
    }

    QList<Anchor> ret;

    qDebug() << "Received Rssi info:";
    for (int i = 1; i < 16; ++i) {
        if (cnt[i] != 0) {
            Anchor anchor(i, anchors[i]/cnt[i]*0.004);
            ret.append(anchor);
            qDebug() << "Anchor id: " << i
                     << "with RSSI: " << anchors[i]
                     << "with cnt: " << cnt[i];
        }
    }
    emit resultReady(ret);
}

int RssiWorker::valueOf(char c)
{
    if (c >= '0' && c <= '9')   return c - '0';
    if (c >= 'a' && c <= 'f')   return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')   return c - 'A' + 10;
    return 0;
}

int RssiWorker::valueOfTwo(char a, char b)
{
    return valueOf(a)*16 + valueOf(b);
}

