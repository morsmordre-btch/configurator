#include "settingitem.h"
#include "ui_settingitem.h"
#include <QDebug>
SettingItem::SettingItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingItem)
{
    ui->setupUi(this);

    // Устанавливаем название окна
    this->setWindowTitle(QString("Настройки"));
}

SettingItem::~SettingItem()
{
    delete ui;
}

void SettingItem::on_buttonBox_accepted()
{
    // Сохраняем введенные настройки

    nameIed = ui->nameIed->text();
    ipIed = ui->ipIed->text();
    macIed = ui->macIed->text();
    loginIed = ui->loginIed->text();
    passwordIed = ui->passwordIed->text();
}
