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

    QString getName();
    QString getIp();
    QString getMac();
    QString getLogin();
    QString getPassword();

    void setNameIed(QString nameIed);

private slots:
    void on_buttonBox_accepted();

signals:
    void signalSettingItem();



private:
    Ui::SettingItem *ui;
};

#endif // SETTINGITEM_H
