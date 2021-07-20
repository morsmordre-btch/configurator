#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Задаем название главного окна приложения

    this->setWindowTitle("Конфигуратор устройств АСУ ТП");

    // Настройка графической сцены для отображения графических объектов
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0,5000,5000);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Новый созданный объект помещаем в вектор, чтобы можно было удалять их и тд
    graphicsItemVector.push_back(std::make_shared<GraphicsItem>());
    scene->addItem(graphicsItemVector[GraphicsItem::itemsCounter-1].get());
    //graphicsItemVector[0]->setPos(100,100);
}


void MainWindow::on_pushButton_2_clicked()
{
    graphicsItemVector.pop_back();
}
