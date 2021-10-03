#ifndef MSGBOX_H
#define MSGBOX_H

#include <QMessageBox>

#define ERROR_MSG 0
#define WARNING_MSG 1
#define INFO_MSG 2

class MsgBox : public QMessageBox
{
public:
    MsgBox(QString text, QString informativeText, int typeMsg);

private:
    QString text;
    QString informativeText;
    void showWarningMsgBox();
    void showErrorMsgBox();
    void showInfoMsgBox();
};

#endif // MSGBOX_H
