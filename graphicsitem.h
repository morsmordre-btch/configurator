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

class GraphicsItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

public:
    GraphicsItem(QObject *parent = nullptr);
    ~GraphicsItem();
    QGraphicsRectItem *rectangle = new QGraphicsRectItem();
    QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem(rectangle);

    QPainter *painter = new QPainter();

    QPointF mouseCoords;

    static int itemsCounter;
    int itemCount;


    std::shared_ptr<TableForIed> table;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    void initPosItem(QPointF coords);
    void initFont();


};

#endif // GRAPHICSITEM_H
