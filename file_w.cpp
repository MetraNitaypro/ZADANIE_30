#include "file_w.hpp"

file_w::file_w(QTextEdit* text, QVector<int> comands, QVector<QString> params)
{
    this->text = text;
    this->comands = comands;
    this->params = params;
}
