#include "tableforied.h"
#include "ui_tableforied.h"

TableForIed::TableForIed(int itemCount, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableForIed)
{
    ui->setupUi(this);

    // Устанавливаем название окна с таблицей
    this->setWindowTitle(QString("Таблица КП").append(QString::number(itemCount)));

    ui->label->setText("SPI SPI");
}

TableForIed::~TableForIed()
{
    delete ui;
}
