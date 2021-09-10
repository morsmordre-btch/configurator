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

    // Создаем окно для таблицы модулей




    // Вместе с каждой новой строкой создаем новую таблицу, соответствующую модулю, который описывается в текущей строке
    for(int i = 0; i < 1; i++){
        ui->tableWidgetSpi->insertRow(i);
        vectorTableForModule.push_back(std::make_shared<TableForModule>(i));
        for (int j = 0; j < 4; j++) {
            // Также создаем новый указатель на каждую ячейку таблицы, и записываем в вектор ячеек таблицы
            vectorTableItem.push_back(std::make_unique<QTableWidgetItem>(tr("%1").arg("")));
            ui->tableWidgetSpi->setItem(i, j, vectorTableItem[vectorTableItem.size()-1].get());
        }
    }
    vectorTableItem[0]->setText("AI-A");
    vectorTableItem[1]->setText("AI-B");
}

TableForIed::~TableForIed()
{
    delete ui;
}

void TableForIed::on_tableWidgetSpi_cellDoubleClicked(int row, int column)
{
    // Необходимо условие, чтобы открывать таблицу модуля, только при нажатии на ячейку с Типом самого модуля, то есть только самая первая колонка
    if (column == 0)
        vectorTableForModule[row]->show();
    else
        return;

}
