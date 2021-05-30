#include "graphicsitem.h"



GraphicsItem::GraphicsItem(QObject *parent) : QObject(parent), QGraphicsItemGroup ()
{
    initFont();
    text->setText("КП1");

    initPosItem(QPointF(50,50));

    addToGroup(text);
    addToGroup(rectangle);
}

GraphicsItem::~GraphicsItem()
{

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

void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->drawRoundedRect(0,0,100,50,5,5);

    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
