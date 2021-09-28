#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <graphicsitem.h>

#include <map>

#include <QXmlStreamReader>
#include <QFile>

class XmlParser
{
public:
    XmlParser(GraphicsItem *item, QString nameXmlFile);


    std::unique_ptr<QFile> xmlFile;
    std::unique_ptr<QXmlStreamReader> xml;
    std::map<QString, std::map<int, std::map<QString, QString>>> map;
    std::map<int, std::map<QString, QString>> subMap;
    std::map<QString, QString> subSubMap;
    std::map<QString, int> mapIpModulesNum;
    std::map<QString, std::map<int, QString>> mapIpInterfaceNum;
    std::map<int, QString> subMapIpInterfaceNum;

private:
    void parsingModulesList(QString ip);
    void insertToTable(GraphicsItem *item);
    QString findContent(QString keyIp, int keyNum, QString keyType);
};

#endif // XMLPARSER_H
