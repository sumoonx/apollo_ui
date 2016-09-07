#ifndef SERIALPORTREADER_H
#define SERIALPORTREADER_H

#include <QObject>
#include <QByteArray>
#include <QTimer>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <anchor.h>
#include <rssiworker.h>

class SerialPortReader : public QObject
{
    Q_OBJECT

public:
    SerialPortReader(QObject *parent = Q_NULLPTR);
    ~SerialPortReader();

    bool open();

signals:
    void dataArrived(QByteArray bytes);
    void rssiObtained(QList<Anchor> anchors);

private slots:
    void handleReadyRead();
    void handleTimeout();
    void handleError(QSerialPort::SerialPortError error);
    void handleRssi(QList<Anchor> anchors);

private:
    static const QString SERIALPORT_NAME;
    static const int TIMEOUT = 500;

    QSerialPort *m_serialPort;
    QByteArray  m_readData;
    QTimer      m_timer;

    RssiWorker *worker;
    QThread m_workerThread;
};

#endif // SERIALPORTREADER_H
