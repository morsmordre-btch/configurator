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
    emit signalSettingItem();

}

QString SettingItem::getNameIed() {
    return ui->nameIed->text();
}

QString SettingItem::getIpIed() {
    return ui->ipIed->text();
}

QString SettingItem::getMacIed() {
    return ui->macIed->text();
}

QString SettingItem::getLoginIed() {
    return ui->loginIed->text();
}

QString SettingItem::getPasswordIed(){
    return ui->passwordIed->text();
}

void SettingItem::setNameIed(QString nameIed) {
    ui->nameIed->setText(nameIed);
}
