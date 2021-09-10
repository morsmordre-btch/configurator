#ifndef TABLEFORMODULE_H
#define TABLEFORMODULE_H

#include <QDialog>
#include <QComboBox>
#include <memory>

namespace Ui {
class TableForModule;
}

class TableForModule : public QDialog
{
    Q_OBJECT

public:
    explicit TableForModule(int numberOfTypeModule, QWidget *parent = nullptr);
    ~TableForModule();

    // Создаем вектор комбо боксов
    std::vector<std::unique_ptr<QComboBox>> vectorComboBox;
private:
    Ui::TableForModule *ui;
};

#endif // TABLEFORMODULE_H
