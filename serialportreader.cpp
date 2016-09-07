#include "serialportreader.h"

#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <rssiworker.h>

const QString SerialPortReader::SERIALPORT_NAME = "ttyUSB0";

SerialPortReader::SerialPortReader(QObject *parent)
    :QObject(parent)
{
    worker = new RssiWorker();
    worker->moveToThread(&m_workerThread);
    connect(&m_workerThread, SIGNAL(finished()),
            worker, SLOT(deleteLater()));
    connect(this, SIGNAL(dataArrived(QByteArray)), worker, SLOT(doWork(QByteArray)));
    connect(worker, SIGNAL(resultReady(QList<Anchor>)), this, SLOT(handleRssi(QList<Anchor>)));
    m_workerThread.start();
}

SerialPortReader::~SerialPortReader()
{
    delete worker;
    m_workerThread.quit();
    m_workerThread.wait();
}

bool SerialPortReader::open()
{
    m_serialPort = new QSerialPort(SERIALPORT_NAME, this);
    bool ret = m_serialPort->open(QIODevice::ReadOnly);
    if (ret) {
        m_serialPort->setBaudRate(QSerialPort::Baud115200);
        m_serialPort->setDataBits(QSerialPort::Data8);
        m_serialPort->setParity(QSerialPort::NoParity);
        m_serialPort->setStopBits(QSerialPort::OneStop);
        m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

        m_serialPort->clearError();
        m_serialPort->clear();

        connect(m_serialPort, &QSerialPort::readyRead,
                this, &SerialPortReader::handleReadyRead);
        connect(m_serialPort, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
                this, &SerialPortReader::handleError);
        connect(&m_timer, &QTimer::timeout, this, &SerialPortReader::handleTimeout);

        m_timer.start(TIMEOUT);
    }
    return ret;
    //return false;
}

void SerialPortReader::handleReadyRead()
{
    m_readData.append(m_serialPort->readAll());

    if (!m_timer.isActive())
        m_timer.start(TIMEOUT);
}

void SerialPortReader::handleTimeout()
{
    if (m_readData.isEmpty()) {
        qDebug() << QObject::tr("No data was currently available for reading from port %1").arg(m_serialPort->portName()) << endl;
    } else {
        emit(dataArrived(m_readData));
        //qDebug() << m_readData.toHex();
        m_readData.clear();
    }
}

void SerialPortReader::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        qDebug() << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
    }
}

void SerialPortReader::handleRssi(QList<Anchor> anchors)
{
    qDebug() << "Rssi receied in Serial port";
    emit rssiObtained(anchors);
}
