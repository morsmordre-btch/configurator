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

QString SettingItem::getName() {
    return ui->nameIed->text();
}

QString SettingItem::getIp() {
    return ui->ipIed->text();
}

QString SettingItem::getMac() {
    return ui->macIed->text();
}

QString SettingItem::getLogin() {
    return ui->loginIed->text();
}

QString SettingItem::getPassword(){
    return ui->passwordIed->text();
}

void SettingItem::setNameIed(QString nameIed) {
    ui->nameIed->setText(nameIed);
}
