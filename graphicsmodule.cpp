#include "graphicsmodule.h"

GraphicsModule::GraphicsModule(QString name, int x, int y) : GraphicsItem() {
    // в название элемента добавляем его порядковый номер
    _name = name;
    text->setText(_name);


//    addToGroup(text.get());
//    addToGroup(rectangle.get());
    text.get()->setParentItem(this);
    rectangle.get()->setParentItem(this);
    // Создаем окно для таблицы

    // располагаем графический объект в случайном месте
    initPosItem(QPointF(x, y));


    table = std::make_unique<TableForIed>(0);

    // Создаем окно для настроек

    settingItem = std::make_unique<SettingItem>();
    settingItem->setNameIed(_name);

    connect(
            settingItem.get(),
            &SettingItem::signalSettingItem,
            this,
            &GraphicsModule::slotSettingItem
    );
    createContextMenu();

    setHandlesChildEvents(true);
}

GraphicsModule::~GraphicsModule()
{
    text.get()->setParentItem(nullptr);
    rectangle.get()->setParentItem(nullptr);

//    removeFromGroup(text.get());
//    removeFromGroup(rectangle.get());
}

void GraphicsModule::initPosItem(QPointF coords)
{
    // Задаем начальные координаты нашего объекта (ItemGroup)
    this->setPos(coords);
    // Задаем параметры прямоугольника, связываем координаты прямоугольника с нашим объектом
    rectangle->setRect(this->x(),this->y(),50,25);
    // Располагаем текст по центру прямоугольника
    text->setPos(rectangle->rect().center().x()-text->boundingRect().width()/2,
                 rectangle->rect().center().y()-text->boundingRect().height()/2);

}

void GraphicsModule::createContextMenu() {
    contextMenu = new QMenu();

    contextMenu->addAction("Настроить по XML-файлу", this, SLOT(slotExportXml()));
    contextMenu->addAction("Настройка", this, SLOT(slotSetting()));
}

void GraphicsModule::slotSettingItem() {
    _name = settingItem->getName();
}

void GraphicsModule::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Устанавливаем координаты объекта в новые координаты минус исходные координаты
    // мыши для плавного перемещения объекта
    event->ignore();
    //this->setPos(mapToScene(event->pos()) - mouseCoords);
}

void GraphicsModule::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Запоминаем координаты мыши для плавного перемещения объекта
    //event->ignore();
    //mouseCoords = event->pos();
}

void GraphicsModule::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //event->ignore();
    Q_UNUSED(event);
}

void GraphicsModule::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    table->show();
    Q_UNUSED(event);
}

void GraphicsModule::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(contextMenu != nullptr)
        contextMenu->popup(event->screenPos());
    else
        qDebug() << "Попытка обратиться к несуществующему QMenu";
}
