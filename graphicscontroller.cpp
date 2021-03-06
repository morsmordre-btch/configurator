#include "graphicscontroller.h"

int GraphicsController::itemsCounter = 0;

GraphicsController::GraphicsController() : GraphicsItem() {
    // в название элемента добавляем его порядковый номер
    itemCount = itemsCounter;
    itemsCounter++;

    _name = "КП" + QString::number(itemCount + 1);
    text->setText(_name);

    text.get()->setParentItem(this);
    rectangle.get()->setParentItem(this);

//    addToGroup(text.get());
//    addToGroup(rectangle.get());

    // Создаем окно для таблицы

    // располагаем графический объект в случайном месте
    //initPosItem(QPointF(std::rand()%100, std::rand()%100));
    initPosItem(QPointF(100, 100));

    table = std::make_unique<TableForIed>(itemCount + 1);

    // Создаем окно для настроек

    settingItem = std::make_unique<SettingItem>();
    settingItem->setNameIed(_name);

    connect(
            settingItem.get(),
            &SettingItem::signalSettingItem,
            this,
            &GraphicsController::slotSettingItem
    );
    createContextMenu();

    // Debug Добавление нескольких модулей
//    graphicsModuleVector.push_back(std::make_unique<GraphicsModule>("AI-1",
//                                                                    this->x() - 30,
//                                                                    this->y() + 30));
//    graphicsModuleVector.push_back(std::make_unique<GraphicsModule>("AI-2",
//                                                                    this->x() - 30,
//                                                                    this->y() + 30*2));
//    graphicsModuleVector.push_back(std::make_unique<GraphicsModule>("AI-3",
//                                                                    this->x() - 30,
//                                                                    this->y() + 30*3));

//    int i = 1;
//    for(auto& module : graphicsModuleVector)
//    {
//        module.get()->setParentItem(this);
//        module.get()->setPos(QPointF(-30, +35*i));
//        i++;
//        //addToGroup(module.get());
//    }

    //setHandlesChildEvents(false);
    setHandlesChildEvents(true);
}

GraphicsController::~GraphicsController()
{
//    if(contextMenu != nullptr)
//    {
//        delete contextMenu;
//        contextMenu = nullptr;
//    }
    //removeFromGroup(text.get());
    //removeFromGroup(rectangle.get());

    text->setParentItem(nullptr);
    rectangle->setParentItem(nullptr);

//    for(auto& module : graphicsModuleVector)
//    {
//        module.get()->setParentItem(nullptr);
//        //removeFromGroup(module.get());
//    }

    itemsCounter--;
}

void GraphicsController::setItemIndex(int new_index)
{
    itemCount = new_index;
    _name = "КП" + QString::number(new_index + 1);
    text->setText(_name);

    table->setIndex(new_index + 1);
    settingItem->setNameIed(_name);
}

void GraphicsController::setFont(QFont &font)
{
    text->setFont(font);

    rectangle->setRect(this->x(),
                       this->y(),
                       text->boundingRect().width() + 60,
                       text->boundingRect().height() + 40);

    text->setPos(rectangle->rect().center().x()-text->boundingRect().width()/2,
                 rectangle->rect().center().y()-text->boundingRect().height()/2);
}

// Метод для инициализации связи координат прямоугольника и текста в нем с нашим объектом
void GraphicsController::initPosItem(QPointF coords)
{
    // Задаем начальные координаты нашего объекта (ItemGroup)
    this->setPos(coords);
    // Задаем параметры прямоугольника, связываем координаты прямоугольника с нашим объектом
    rectangle->setRect(this->x(),
                       this->y(),
                       text->boundingRect().width() + 60,
                       text->boundingRect().height() + 40);
    // Располагаем текст по центру прямоугольника

    text->setPos(rectangle->rect().center().x()-text->boundingRect().width()/2,
                 rectangle->rect().center().y()-text->boundingRect().height()/2);

}

void GraphicsController::slotDel() {
    // Отправляем сигнал в mainwindow на удаление текущего графического объекта
    contextMenu->clear();

    emit signalDel(itemCount);
    // удаляем контекстное меню
    //contextMenu->deleteLater();
}

void GraphicsController::slotSetting() {
    settingItem->show();
}

void GraphicsController::slotExportXml() {
    emit signalExportXml(itemCount);
}

void GraphicsController::slotImportXml() {
    emit signalImportXml(itemCount);
}

void GraphicsController::slotDiagnostic() {
    qDebug() << "diagnostic \n";
}

void GraphicsController::createContextMenu() {
    contextMenu = new QMenu();
    contextMenu->addAction("Отправить XML-файл", this, SLOT(slotExportXml()));
    contextMenu->addAction("Принять XML-файл", this, SLOT(slotImportXml()));
    contextMenu->addAction("Выполнить диагностику", this, SLOT(slotDiagnostic()));
    contextMenu->addAction("Настройка", this, SLOT(slotSetting()));
    contextMenu->addSeparator();
    contextMenu->addAction("Удалить", this, SLOT(slotDel()));
}

QString GraphicsController::getIp() {
    return _ip;
}

QString GraphicsController::getMac() {
    return _mac;
}

QString GraphicsController::getLogin() {
    return _login;
}

QString GraphicsController::getPassword(){
    return _password;
}

void GraphicsController::slotSettingItem() {
    _name = settingItem->getName();
    _ip = settingItem->getIp();
    _mac = settingItem->getMac();
    _login = settingItem->getLogin();
    _password = settingItem->getPassword();
}

void GraphicsController::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Устанавливаем координаты объекта в новые координаты минус исходные координаты
    // мыши для плавного перемещения объекта
    event->ignore();
//    this->setPos(mapToScene(event->pos()) - mouseCoords);
}

void GraphicsController::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Запоминаем координаты мыши для плавного перемещения объекта
    //event->ignore();
//    mouseCoords = event->pos();
}

void GraphicsController::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //event->ignore();
//    Q_UNUSED(event);
}

void GraphicsController::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    table->show();
    Q_UNUSED(event);
}

void GraphicsController::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if(contextMenu != nullptr)
        contextMenu->popup(event->screenPos());
    else
        qDebug() << "Попытка обратиться к несуществующему QMenu";
}
