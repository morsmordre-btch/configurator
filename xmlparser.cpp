#include "xmlparser.h"

XmlParser::XmlParser(GraphicsItem *item, QString nameXmlFile)
{
    xmlFile = std::make_unique<QFile>(nameXmlFile);
    if (!xmlFile->open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file ";
    }
    xml = std::make_unique<QXmlStreamReader>(xmlFile.get());

    while (!xml->atEnd()) {
        if (xml->isStartElement()) {
            if(xml->name() == "modulesList") {

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
            if(xml->name() == "module") {
                QXmlStreamAttributes attr = xml->attributes();
                interface = attr.value("interface").toString();
            }
            if(xml->name() == "type") {
                subSubMap.insert({"type", xml->readElementText()});
            }
            else if(xml->name() == "slaveId") {
                subSubMap.insert({"slaveId", xml->readElementText()});
            }
            else if(xml->name() == "serialNum") {
                subSubMap.insert({"serialNum", xml->readElementText()});
            }
            else if(xml->name() == "freq") {
                subSubMap.insert({"freq", xml->readElementText()});
            }
            else if(xml->name() == "speed") {
                subSubMap.insert({"speed", xml->readElementText()});
            }
        }
        else if (xml->isEndElement()) {
            if (xml->name() == "module") {
                subMap.insert({numberModules, subSubMap});
                subSubMap.clear();
                subMapIpInterfaceNum.insert({numberModules, interface});
                numberModules++;
            }
        }
        xml->readNextStartElement();
        if (xml->isEndElement()) {
            if (xml->name() == "modulesList") {
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
    QString ip = "192.168.0.0.1";//item->settingItem->ipIed;
    int numberModule;                   // Количество модулей в объекте
    it = mapIpModulesNum.find(ip);
    if (it == mapIpModulesNum.end()) {
        showMsgBox();
        return;
    }
    std::map<int, QString> interfaceNum = mapIpInterfaceNum.find(ip)->second;
    numberModule = it->second;
    int tableItemCountSpi = 0;
    int tableItemCountRs = 0;
    for (int i = 0; i < numberModule; i++) {
        if (interfaceNum.find(i)->second == "SPI") {
            item->table->insertRowsForSpi();
            item->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "type"));
            item->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "slaveId"));
            item->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "serialNum"));
            item->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "freq"));
            item->table->vectorTableSpiItem[tableItemCountSpi++]->setText(
                        findContent(ip,i, "speed"));
        }
        else if (interfaceNum.find(i)->second == "RS-485") {
            item->table->insertRowsForRs();
            item->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "type"));
            item->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "slaveId"));
            item->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "serialNum"));
            item->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "freq"));
            item->table->vectorTableRsItem[tableItemCountRs++]->setText(
                        findContent(ip,i, "speed"));
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
    subSubMap = subIt->second;
    subSubIt = subSubMap.find(keyType);
    return subSubIt->second;
}

void XmlParser::showMsgBox() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Предупреждение");
    msgBox.setText("На поле нет контроллеров с IP адрессами из XML-файла.");
    msgBox.setInformativeText("Проверьте правильность IP адресса контроллеров в настройках.");
    msgBox.exec();
}
