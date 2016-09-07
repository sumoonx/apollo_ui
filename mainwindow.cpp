#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <positioningworker.h>
#include <threedimenworker.h>

const QString MainWindow::ANCHORS_PATH = "/home/jeremy/workspace/qt/positioning/config/anchors";
const QChar MainWindow::SPLITER = ',';

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createSceneAndItems();
    m_serialReader = new SerialPortReader(this);
    connect(m_serialReader, SIGNAL(rssiObtained(QList<Anchor>)), this, SLOT(updateAnchorRssies(QList<Anchor>)));
    m_serialReader->open();

    worker = new ThreeDimenWorker();
    worker->moveToThread(&m_workerThread);
    connect(m_serialReader, SIGNAL(rssiObtained(QList<Anchor>)), worker, SLOT(doWork(QList<Anchor>)));
    connect(worker, SIGNAL(resultReady(Location)), this, SLOT(updateClient(Location)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_map;
    delete worker;
    writeAnchorsToFile();
}

void MainWindow::createSceneAndItems()
{
    m_scene = new GraphicsScene(this);
    m_map = new GraphicsMap();
    m_scene->addItem(m_map);
    m_client = new ClientItem(m_map);
    m_client->setPoint(QPointF(0, 0));
    m_scene->addItem(m_client);
    loadAnchorsFromFile();
    ui->graphicsView->setScene(m_scene);
}

void MainWindow::generateAnchorItem(Anchor anchor)
{
    AnchorItem *item = new AnchorItem(anchor, m_map);
    m_anchorItems.append(item);
    m_scene->addItem(item);
}

void MainWindow::loadAnchorsFromFile()
{
    QFile f(ANCHORS_PATH);
    if (f.open(QIODevice::ReadOnly)) {
        QTextStream in(&f);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList args = line.split(',');
            int id = args.at(0).toInt();
            double x = args.at(1).toDouble();
            double y = args.at(2).toDouble();
            double z = args.at(3).toDouble();
            if (args.size() == 4) {
                Anchor anchor = Anchor(id, x, y, z);
                qDebug() << "id: " << id
                         << "x :" << x
                         << "y: " << y
                         << "z: " << z;
                m_anchors.append(anchor);
                generateAnchorItem(anchor);
            }
        }
        f.close();
    }
}

void MainWindow::writeAnchorsToFile()
{
    QFile f(ANCHORS_PATH);
    if (f.open(QIODevice::WriteOnly)) {
        QTextStream out(&f);
        for (Anchor anchor : m_anchors) {
            out << anchor.getId() << SPLITER
                << anchor.getLocation().x() << SPLITER
                << anchor.getLocation().y() << SPLITER
                << anchor.getLocation().z() << endl;
        }
        f.close();
    }
}

void MainWindow::updateAnchor(Anchor anchor)
{
    for (Anchor an : m_anchors) {
        if (an.getId() == anchor.getId()) {
            an.setLocation(anchor.getLocation());
            break;
        }
    }

    for (AnchorItem *item : m_anchorItems) {
        if (item->isWithId(anchor.getId())) {
            item->setPoint(anchor.getLocation().point());
            break;
        }
    }
}

void MainWindow::updateAnchorRssies(QList<Anchor> anchors)
{
    qDebug() << "update anchors rssi in window";
    for (Anchor anchor : anchors) {
        updateAnchorRssi(anchor);
    }
}

void MainWindow::updateAnchorRssi(Anchor anchor)
{
    for (Anchor an : m_anchors) {
        if (an.getId() == anchor.getId()) {
            an.setRssi(anchor.getRssi());
            break;
        }
    }
    for (AnchorItem *item : m_anchorItems) {
        if (item->isWithId(anchor.getId())) {
            item->setRssi(anchor.getRssi());
            item->update();
            break;
        }
    }
}

void MainWindow::updateClient(Location location)
{
    m_client->setPoint(location.point());
}
