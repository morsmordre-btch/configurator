#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <msgbox.h>

#include <QMessageBox>
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

class GraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

protected:
    QString _name;

    std::unique_ptr<SettingItem> settingItem;

    QMenu *contextMenu;
public:
    GraphicsItem(QObject *parent = nullptr);
    ~GraphicsItem();

    std::unique_ptr<QGraphicsRectItem> rectangle = std::make_unique<QGraphicsRectItem>();
    std::unique_ptr<QGraphicsSimpleTextItem> text = std::make_unique<QGraphicsSimpleTextItem>();

    QPainter *painter = new QPainter();

    QPointF mouseCoords;


    QRectF boundingRect() const;

    QString getName();



    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    void setFont(QFont&);
protected:
    virtual void createContextMenu() = 0;
    virtual void initPosItem(QPointF coords) = 0;

protected slots:
    virtual void slotSettingItem() = 0;

signals:
    void signalDel(int itemCount);
    void signalExportXml(int itemCount);
    void signalImportXml(int itemCount);

};

#endif // GRAPHICSITEM_H
