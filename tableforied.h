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

    void setIndex(int);

    // Метод добавления строк в таблицу

    void insertRowsForSpi();
    void insertRowsForRs();

    // Создаем вектор таблиц для каждого модуля
    std::vector<std::shared_ptr<TableForModule>> vectorTableForModuleSpi;

    // Создаем вектор ячеек таблицы ied
    std::vector<std::unique_ptr<QTableWidgetItem>> vectorTableSpiItem;

    // Создаем вектор таблиц для каждого модуля
    std::vector<std::shared_ptr<TableForModule>> vectorTableForModuleRs;

    // Создаем вектор ячеек таблицы ied
    std::vector<std::unique_ptr<QTableWidgetItem>> vectorTableRsItem;

private slots:

    void on_tableWidgetSpi_cellDoubleClicked(int row, int column);

    void on_tableWidgetRs_cellDoubleClicked(int row, int column);

private:
    Ui::TableForIed *ui;
};

#endif // TABLEFORIED_H
