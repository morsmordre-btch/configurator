#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <graphicsitem.h>
#include <tableforied.h>
#include <vector>
#include <memory>
#include <QMenu>
#include <QToolBar>
#include <QMenuBar>
#include <xmlparser.h>


#define ALL_ITEM -1


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:   
    QGraphicsScene *scene;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Создаем вектор графических объектов
    std::vector<std::unique_ptr<GraphicsItem>> graphicsItemVector;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public slots:
    void slotDeleteFromVector(int itemCount);

    /**************************************************************
     *
     *        Слоты для обработки нажатий menuBar и toolBar
     *
     **************************************************************/
    // Слоты для обработки нажатия на отправку, либо прием XML-файла //
    void slotExportXml(int itemCount);
    void slotExportXml();
    void slotImportXml(int itemCount);
    void slotImportXml();
    // Слоты для обработки нажатия на парсинг, либо формирование XML-файла //
    void slotParsingXml();
    void slotFormingXml();
    // Слоты для обработки нажатия Сохранить, Выйти //
    void slotSave();
    void slotQuit();


private:
    QPixmap exportPix;

    QToolBar *createToolBar();
    QMenuBar *createMenuBar();
    QMenu *createSubMenuBarFile();
    QMenu *createSubMenuBarTools();

    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
