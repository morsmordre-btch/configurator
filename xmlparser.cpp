#include "xmlparser.h"

QGraphicsScene *scene_;

XmlParser::XmlParser()
{

}

XmlParser::XmlParser(SystemGroup *item, QString nameXmlFile)
{
    parse(item, nameXmlFile);
}

bool XmlParser::parse(SystemGroup *item, QString nameXmlFile)
{
    xmlFile = std::make_unique<QFile>(nameXmlFile);
    if (!xmlFile->open(QIODevice::ReadOnly)) {
        MsgBox("Не удалось открыть файл.",
               "Проверьте состояние файла.",
               WARNING_MSG);
        return false;
    }
    xml = std::make_unique<QXmlStreamReader>(xmlFile.get());

    while (!xml->atEnd()) {
        if (xml->isStartElement()) {
            if(xml->name() == "Controller") {

                QXmlStreamAttributes attr = xml->attributes();
                parsingModulesList(attr.value("ip").toString());
            }
        }
        xml->readNextStartElement();
    }
    insertToTable(item);

    xmlFile->close();

    return true;
}

void XmlParser::parsingModulesList(QString ip) {
    int numberModules = 0;
    QString interface;
    while (!xml->atEnd()) {
        if (xml->isStartElement()) {
            if(xml->name() == "Module") {
                QXmlStreamAttributes attr = xml->attributes();
                interface = attr.value("interface").toString();
            }
            if(xml->name() == "MType") {
                subSubMap.insert({"MType", xml->readElementText()});
            }
            else if(xml->name() == "SlaveID") {
                subSubMap.insert({"SlaveID", xml->readElementText()});
            }
            else if(xml->name() == "SN") {
                subSubMap.insert({"SN", xml->readElementText()});
            }
            else if(xml->name() == "Freq") {
                subSubMap.insert({"Freq", xml->readElementText()});
            }
            else if(xml->name() == "Speed") {
                subSubMap.insert({"Speed", xml->readElementText()});
            }
        }
        else if (xml->isEndElement()) {
            if (xml->name() == "Module") {
                subMap.insert({numberModules, subSubMap});
                subSubMap.clear();
                subMapIpInterfaceNum.insert({numberModules, interface});
                numberModules++;
            }
        }
        xml->readNextStartElement();
        if (xml->isEndElement()) {
            if (xml->name() == "ModulesList") {
                map.insert({ip,subMap});
                mapIpModulesNum.insert({ip, numberModules});
                mapIpInterfaceNum.insert({ip, subMapIpInterfaceNum});
                subMapIpInterfaceNum.clear();
                subMap.clear();
                return;
            }
        }
    }
}

