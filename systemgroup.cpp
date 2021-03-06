#include "systemgroup.h"

SystemGroup::SystemGroup(QObject *parent) : QObject(parent), QGraphicsItem()
{
    cntrl = std::make_unique<GraphicsController>();

    cntrl->setFont(font);
    cntrl->setParentItem(this);
    cntrl->setFlag(QGraphicsItem::ItemStacksBehindParent, true);

    textRS = std::make_unique<QGraphicsSimpleTextItem>("RS-485");
    textSPI = std::make_unique<QGraphicsSimpleTextItem>("SPI");

    setFlag(QGraphicsItem::ItemHasNoContents, true);
    setFiltersChildEvents(false);
}

SystemGroup::~SystemGroup()
{
    for(auto& module : graphicsModuleVector)
        module->setParentItem(nullptr);

    cntrl->setParentItem(nullptr);

    lineRS1->setParentItem(nullptr);
    lineRS2->setParentItem(nullptr);
    lineSPI1->setParentItem(nullptr);
    lineSPI2->setParentItem(nullptr);

    delete lineRS1;
    delete lineRS2;
    delete lineSPI1;
    delete lineSPI2;

    for(auto& line : rsLines)
        line->setParentItem(nullptr);
    for(auto& line : spiLines)
        line->setParentItem(nullptr);

    delete painter;
}

void SystemGroup::setItemIndex(int new_index)
{
    cntrl->setItemIndex(new_index);
}

