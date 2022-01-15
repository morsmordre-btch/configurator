#ifndef GRAPHICSMODULE_H
#define GRAPHICSMODULE_H

#include <graphicsitem.h>

class GraphicsModule : public GraphicsItem
{
public:
    GraphicsModule(QString name, int x, int y);
    ~GraphicsModule();

    void createContextMenu();

private:
    void initPosItem(QPointF coords);

private slots:
    void slotSettingItem();
};

#endif // GRAPHICSMODULE_H
