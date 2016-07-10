#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>

#include <graphicsmap.h>
#include <anchoritem.h>
#include <clientitem.h>
#include <anchor.h>
#include <client.h>

class GraphicsScene
        :public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene(QObject *parent = Q_NULLPTR);
    ~GraphicsScene();

private:
    void createMapAndItems();
    void clearAnchors();

private slots:
    void createAnchorsSlot(QList<Anchor> anchors);
    void updateAnchorSlot(Anchor anchor);

    void updateClientSlot(QPointF location);

private:
    GraphicsMap* m_map = nullptr;
    QHash<int, AnchorItem*> m_anchorItems;
    ClientItem* m_clientItem = nullptr;
};

#endif // GRAPHICSSCENE_H
