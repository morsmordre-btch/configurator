#ifndef TABLEFORIED_H
#define TABLEFORIED_H

#include <QDialog>


namespace Ui {
class TableForIed;
}

class TableForIed : public QDialog
{
    Q_OBJECT

public:
    explicit TableForIed(int itemCount, QWidget *parent = nullptr);
    ~TableForIed();

private:
    Ui::TableForIed *ui;
};

#endif // TABLEFORIED_H
