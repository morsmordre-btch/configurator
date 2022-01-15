#include "graphicsmodule.h"

GraphicsModule::GraphicsModule(QString name, int x, int y) : GraphicsItem() {
    // в название элемента добавляем его порядковый номер
    _name = name;
    text->setText(_name);

    addToGroup(text.get());
    addToGroup(rectangle.get());

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
}

GraphicsModule::~GraphicsModule()
{
    removeFromGroup(text.get());
    removeFromGroup(rectangle.get());
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


