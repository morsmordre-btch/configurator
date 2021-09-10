#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QGraphicsItem>
#include <QFont>
#include <QFontDatabase>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <memory>
#include <tableforied.h>
#include <QMenu>
#include <cstdlib>
#include <settingitem.h>

class GraphicsItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:
    GraphicsItem(/*std::shared_ptr<QMenu> contextMenu,*/ QObject *parent = nullptr);
    ~GraphicsItem();
    QGraphicsRectItem *rectangle = new QGraphicsRectItem();
    QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem(rectangle);

    QPainter *painter = new QPainter();

    QPointF mouseCoords;

    static int itemsCounter;
    int itemCount;

    std::unique_ptr<TableForIed> table;

    std::unique_ptr<SettingItem> settingItem;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);


private:
    void initPosItem(QPointF coords);
    void initFont();

    //std::unique_ptr<QMenu> contextMenu;
    QMenu *contextMenu;
    QAction *setting;
    QAction *del;

public slots:
    void slotSetting();
    void slotDel();

signals:
    void signalDel(int itemCount);

};

#endif // GRAPHICSITEM_H
