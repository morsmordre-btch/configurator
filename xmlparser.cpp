#include "xmlparser.h"

XmlParser::XmlParser(GraphicsItem *item, QString nameXmlFile)
{
    xmlFile = std::make_unique<QFile>(nameXmlFile);
    if (!xmlFile->open(QIODevice::ReadOnly)) {
        MsgBox("Не удалось открыть файл.",
               "Проверьте состояние файла.",
               WARNING_MSG);
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

void XmlParser::insertToTable(GraphicsItem *item) {
    std::map <QString, int>::iterator it;
    QString ip = item->getIpIed();//"192.168.0.0.1";//item->getIpIed();
    int numberModule;                   // Количество модулей в объекте
    it = mapIpModulesNum.find(ip);
    if (it == mapIpModulesNum.end()) {
        MsgBox("На поле нет контроллеров с IP адрессами из XML-файла.",
               "Проверьте правильность IP адресса контроллеров в настройках.",
               WARNING_MSG);
        return;
    }
    std::map<int, QString> interfaceNum = mapIpInterfaceNum.find(ip)->second;
    numberModule = it->second;
    int tableItemCountSpi = 0;
    int tableItemCountRs = 0;
    for (int i = 0; i < numberModule; i++) {
        if (interfaceNum.find(i)->second == "SPI") {
            item->table->insertRowsForSpi();
            item->table->vectorTableSpiItem[tableItemCountSpi]->setFlags(Qt::ItemIsEnabled);
            item->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "MType"));
            item->table->vectorTableSpiItem[tableItemCountSpi]->setFlags(Qt::ItemIsEnabled);
            item->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "SlaveID"));
            item->table->vectorTableSpiItem[tableItemCountSpi]->setFlags(Qt::ItemIsEnabled);
            item->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "SN"));
            item->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "Freq"));
            item->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "Speed"));
        }
        else if (interfaceNum.find(i)->second == "RS-485") {
            item->table->insertRowsForRs();
            item->table->vectorTableRsItem[tableItemCountRs]->setFlags(Qt::ItemIsEnabled);
            item->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "MType"));
            item->table->vectorTableRsItem[tableItemCountRs]->setFlags(Qt::ItemIsEnabled);
            item->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "SlaveID"));
            item->table->vectorTableRsItem[tableItemCountRs]->setFlags(Qt::ItemIsEnabled);
            item->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "SN"));
            item->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "Freq"));
            item->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "Speed"));
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

