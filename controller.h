#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QMutex>
#include "worker.h"
#include <QTextEdit>
class controller: public QObject
{
    Q_OBJECT
private:
    int* time;
    QVector<int> comands;
    QVector<QString> params;
    QMutex* mutex;
    QTextEdit* text;
public:
    controller(QTextEdit* text, QMutex* mutex, int* time1, QVector<int> comands, QVector<QString> params);
    void makeThread(){
        worker* Worker = new  worker(this->text, mutex, this->time, this->comands, this->params);
        QThread* thread = new QThread();
        Worker->moveToThread(thread);
        // При запуске потока запускаем выполнение метода Worker::process()
        QObject::connect(thread, &QThread::started, Worker, &worker::process);
        // Также, по сигналу finished отправляем команду на завершение потока
        QObject::connect(Worker, &worker::finished, thread, &QThread::quit);
        // А потом удаляем экземпляр обработчика
        QObject:: connect(Worker, &worker::finished, Worker, &QObject::deleteLater);
        // И наконец, когда закончит работу поток, удаляем и его
        QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);
        thread->start();
    }

};

#endif // CONTROLLER_H
