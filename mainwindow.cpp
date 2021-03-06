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

    dir.mkdir("export");
    dir.mkdir("import");
    nameXmlFile = "192_168_0_1.xml";
    pathToXmlFile = "./import/" + nameXmlFile;

    // Устанавливаем шрифт текста
    //QFont font;
    int id = QFontDatabase::addApplicationFont("/home/isault/.fonts/GOST/GOST2304_TypeB.ttf"); // TODO
    QStringList GOST_TypeB = QFontDatabase::applicationFontFamilies(id);
    // Если GOST Type B недоступен, то по-умолчанию Arial
    if (id == -1)
    {
        font.setFamily("Arial");
        font.setPointSize(14);
        font.setWeight(QFont::Normal);
        font.setItalic(true);
    }
    else
    {
        font.setFamily(GOST_TypeB.at(0));
        font.setPointSize(16);
        font.setWeight(QFont::Normal);
        font.setItalic(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Создаем вектор указателей на контекстное меню, который потом передаем в объект GraphicsController
    //std::shared_ptr<QMenu> contextMenu = std::make_shared<QMenu>();
    // Новый созданный объект помещаем в вектор, чтобы можно было удалять их и тд
    systemVector.push_back(std::make_unique<SystemGroup>());
    systemVector.back()->setFont(font);

    //controllerVector.push_back(std::make_unique<GraphicsController>());

    connect(systemVector.back()->cntrl.get(),
            //graphicsItemVector.[GraphicsController::itemsCounter-1].get(),
            &GraphicsController::signalDel,
            this,
            &MainWindow::slotDeleteFromVector
    );
    connect(systemVector.back()->cntrl.get(),
            //graphicsItemVector[GraphicsController::itemsCounter-1].get(),
            static_cast<void(GraphicsController::*)(int)>(&GraphicsController::signalExportXml),
            this,
            static_cast<void(MainWindow::*)(int)>(&MainWindow::slotExportXml)
    );
    connect(systemVector.back()->cntrl.get(),
            //graphicsItemVector[GraphicsController::itemsCounter-1].get(),
            static_cast<void(GraphicsController::*)(int)>(&GraphicsController::signalImportXml),
            this,
            static_cast<void(MainWindow::*)(int)>(&MainWindow::slotImportXml)
    );

//    systemVector.back()->addToGroup(controllerVector.back().get());
//    controllerVector.back()->setPos({0, 0});
//    // test
//    controllerVector.back()->graphicsModuleVector.push_back(std::make_unique<GraphicsModule>("AI-1",
//                                                                    this->x() - 30,
//                                                                    this->y() + 30));
//    controllerVector.back()->graphicsModuleVector.push_back(std::make_unique<GraphicsModule>("AI-2",
//                                                                    this->x() - 30,
//                                                                    this->y() + 30*2));
//    controllerVector.back()->graphicsModuleVector.push_back(std::make_unique<GraphicsModule>("AI-3",
//                                                                    this->x() - 30,
//                                                                    this->y() + 30*3));

//    int i = 1;
//    for(auto& module : controllerVector.back()->graphicsModuleVector)
//    {
//        systemVector.back()->addToGroup(module.get());

//        module.get()->setParentItem(controllerVector.back().get());
//        module.get()->setPos(QPointF(-30, +35*i));
//        i++;
//    }
//    systemVector.back()->setHandlesChildEvents(false);

    scene->addItem(systemVector.back().get());
}

void MainWindow::on_pushButton_2_clicked()
{
    if (GraphicsController::itemsCounter == 0) {
        MsgBox("Нет графических элементов для удаления.",
               "",
               WARNING_MSG);
        return;
    }
    else
    {
        scene->removeItem(systemVector.back().get());
        systemVector.pop_back();
        //controllerVector.pop_back();
    }
}

/* Пофиксить нумерацию КП при удалении и последующим добавлением */

void MainWindow::slotDeleteFromVector(int itemCount)
{
    scene->removeItem(systemVector.at(itemCount).get());

    systemVector.erase(systemVector.begin() + itemCount);
    //controllerVector.erase(controllerVector.begin() + itemCount);

    // Перенумерация КП
    for(std::size_t i = 0; i < systemVector.size(); i++)
    {
        systemVector.at(i)->setItemIndex(i);
    }
}

QToolBar *MainWindow::createToolBar() {
    QToolBar *toolBar = new QToolBar("Tool Bar", this );
    toolBar->addAction(QPixmap(":/save.png"), "Сохранить", this, SLOT(slotSave()));
    toolBar->addAction(QPixmap(":/savexml.png"), "Парсинг XML-файла", this, SLOT(slotParsingXml()));
    toolBar->addAction(QPixmap(":/formxml.png"), "Формирование XML-файла", this, SLOT(slotFormingXml()));
    toolBar->addAction(QPixmap(":/import.png"), "Прием XML-файла", this, SLOT(slotImportXml()));
    toolBar->addAction(QPixmap(":/export.png"), "Отправка XML-файла", this, SLOT(slotExportXml()));
    return toolBar;
}

void MainWindow::slotParsingXml() {
    if (GraphicsController::itemsCounter == 0)
    {
        MsgBox("Добавьте контроллер для записи данных XML-файла.",
               "",
               WARNING_MSG);
        return;
    }
    else
    {


        for (std::size_t i = 0; i < systemVector.size(); i++)
        {
            pathToXmlFile = "./import/" + systemVector.at(i)->cntrl->getIp().replace('.','_') + ".xml";
            XmlParser parser(systemVector.at(i).get(), pathToXmlFile);

            //parser.scene_->addItem(graphicsItemVector[GraphicsController::itemsCounter-1]->graphicsModuleVector[0].get());
        }
    }
    qDebug() << "parsing XML shit \n";
}

void MainWindow::slotFormingXml() {
    qDebug() << "forming XML shit \n";
}



/******************************************************
*
* Слот отправки XML файла, вызываемый нажатием кнопки
* в контекстном меню контроллера. Отправка XML файла
* происходит только по IP адресу этого контроллера
*
******************************************************/
void MainWindow::slotExportXml(int itemCount) {
    if ( exportXml(itemCount) ) {
        MsgBox("Экспорт XML-файла завершен.",
               "",
               INFO_MSG);
    }
    else {
        MsgBox("Экспорт XML-файла не был произведен.",
               "Попробуйте еще раз.",
               ERROR_MSG);
    }
}

/******************************************************
*
* Слот отправки XML файла, вызываемый нажатием кнопок
* в главном меню программы. Отправка XML файла
* происходит для всех контроллеров, добавленных на
* графическую сцену
*
******************************************************/
void MainWindow::slotExportXml() {
    if ( exportXml(ALL_ITEM) ) {
        MsgBox("Экспорт XML-файла завершен.",
               "",
               INFO_MSG);
    }
    else {
        MsgBox("Экспорт XML-файла не был произведен.",
               "Попробуйте еще раз.",
               ERROR_MSG);
    }
}

/******************************************************
*
* Слот приема XML файла, вызываемый нажатием кнопки
* в контекстном меню контроллера. Прием XML файла
* происходит только с этого контроллера с текущим
* IP адресом
*
******************************************************/
void MainWindow::slotImportXml(int itemCount) {
    if ( importXml(itemCount) ) {
        MsgBox("Импорт XML-файла завершен.",
               "",
               INFO_MSG);
    }
    else {
        MsgBox("Импорт XML-файла не был произведен.",
               "Попробуйте еще раз.",
               ERROR_MSG);
    }
}

/******************************************************
*
* Слот приема XML файла, вызываемый нажатием кнопок
* в главном меню программы. Прием XML файла
* происходит со всех контроллеров, добавленных
* на графическую сцену
*
******************************************************/
void MainWindow::slotImportXml() {
    if ( importXml(ALL_ITEM) ) {
        MsgBox("Импорт XML-файла завершен.",
               "",
               INFO_MSG);
    }
    else {
        MsgBox("Импорт XML-файла не был произведен.",
               "Попробуйте еще раз.",
               ERROR_MSG);
    }
}

bool MainWindow::exportXml(int itemCount) {
    if (itemCount == ALL_ITEM) {

    }
    else {
        SshCommands ssh;
        ssh.setIp(controllerVector[itemCount].get()->getIp());
        ssh.setLogin(controllerVector[itemCount].get()->getLogin());
        ssh.setPassword(controllerVector[itemCount].get()->getPassword());
        ssh.setPort("3333");
        return ssh.exportFile(pathToXmlFile, "/mnt/hdd/k0nstable_fold/test/import/");
    }
}

bool MainWindow::importXml(int itemCount) {
    if (itemCount == ALL_ITEM) {

    }
    else {
        SshCommands ssh;
        ssh.setIp(controllerVector[itemCount].get()->getIp());
        ssh.setLogin(controllerVector[itemCount].get()->getLogin());
        ssh.setPassword(controllerVector[itemCount].get()->getPassword());
        ssh.setPort("3333");
        return ssh.importFile("/mnt/hdd/k0nstable_fold/test/export/export.xml", "./import/");
    }

}

/*****************************************************
* Function Name: createMenuBar
******************************************************
*
* Summary:
* Создает указатель на меню-бар, в этом меню-баре
* добавляются разделы "Файл" и "Инструменты"
* Parameters:
*
* Returns:
* Возвращает указатель на созданный меню-бар
*
******************************************************/
QMenuBar *MainWindow::createMenuBar() {
    QMenuBar *menuBar = new QMenuBar(this);

    menuBar->addMenu(createSubMenuBarFile());
    menuBar->addMenu(createSubMenuBarTools());

    return menuBar;
}



QMenu *MainWindow::createSubMenuBarTools() {
    QMenu *menu = new QMenu("Инструменты", this);
    menu->addAction("Парсинг XML-файла", this, SLOT(slotParsingXml()));
    menu->addAction("Формирование XML-файла", this, SLOT(slotFormingXml()));
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







