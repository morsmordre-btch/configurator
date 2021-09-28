#include "msgbox.h"

MsgBox::MsgBox(QString text, QString informativeText, int typeMsg)
{
    this->text = text;
    this->informativeText = informativeText;

    switch (typeMsg) {
        case ERROR_MSG:
            showErrorMsgBox();
            break;
        case WARNING_MSG:
            showWarningMsgBox();
            break;
    }

}

void MsgBox::showWarningMsgBox() {
    setWindowTitle("Предупреждение");
    setText(text);
    setInformativeText(informativeText);
    exec();
}

void MsgBox::showErrorMsgBox() {
    setWindowTitle("Ошибка");
    setText(text);
    setInformativeText(informativeText);
    exec();
}
