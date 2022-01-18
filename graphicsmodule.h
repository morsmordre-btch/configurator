#ifndef GRAPHICSMODULE_H
#define GRAPHICSMODULE_H

#include <graphicsitem.h>

enum class ModuleInterface {UNDEFINED, SPI, RS_485};

class GraphicsModule : public GraphicsItem
{
public:
    GraphicsModule(QString name, int x, int y);
    ~GraphicsModule();

    void setFont(QFont &);

    void createContextMenu();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    void setSerial(uint32_t new_serial) {serial = new_serial;}
    uint32_t getSerial(void) {return serial;}
    void updateSize();

    std::unique_ptr<TableForModule> table;

    static QRectF maxRect;
    ModuleInterface moduleInterface = ModuleInterface::UNDEFINED;
private:
    uint32_t serial;


    void initPosItem(QPointF coords);

private slots:
    void slotSettingItem();
};

#endif // GRAPHICSMODULE_H
