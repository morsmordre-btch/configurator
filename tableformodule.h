#ifndef TABLEFORMODULE_H
#define TABLEFORMODULE_H

#include <QDialog>

namespace Ui {
class TableForModule;
}

class TableForModule : public QDialog
{
    Q_OBJECT

public:
    explicit TableForModule(int numberOfTypeModule, QWidget *parent = nullptr);
    ~TableForModule();

private:
    Ui::TableForModule *ui;
};

#endif // TABLEFORMODULE_H
