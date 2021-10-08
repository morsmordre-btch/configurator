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

class GraphicsItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

private:
    QString _nameIed;
    QString _ipIed;
    QString _macIed;
    QString _loginIed;
    QString _passwordIed;

    std::unique_ptr<SettingItem> settingItem;

    QMenu *contextMenu;

public:
    QGraphicsRectItem *rectangle = new QGraphicsRectItem();
    QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem(rectangle);

    QPainter *painter = new QPainter();

    QPointF mouseCoords;

    static int itemsCounter;
    int itemCount;

    std::unique_ptr<TableForIed> table;


    QRectF boundingRect() const;

    GraphicsItem(QObject *parent = nullptr);
    ~GraphicsItem();

    QString getNameIed();
    QString getIpIed();
    QString getMacIed();
    QString getLoginIed();
    QString getPasswordIed();


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    void createContextMenu();
    void initPosItem(QPointF coords);
    void initFont();

private slots:
    void slotSetting();
    void slotDel();
    void slotExportXml();
    void slotImportXml();
    void slotDiagnostic();
    void slotSettingItem();

signals:
    void signalDel(int itemCount);
    void signalExportXml(int itemCount);
    void signalImportXml(int itemCount);

};

#endif // GRAPHICSITEM_H
