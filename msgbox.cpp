#include "msgbox.h"

/*****************************************************
* Class Name: MsgBox
******************************************************
*
* Summary:
* Выводит предупрежение или ошибку на экран. Текст
* передается в качестве аргументов, тип MsgBox
* также передается в качетсве аргумента
* Parameters:
* QString text - основной текст
* Qstring informativeText - доп. текст
* int typeMsg - тип сообщения (ошибка ERROR_MSG,
* предупреждение WARNING_MSG)
*
* Returns:
* -
******************************************************/
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
