#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include<QDebug>
#include "file_w.hpp"
#include <QTextEdit>
class worker: public QObject
{
    Q_OBJECT
    file_w* work;

public:
    worker( QTextEdit* text, QMutex* mutex, int* time1,  QVector<int> comands, QVector<QString> params);
private:
    int* time;
    QVector<int> comands;
    QVector<QString> params;
    QTime timer;
    QMutex* mutex;
    QTextEdit* text;
public slots:
    void process(){ 
        // Этот метод будет запущен при старте потока
        // Аллоцируем наш объект. Теперь это происходит в отдельном потоке
        work = new file_w(this->text, this->comands, this->params);
        if(work == nullptr) {
            // Если произошла ошибка, то сигнализируем что поток завершен с отрицательным результатом и покидаем функцию (а с ней и завершается поток)
            emit finished(false);
            return;
        }
        // Делаем сложную работу
        work->doWork();
        if(comands[2] == 2){
            while(this->time[0] != 0){
                qDebug()<<this->time[0];
                QThread::sleep(this->time[0]);
                this->mutex->lock();
                work->doWork();
                this->mutex->unlock();
            }
        }
        this->text->append("ПОТОК ЗАВЕРШИЛСЯ");
        // Сигнализируем об успешном выполнении
        emit finished(true);
    }


signals:
    void finished(bool);

};




#endif // WORKER_H
