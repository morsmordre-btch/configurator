#ifndef SETTINGITEM_H
#define SETTINGITEM_H

#include <QDialog>

namespace Ui {
class SettingItem;
}

class SettingItem : public QDialog
{
    Q_OBJECT

public:
    explicit SettingItem(QWidget *parent = nullptr);
    ~SettingItem();

    QString nameIed;
    QString ipIed;
    QString macIed;
    QString loginIed;
    QString passwordIed;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::SettingItem *ui;
};

#endif // SETTINGITEM_H