GraphicsModule* SystemGroup::addModule(QString name, ModuleInterface interface)
{
    graphicsModuleVector.push_back(std::make_unique<GraphicsModule>(name,
                                                                    0,
                                                                    0));

    graphicsModuleVector.back()->setFont(font);
    graphicsModuleVector.back()->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
    graphicsModuleVector.back()->setParentItem(this);
    graphicsModuleVector.back()->moduleInterface = interface;

    if(interface == ModuleInterface::RS_485) // По стрелкам справа
    {
        QLineF line3Coords;
        if(noRS485)
        {
            noRS485 = false;

            auto rect = cntrl->boundingRect();

            rect = mapRectFromItem(cntrl.get(), rect);

            textRS->setParentItem(this);
            textRS->setFont(font);

            QLineF line1Coords{rect.x() + rect.width(),
                        rect.y() + rect.height()/2,
                        rect.x() + rect.width() + 20 + textRS->boundingRect().width(),
                        rect.y() + rect.height()/2};

            lineRS1 = new QGraphicsLineItem;
            lineRS1->setParentItem(this);
            lineRS1->setLine(line1Coords);
/*
            static QGraphicsLineItem line1{{rect.x() + rect.width(),
                            rect.y() + rect.height()/2,
                            rect.x() + rect.width() + 60,
                            rect.y() + rect.height()/2}, this};
*/
            //QLineF line1Coords{line1.line()};
            rect = mapRectFromItem(textRS.get(), textRS->boundingRect());

            textRS->setPos({(line1Coords.x1() + line1Coords.x2())/2 - rect.width()/2,
                           line1Coords.y1() - rect.height() - 5});

            QLineF line2Coords{line1Coords.x2(),
                        line1Coords.y2(),
                        line1Coords.x2(),
                        line1Coords.y2() + 20
                        + graphicsModuleVector.back()->boundingRect().height()
                        + cntrl->boundingRect().height()/2};

            lineRS2 = new QGraphicsLineItem;
            lineRS2->setParentItem(this);
            lineRS2->setLine(line2Coords);
//            static QGraphicsLineItem line2{line2Coords, this};

            line3Coords = {line2Coords.x2(), line2Coords.y2(),
                        line2Coords.x2() + 20, line2Coords.y2()};
            auto line3 = new QGraphicsLineItem(line3Coords, this);
            rsLines.emplace_back(line3);

            rect = graphicsModuleVector.back()->boundingRect();
            graphicsModuleVector.back()->setPos(line3Coords.x2(), line3Coords.y2() - rect.height()/2);
        }
        else
        {
            QLineF line2Coords{lineRS2->line()};
            line2Coords.setLength(line2Coords.length() + 20
                                  + graphicsModuleVector.back()->boundingRect().height());
            lineRS2->setLine(line2Coords);

            line3Coords = {line2Coords.x2(), line2Coords.y2(),
                        line2Coords.x2() + 20, line2Coords.y2()};


            auto line3 = new QGraphicsLineItem(line3Coords, this);
            rsLines.emplace_back(line3);

            auto rect = graphicsModuleVector.back()->boundingRect();
            graphicsModuleVector.back()->setPos(line3Coords.x2(), line3Coords.y2() - rect.height()/2);
        }
    }
    else // Слева
    {
        QLineF line3Coords;
        if(noSPI)
        {
            noSPI = false;

            auto rect = cntrl->boundingRect();

            rect = mapRectFromItem(cntrl.get(), rect);
            //test

            textSPI->setFont(font);
            textRS->setFont(font);
            textSPI->setParentItem(this);

            QLineF line1Coords{rect.x(),
                        rect.y() + rect.height()/2,
                        rect.x() - 20 - textRS->boundingRect().width(),
                        rect.y() + rect.height()/2};

            lineSPI1 = new QGraphicsLineItem;
            lineSPI1->setParentItem(this);
            lineSPI1->setLine(line1Coords);
/*
            static QGraphicsLineItem line1{{rect.x() + rect.width(),
                            rect.y() + rect.height()/2,
                            rect.x() + rect.width() + 60,
                            rect.y() + rect.height()/2}, this};
*/
            //QLineF line1Coords{line1.line()};
            rect = mapRectFromItem(textSPI.get(), textSPI->boundingRect());

            textSPI->setPos({(line1Coords.x1() + line1Coords.x2())/2 - rect.width()/2,
                           line1Coords.y2() - rect.height() - 5});

            QLineF line2Coords{line1Coords.x2(),
                        line1Coords.y2(),
                        line1Coords.x2(),
                        line1Coords.y2() + 20
                        + graphicsModuleVector.back()->boundingRect().height()
                        + cntrl->boundingRect().height()/2};

            lineSPI2 = new QGraphicsLineItem;
            lineSPI2->setParentItem(this);
            lineSPI2->setLine(line2Coords);
//            static QGraphicsLineItem line2{line2Coords, this};

            line3Coords = {line2Coords.x2(), line2Coords.y2(),
                        line2Coords.x2() + 20, line2Coords.y2()};
            auto line3 = new QGraphicsLineItem(line3Coords, this);
            spiLines.emplace_back(line3);

            rect = graphicsModuleVector.back()->boundingRect();
            graphicsModuleVector.back()->setPos(line3Coords.x2(),
                                                line3Coords.y2() - rect.height()/2);
        }
        else
        {
            QLineF line2Coords{lineSPI2->line()};
            line2Coords.setLength(line2Coords.length() + 20
                                  + graphicsModuleVector.back()->boundingRect().height());
            lineSPI2->setLine(line2Coords);

            line3Coords = {line2Coords.x2(), line2Coords.y2(),
                        line2Coords.x2() + 20, line2Coords.y2()};


            auto line3 = new QGraphicsLineItem(line3Coords, this);
            spiLines.emplace_back(line3);

            auto rect = graphicsModuleVector.back()->boundingRect();
            graphicsModuleVector.back()->setPos(line3Coords.x2(),
                                                line3Coords.y2() - rect.height()/2);
        }
    }

    std::size_t cntr_rs = 0;
    std::size_t cnrt_spi = 0;

    for(auto& module : graphicsModuleVector)
    {
        module->updateSize();
        if(module->moduleInterface == ModuleInterface::RS_485)
        {
            const auto line = rsLines.at(cntr_rs++)->line();
            const QPointF end = {line.x2(), line.y2()};
            const auto rect = mapRectFromItem(module.get(), module->boundingRect());

            const QPointF pnt{end.x(), end.y() - rect.height()/2};

            module->setPos(mapToItem(module.get(), pnt));
        }
        else
        {
            const auto line = spiLines.at(cnrt_spi++)->line();
            //const auto end = mapFromItem(spiLines.at(cnrt_spi - 1).get(), line.x2(), line.y2());
            const QPointF end = {line.x2(), line.y2()};
            const auto rect = mapRectFromItem(module.get(), module->boundingRect());

            const QPointF pnt{end.x(), end.y() - rect.height()/2};

            module->setPos(mapToItem(module.get(), pnt));
        }

    }

    return graphicsModuleVector.back().get();
}

void SystemGroup::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // Устанавливаем координаты объекта в новые координаты минус исходные координаты
    // мыши для плавного перемещения объекта
    this->moveBy(event->pos().x() - mouseCoords.x(), event->pos().y() - mouseCoords.y());
}

void SystemGroup::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Запоминаем координаты мыши для плавного перемещения объекта

    bool contains = false;
    for(auto* child : childItems())
    {
        if(child->isUnderMouse())
        {
            contains = true;
        }
    }

    if(!contains)
    {
        event->ignore();
        return;
    }

    mouseCoords = event->pos();
}

void SystemGroup::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void SystemGroup::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    for(auto* child : childItems())
    {
        if(child->isUnderMouse())//child->contains(mapToItem(child, event->pos())))
        {
            scene()->sendEvent(child, event);
            break;
        }
    }
}

void SystemGroup::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    event->ignore();
}

void SystemGroup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF SystemGroup::boundingRect() const
{
    return childrenBoundingRect();
}
