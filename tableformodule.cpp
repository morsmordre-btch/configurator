#include "tableformodule.h"
#include "ui_tableformodule.h"

TableForModule::TableForModule(int numberOfTypeModule, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableForModule)
{
    ui->setupUi(this);

    ui->label->setText(QString::number(numberOfTypeModule));


}

TableForModule::~TableForModule()
{
    delete ui;
}
