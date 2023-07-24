#ifndef FILE_W_HPP
#define FILE_W_HPP

#include <QObject>
#include <iostream>
#include <QThread>

#include <QDebug>

#include <QFileInfo>
#include <QDir>
#include <QMutex>
#include <QTextEdit>
class file_w: public QObject
{
    Q_OBJECT
private:
    QVector<int> comands;//radiobattom
    QVector<QString> params;//lineedit
    QMap <QString, int> file_name;//входные файлы
    QMap <QString, int> file_name_1;//выходные файлы
    QVector<QString> files_1;//входные файлы
    QTextEdit* text;
public:
    file_w(QTextEdit* text, QVector<int> comands, QVector<QString> params);
    void file_write(QString file_name_1, QString file_name_2){// чтение входного файла, модификация и запись выходного
        QFile f_1("C:/Users/artem/Desktop/FIles/" + file_name_1);
        QByteArray arr_1;
        if(f_1.open(QIODevice::ReadOnly)){
            arr_1 = f_1.readAll();
            if(comands[0] == 1) {
                f_1.remove();
            }
            f_1.close();
        }
        else {
            f_1.close();
            return;
        }
        xor_(arr_1, params[2].toInt());
        qDebug() << params[1] + file_name_2;
        QString i(params[1] + file_name_2);
        f_1.setFileName(i);
        if(f_1.open(QIODevice::ReadWrite)){
            f_1.write(arr_1);
            f_1.close();
        }
    }
    void xor_(QByteArray& arr, int val){//XOR
        for(int i = 0; i < arr.size(); i++){
            arr[i] ^= val;
        }
    }

    void doWork() {

        if(comands[0] == 1 && !file_name.empty()){
            file_name.clear();
            files_1.clear();
        }
        this->text->append("NEW INPUT FILES");
        QDir mDir("C:/Users/artem/Desktop/FIles");//проверка новых входных файлов по маске
        foreach (const QFileInfo &mitm, mDir.entryInfoList(QStringList(params[0]))){
            if(file_name.contains(mitm.fileName())) continue;
            else{
                QString val = mitm.fileName();
                file_name.insert(val, 0);
                files_1.push_back(val);
                this->text->append(val);
            }
        }
        QDir mDir1(params[1]);
        this->text->append("NEW OUTPUT FILES");
        foreach (const QFileInfo &mitm, mDir1.entryInfoList(QStringList(params[0]))){//проверка новых выходных файлов по маске
            if(file_name_1.contains(mitm.fileName())){
                continue;
            }
            else{
                file_name_1.insert(mitm.fileName(), 0);
            }
        }
        for(int i = 0; i < files_1.size(); i++){// запись выходных файлов
            if(comands[1] == 2){
                while(file_name_1.contains(QString::number(++file_name[files_1[i]]) + "_" +  files_1[i]));
                file_write(files_1[i], QString::number(file_name[files_1[i]]) + "_" +  files_1[i]);
                this->text->append(QString::number(file_name[files_1[i]]) + "_" +  files_1[i]);
            }
            else {
                this->text->append(files_1[i]);
                file_write(files_1[i], files_1[i]);
            }
        }
    }

};

#endif // FILE_W_HPP
