#include "controller.h"

controller::controller(QTextEdit *text, QMutex* mutex, int* time1,  QVector<int> comands, QVector<QString> params)
{
    this->text = text;
    this->mutex = mutex;
    this->time = time1;
    this->comands = comands;
    this->params = params;
}