void XmlParser::insertToTable(SystemGroup *item) {
    //std::map <QString, int>::iterator it;
    QString ip = item->cntrl->getIp();//"192.168.0.1";//item->getIp();
    int numberModule;                   // Количество модулей в объекте

    auto it = mapIpModulesNum.find(ip);
    if (it == mapIpModulesNum.end()) {
        MsgBox("На поле нет контроллеров с IP адресами из XML-файла.",
               "Проверьте правильность IP адресса контроллеров в настройках.",
               WARNING_MSG);
        return;
    }
    std::map<int, QString> interfaceNum = mapIpInterfaceNum.find(ip)->second;
    numberModule = it->second;
    int tableItemCountSpi = 0;
    int tableItemCountRs = 0;
    int countSpi = 0;
    int countRs = 0;

    auto convertModuleTypeToStr = [](int mtype) -> QString
    {
        QString moduleName;

        if(mtype < 100) // модуль интерфейсов
        {
            moduleName = "IM_rev." + QString("%1").arg(mtype,
                                                       2,
                                                       10,
                                                       QChar('0'));
        }
        else if(mtype < 200)
        {
            moduleName = "DI-16_rev." + QString("%1").arg(mtype - 100,
                                                          2,
                                                          10,
                                                          QChar('0'));
        }
        else if(mtype < 300)
        {
            moduleName = "DO-16_rev." + QString("%1").arg(mtype - 200,
                                                          2,
                                                          10,
                                                          QChar('0'));
        }
        else if(mtype < 400)
        {
            moduleName = "AI-8_rev." + QString("%1").arg(mtype - 300,
                                                         2,
                                                         10,
                                                         QChar('0'));
        }
        else if(mtype < 500)
        {
            moduleName = "AO-8_rev." + QString("%1").arg(mtype - 400,
                                                         2,
                                                         10,
                                                         QChar('0'));
        }
        else
        {
            moduleName = "??";
        }

        return moduleName;
    };

    for (int i = 0; i < numberModule; i++) {
        if (interfaceNum.find(i)->second == "SPI") {
            countSpi++;

            QString moduleName;
            auto mtype = findContent(ip,i, "MType").toInt();

            moduleName = convertModuleTypeToStr(mtype);

            auto module_ptr = item->addModule(moduleName, {ModuleInterface::SPI});

            item->cntrl->table->insertRowsForSpi();
            item->cntrl->table->vectorTableSpiItem[tableItemCountSpi]->setFlags(Qt::ItemIsEnabled);
            item->cntrl->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "MType"));
            item->cntrl->table->vectorTableSpiItem[tableItemCountSpi]->setFlags(Qt::ItemIsEnabled);
            item->cntrl->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "SlaveID"));
            item->cntrl->table->vectorTableSpiItem[tableItemCountSpi]->setFlags(Qt::ItemIsEnabled);
            item->cntrl->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "SN"));

            module_ptr->setSerial(findContent(ip,i, "SN").toULong());

            item->cntrl->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "Freq"));
            item->cntrl->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "Speed"));

            module_ptr->table->updateTable(moduleName);

        }
        else if (interfaceNum.find(i)->second == "RS-485") {
            countRs++;

            QString moduleName;
            auto mtype = findContent(ip,i, "MType").toInt();

            moduleName = convertModuleTypeToStr(mtype);

            auto module_ptr = item->addModule(moduleName, {ModuleInterface::RS_485});

            item->cntrl->table->insertRowsForRs();
            item->cntrl->table->vectorTableRsItem[tableItemCountRs]->setFlags(Qt::ItemIsEnabled);
            item->cntrl->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "MType"));
            item->cntrl->table->vectorTableRsItem[tableItemCountRs]->setFlags(Qt::ItemIsEnabled);
            item->cntrl->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "SlaveID"));
            item->cntrl->table->vectorTableRsItem[tableItemCountRs]->setFlags(Qt::ItemIsEnabled);
            item->cntrl->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "SN"));

            module_ptr->setSerial(findContent(ip,i, "SN").toULong());

            item->cntrl->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "Freq"));
            item->cntrl->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "Speed"));

            module_ptr->table->updateTable(moduleName);
        }
    }
}
/*****************************************************
* Function Name: findContent
******************************************************
*
* Summary:
* Находит значение в std::map по переданным ключам
* Parameters:
*
*
* Returns:
* Возвращает соответствующее ключам значение
*
******************************************************/
QString XmlParser::findContent(QString keyIp, int keyNum, QString keyType) {
    std::map<QString, std::map<int, std::map<QString, QString>>>::iterator it;
    std::map<int, std::map<QString, QString>>::iterator subIt;
    std::map<QString, QString>::iterator subSubIt;
    std::map<int, std::map<QString, QString>> subMap;
    std::map<QString, QString> subSubMap;

    it = map.find(keyIp);
    subMap = it->second;
    subIt = subMap.find(keyNum);
    if (subIt == subMap.end())
        return "-";
    subSubMap = subIt->second;
    subSubIt = subSubMap.find(keyType);
    if (subSubIt == subSubMap.end())
        return "-";
    return subSubIt->second;
}

