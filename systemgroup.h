#ifndef SYSTEMGROUP_H
#define SYSTEMGROUP_H

#include <memory>

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "graphicsmodule.h"
#include "graphicscontroller.h"

enum class ModuleInterface {SPI, RS_485};

class SystemGroup : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    SystemGroup(QObject *parent = nullptr);
    ~SystemGroup();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    QRectF boundingRect() const;

    void setItemIndex(int);

    GraphicsModule* addModule(QString, ModuleInterface);

    GraphicsModule* getModule(std::size_t index)
    {
        return graphicsModuleVector.at(index).get();
    }

    GraphicsModule* getModuleBySerial(uint32_t serial)
    {
        for(auto &module : graphicsModuleVector)
        {
            if(module->getSerial() == serial)
                return module.get();
        }

        return nullptr; // be careful NOTABUG WONTFIX
    }

    QPainter *painter = new QPainter();

    std::vector<std::unique_ptr<GraphicsModule>> graphicsModuleVector;
    std::unique_ptr<GraphicsController> cntrl;
private:
    QPointF mouseCoords;
    bool noSPI = true;
    bool noRS485 = true;

    QGraphicsLineItem *lineRS1;
    QGraphicsLineItem *lineRS2;

    std::vector<std::unique_ptr<QGraphicsLineItem>> rsLines;

    QGraphicsLineItem *lineSPI1;
    QGraphicsLineItem *lineSPI2;

    std::vector<std::unique_ptr<QGraphicsLineItem>> spiLines;
    //void initPosItem(QPointF coords);
};

#endif // SYSTEMGROUP_H
