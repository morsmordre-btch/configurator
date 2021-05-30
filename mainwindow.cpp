#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0,5000,5000);

    GraphicsItem *r1 = new GraphicsItem();

    scene->addItem(r1);
    r1->setPos(QPointF(600,100));


}

MainWindow::~MainWindow()
{
    delete ui;
}
