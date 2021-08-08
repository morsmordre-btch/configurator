#ifndef TABLEFORIED_H
#define TABLEFORIED_H

#include <QDialog>
#include <memory>
#include <tableformodule.h>
#include <QTableWidget>

namespace Ui {
class TableForIed;
}

class TableForIed : public QDialog
{
    Q_OBJECT

public:
    explicit TableForIed(int itemCount, QWidget *parent = nullptr);
    ~TableForIed();

    // Создаем вектор таблиц для каждого модуля
    std::vector<std::shared_ptr<TableForModule>> vectorTableForModule;

    // Создаем вектор ячеек таблицы ied
    std::vector<std::unique_ptr<QTableWidgetItem>> vectorTableItem;


private slots:

    void on_tableWidgetSpi_cellDoubleClicked(int row, int column);

private:
    Ui::TableForIed *ui;
};

#endif // TABLEFORIED_H
