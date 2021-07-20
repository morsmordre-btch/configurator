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
    std::vector<std::shared_ptr<GraphicsItem>> graphicsItemVector;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
