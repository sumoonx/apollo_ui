#include "graphicsscene.h"

#include <QDebug>

GraphicsScene::GraphicsScene(QObject *parent)
    :QGraphicsScene(parent)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);

    createMapAndItems();
}
GraphicsScene::~GraphicsScene()
{
    clearAnchors();
    delete m_map;
}

void GraphicsScene::createMapAndItems(){
    if (m_map == nullptr) m_map = new GraphicsMap();
    if (m_clientItem == nullptr) m_clientItem = new ClientItem();
}

void GraphicsScene::clearAnchors()
{
    for (AnchorItem *item : m_anchorItems) {
        delete item;
    }
}

void GraphicsScene::createAnchorsSlot(QList<Anchor> anchors)
{
//    clearAnchors();
//    for(Anchor anchor : anchors){
//        AnchorItem* item = new AnchorItem(anchor.getLocation());
//        m_anchorItems.insert(anchor.getId(), item);
//    }
}

void GraphicsScene::updateAnchorSlot(Anchor anchor)
{
    if (m_anchorItems.contains(anchor.getId()))
    {
        AnchorItem* item = m_anchorItems.value(anchor.getId());
        item->setPoint(anchor.getLocation().point());
    } else {
        qDebug() << "no AnchorItem is founded with id: " << anchor.getId();
    }
}


void GraphicsScene::updateClientSlot(QPointF location)
{
    m_clientItem->setPoint(location);
}


