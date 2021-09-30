#include "graphicsitem.h"

int GraphicsItem::itemsCounter = 0;


GraphicsItem::GraphicsItem(QObject *parent) : QObject(parent), QGraphicsItemGroup ()
{
    initFont();
    itemsCounter++;
    itemCount = itemsCounter;

    // в название элемента добавляем его порядковый номер
    text->setText(QString("КП").append(QString::number(itemCount)));
    // располагаем графический объект в случайном месте
    initPosItem(QPointF(std::rand()%100, std::rand()%100));

    addToGroup(text);
    addToGroup(rectangle);

    // Создаем окно для таблицы

    table = std::make_unique<TableForIed>(itemCount);

    // Создаем окно для настроек

    settingItem = std::make_unique<SettingItem>();

    // Создание контекстного меню для объекта
    createContextMenu();

}

GraphicsItem::~GraphicsItem()
{
    itemsCounter--;
}

QRectF GraphicsItem::boundingRect() const
{
    return QRectF (0,0,100,50);
}

void GraphicsItem::initFont()
{
    // Устанавливаем шрифт текста
    QFont font;
    int id = QFontDatabase::addApplicationFont("/home/morsmordre/.fonts/GOST2304_TypeB.ttf");
    QStringList GOST_TypeB = QFontDatabase::applicationFontFamilies(id);
    // Если GOST Type B недоступен, то по-умолчанию Arial
    if (id == -1)
    {
        font.setFamily("Arial");
        font.setPointSize(14);
        font.setWeight(QFont::Normal);
        font.setItalic(true);
    }
    else
    {
        font.setFamily(GOST_TypeB.at(0));
        font.setPointSize(18);
        font.setWeight(QFont::Normal);
        font.setItalic(true);
    }
    text->setFont(font);
}


// Метод для инициализации связи координат прямоугольника и текста в нем с нашим объектом
void GraphicsItem::initPosItem(QPointF coords)
{
    // Задаем начальные координаты нашего объекта (ItemGroup)
    this->setPos(coords);
    // Задаем параметры прямоугольника, связываем координаты прямоугольника с нашим объектом
    rectangle->setRect(this->x(),this->y(),100,50);
    // Располагаем текст по центру прямоугольника
    text->setPos(rectangle->rect().center().x()-text->boundingRect().width()/2,
                 rectangle->rect().center().y()-text->boundingRect().height()/2);

}

void GraphicsItem::createContextMenu() {
    contextMenu = new QMenu();
    contextMenu->addAction("Отправить XML-файл", this, SLOT(slotExportXml()));
    contextMenu->addAction("Принять XML-файл", this, SLOT(slotImportXml()));
    contextMenu->addAction("Выполнить диагностику", this, SLOT(slotDiagnostic()));
    contextMenu->addAction("Настройка", this, SLOT(slotSetting()));
    contextMenu->addSeparator();
    contextMenu->addAction("Удалить", this, SLOT(slotDel()));
}



void GraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Устанавливаем координаты объекта в новые координаты минус исходные координаты
    // мыши для плавного перемещения объекта
    this->setPos(mapToScene(event->pos()) - mouseCoords);
}

void GraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Запоминаем координаты мыши для плавного перемещения объекта
    mouseCoords = event->pos();
}

void GraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    Q_UNUSED(event);
}

void GraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    table->show();
    Q_UNUSED(event);
}

void GraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    contextMenu->popup(event->screenPos());
}

void GraphicsItem::slotDel() {
    // Отправляем сигнал в mainwindow на удаление текущего графического объекта
    emit signalDel(itemCount);
    // удаляем контекстное меню
    contextMenu->deleteLater();
}

void GraphicsItem::slotSetting() {
    settingItem->show();
}

void GraphicsItem::slotExportXml() {
    emit signalExportXml(itemCount);
    //qDebug() << "export XML-file \n";
}

void GraphicsItem::slotImportXml() {
    emit signalImportXml(itemCount);
    //qDebug() << "import XML-file \n";
}

void GraphicsItem::slotDiagnostic() {
    qDebug() << "diagnostic \n";
}

void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    //painter->drawRoundedRect(0,0,100,50,5,5);

    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
