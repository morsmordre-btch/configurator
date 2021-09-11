#ifndef TABLEFORMODULE_H
#define TABLEFORMODULE_H

#include <QDialog>
#include <QComboBox>
#include <memory>
#include <QDebug>
#include <vector>
#include <QTableWidgetItem>

namespace Ui {
class TableForModule;
}

class TableForModule : public QDialog
{
    Q_OBJECT

public:
    explicit TableForModule(QWidget *parent = nullptr);
    ~TableForModule();

    // Создаем вектор комбо боксов
    std::vector<std::unique_ptr<QComboBox>> vectorComboBox;

    void updateTable(QString typeModule);



private:

    std::vector<std::unique_ptr<QTableWidgetItem>> vectorTableItem;

    Ui::TableForModule *ui;
    QString typeModule;
};

#endif // TABLEFORMODULE_H
