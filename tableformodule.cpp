#include "tableformodule.h"
#include "ui_tableformodule.h"

TableForModule::TableForModule(int numberOfTypeModule, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableForModule)
{
    ui->setupUi(this);

    // Устанавливаем название окна с таблицей с порядковым номером КП
    this->setWindowTitle(QString("Таблица модуля"));


    // Скрываем вертикальный заголовок
    ui->tableWidget->verticalHeader()->setVisible(false);


    for (int i = 0; i < 2; i++) {
        ui->tableWidget->insertRow(i);
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


