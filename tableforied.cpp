#include "tableforied.h"
#include "ui_tableforied.h"

TableForIed::TableForIed(int itemCount, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableForIed)
{
    ui->setupUi(this);

    // Устанавливаем название окна с таблицей с порядковым номером КП
    this->setWindowTitle(QString("Таблица КП").append(QString::number(itemCount)));

    //Устанавливаем текст в lable для именования таблиц SPI и RS
    ui->labelSpi->setText("SPI SPI");
    ui->labelRs->setText("RS-485 Modbus RTU");

    // Скрываем вертикальный заголовок
    ui->tableWidgetSpi->verticalHeader()->setVisible(false);
    ui->tableWidgetRs->verticalHeader()->setVisible(false);







}

TableForIed::~TableForIed()
{
    delete ui;
}

void TableForIed::on_tableWidgetSpi_cellDoubleClicked(int row, int column)
{
    // Необходимо условие, чтобы открывать таблицу модуля, только при нажатии на ячейку с Типом самого модуля, то есть только самая первая колонка
    if (column == 0) {
        vectorTableForModuleSpi[row]->show();
        vectorTableForModuleSpi[row]->updateTable(vectorTableSpiItem[row*5]->text());
    }
    else
        return;

}

void TableForIed::on_tableWidgetRs_cellDoubleClicked(int row, int column)
{
    // Необходимо условие, чтобы открывать таблицу модуля, только при нажатии на ячейку с Типом самого модуля, то есть только самая первая колонка
    if (column == 0) {
        vectorTableForModuleRs[row]->show();
        vectorTableForModuleRs[row]->updateTable(vectorTableRsItem[row*5]->text());
    }
    else
        return;
}

void TableForIed::insertRowsForSpi() {
    // Вместе с каждой новой строкой создаем новую таблицу, соответствующую модулю, который описывается в текущей строке
    //for(int i = 0; i < number; i++){
        ui->tableWidgetSpi->insertRow(ui->tableWidgetSpi->rowCount());
        vectorTableForModuleSpi.push_back(std::make_shared<TableForModule>());
        for (int j = 0; j < 5; j++) {
            // Также создаем новый указатель на каждую ячейку таблицы, и записываем в вектор ячеек таблицы
            vectorTableSpiItem.push_back(std::make_unique<QTableWidgetItem>(tr("%1").arg("")));
            ui->tableWidgetSpi->setItem(ui->tableWidgetSpi->rowCount()-1, j, vectorTableSpiItem[vectorTableSpiItem.size()-1].get());
        }
    //}
}

void TableForIed::insertRowsForRs() {
    // Вместе с каждой новой строкой создаем новую таблицу, соответствующую модулю, который описывается в текущей строке
    //for(int i = 0; i < number; i++){
        ui->tableWidgetRs->insertRow(ui->tableWidgetRs->rowCount());
        vectorTableForModuleRs.push_back(std::make_shared<TableForModule>());
        for (int j = 0; j < 5; j++) {
            // Также создаем новый указатель на каждую ячейку таблицы, и записываем в вектор ячеек таблицы
            vectorTableRsItem.push_back(std::make_unique<QTableWidgetItem>(tr("%1").arg("")));
            ui->tableWidgetRs->setItem(ui->tableWidgetRs->rowCount()-1, j, vectorTableRsItem[vectorTableRsItem.size()-1].get());
        }
    //}
}


