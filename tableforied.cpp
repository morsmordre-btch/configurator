#include "tableforied.h"
#include "ui_tableforied.h"

TableForIed::TableForIed(int itemCount, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableForIed)
{
    ui->setupUi(this);

    // Устанавливаем название окна с таблицей с порядковым номером КП
    this->setWindowTitle(QString("Таблица КП").append(QString::number(itemCount)));

    //Устанавливаем текст в lable для именования таблиц SPI и RS
    ui->labelSpi->setText("SPI SPI");
    ui->labelRs->setText("RS-485 Modbus RTU");

    // Скрываем вертикальный заголовок
    ui->tableWidgetSpi->verticalHeader()->setVisible(false);
    ui->tableWidgetRs->verticalHeader()->setVisible(false);


    for(int i = 0; i < 10; i++){
        ui->tableWidgetSpi->insertRow(i);
    }

}

TableForIed::~TableForIed()
{
    delete ui;
}
