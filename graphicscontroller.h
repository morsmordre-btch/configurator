#ifndef GRAPHICSCONTROLLER_H
#define GRAPHICSCONTROLLER_H

#include <graphicsitem.h>
//#include <graphicsmodule.h>

class GraphicsController : public GraphicsItem
{
    Q_OBJECT


private:
    QString _ip;
    QString _mac;
    QString _login;
    QString _password;

public:
    GraphicsController();
    ~GraphicsController();
    void createContextMenu();

    // Создаем вектор графических модулей
//    std::vector<std::unique_ptr<GraphicsModule>> graphicsModuleVector;

    static int itemsCounter;
    int itemCount;

    std::unique_ptr<TableForIed> table;

    void setItemIndex(int); // Задать itemCount объекта
    void setFont(QFont &);

    QString getIp();
    QString getMac();
    QString getLogin();
    QString getPassword();

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
private:
    void initPosItem(QPointF coords);

private slots:
    void slotSetting();
    void slotDel();
    void slotExportXml();
    void slotImportXml();
    void slotDiagnostic();
    void slotSettingItem();


};

#endif // GRAPHICSCONTROLLER_H
