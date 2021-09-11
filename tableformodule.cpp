#include "tableformodule.h"
#include "ui_tableformodule.h"

TableForModule::TableForModule(int numberOfTypeModule, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableForModule)
{
    ui->setupUi(this);

    // Устанавливаем название окна
    this->setWindowTitle(QString("Таблица модуля"));


    // Скрываем вертикальный заголовок
    ui->tableWidget->verticalHeader()->setVisible(false);
}


void TableForModule::updateTable(QString typeModule) {
    auto parts = typeModule.split("-");
    // Добавляем в название окна Тип модуля
    this->setWindowTitle(QString("Таблица модуля ") + typeModule);

    for(int i = 0; i < parts[1].toInt(); i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        vectorTableItem.push_back(std::make_unique<QTableWidgetItem>
                                 (QString(parts[0])+"-"+(QString::number(i+1))));
        ui->tableWidget->setItem(i,0,
                                 vectorTableItem[vectorTableItem.size() - 1].get());

        vectorComboBox.push_back(std::make_unique<QComboBox>());
        vectorComboBox[i].get()->addItem("4-20 мА");
        vectorComboBox[i].get()->addItem("0-5 В");
        vectorComboBox[i].get()->addItem("0-10 В");
        vectorComboBox[i].get()->addItem("-5-5 В");
        vectorComboBox[i].get()->addItem("-10-10 В");

        ui->tableWidget->setCellWidget(i,1, vectorComboBox[i].get());
    }
}

TableForModule::~TableForModule()
{
    delete ui;
}


