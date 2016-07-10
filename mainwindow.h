#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <anchor.h>
#include <client.h>
#include <anchoritem.h>
#include <clientitem.h>
#include <graphicsmap.h>
#include <graphicsscene.h>
#include <serialportreader.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createSceneAndItems();

    void generateAnchorItem(Anchor anchor);

private slots:
    void loadAnchorsFromFile();
    void writeAnchorsToFile();
    void updateAnchor(Anchor anchor);
    void updateAnchorRssies(QList<Anchor> anchors);

    void updateClient(Location location);

private:
    void updateAnchorRssi(Anchor anchor);

private:
    static const QString ANCHORS_PATH;
    static const QChar SPLITER;

    Ui::MainWindow *ui;
    GraphicsMap *m_map;
    QList<Anchor> m_anchors;
    QList<AnchorItem*> m_anchorItems;
    ClientItem *m_client;
    GraphicsScene *m_scene;

    SerialPortReader *m_serialReader;
};

#endif // MAINWINDOW_H
