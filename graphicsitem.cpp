#include "graphicsitem.h"

GraphicsItem::GraphicsItem(QObject *parent) : QObject(parent), QGraphicsItem ()
{
    initFont();
    // Создание контекстного меню для объекта
    //createContextMenu();
    contextMenu = nullptr;
}

GraphicsItem::~GraphicsItem()
{
    if(contextMenu != nullptr)
    {
        contextMenu->clear();
        contextMenu->deleteLater();
        contextMenu = nullptr;
    }
}

QRectF GraphicsItem::boundingRect() const
{
    return childrenBoundingRect();
}

void GraphicsItem::initFont()
{
    // Устанавливаем шрифт текста
    QFont font;
    int id = QFontDatabase::addApplicationFont("/home/morsmordre/.fonts/GOST2304_TypeB.ttf"); // TODO
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
    if(contextMenu != nullptr)
        contextMenu->popup(event->screenPos());
    else
        qDebug() << "Попытка обратиться к несуществующему QMenu";
}


QString GraphicsItem::getName() {
    return _name;
}

void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    //painter->drawRoundedRect(0,0,100,50,5,5);

    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
