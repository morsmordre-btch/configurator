#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Задаем название главного окна приложения

    this->setWindowTitle("Конфигуратор устройств АСУ ТП");


    addToolBar(Qt::TopToolBarArea, createToolBar());
    setMenuBar(createMenuBar());

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
    // Создаем вектор указателей на контекстное меню, который потом передаем в объект GraphicsItem
    std::shared_ptr<QMenu> contextMenu = std::make_shared<QMenu>();
    // Новый созданный объект помещаем в вектор, чтобы можно было удалять их и тд
    graphicsItemVector.push_back(std::make_unique<GraphicsItem>(/*contextMenu*/));
    connect(
            graphicsItemVector[GraphicsItem::itemsCounter-1].get(),
            &GraphicsItem::signalDel,
            this,
            &MainWindow::slotDeleteFromVector
    );
    scene->addItem(graphicsItemVector[GraphicsItem::itemsCounter-1].get());

}

void MainWindow::on_pushButton_2_clicked()
{
    graphicsItemVector.pop_back();
}

/* Пофиксить нумерацию КП при удалении и последующим добавлением */

void MainWindow::slotDeleteFromVector(int itemCount)
{
    graphicsItemVector.erase(graphicsItemVector.begin() + itemCount - 1);
}

QToolBar *MainWindow::createToolBar() {
    QToolBar *toolBar = new QToolBar("Tool Bar", this );

    toolBar->addAction(QPixmap(":/save.png"), "Сохранить", this, SLOT(slotSave()));
    toolBar->addAction(QPixmap(":/import.png"), "Прием XML-файла", this, SLOT(slotImportXml()));
    toolBar->addAction(QPixmap(":/export.png"), "Отправка XML-файла", this, SLOT(slotExportXml()));
    return toolBar;
}

void MainWindow::slotExportXml() {
    qDebug() << "export XML shit \n";
}

void MainWindow::slotImportXml() {
    qDebug() << "import XML shit \n";
}

QMenuBar *MainWindow::createMenuBar() {
    QMenuBar *menuBar = new QMenuBar(this);

    menuBar->addMenu(createSubMenuBarFile());
    menuBar->addMenu(createSubMenuBarTools());

    return menuBar;
}

QMenu *MainWindow::createSubMenuBarTools() {
    QMenu *menu = new QMenu("Инструменты", this);
    menu->addAction("Прием XML-файла", this, SLOT(slotImportXml()));
    menu->addAction("Отправка XML-файла", this, SLOT(slotExportXml()));
    return menu;
}

QMenu *MainWindow::createSubMenuBarFile() {
    QMenu *menu = new QMenu("Файл", this);
    menu->addAction("Сохранить", this, SLOT(slotSave()));
    menu->addAction("Выйти", this, SLOT(slotQuit()));
    return menu;
}

void MainWindow::slotSave() {
    qDebug() << "save \n";
}

void MainWindow::slotQuit() {
    qDebug() << "quit \n";
    QApplication::quit();
}







