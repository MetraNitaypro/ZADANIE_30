#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QDebug>
#include <QMutex>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_1_1_clicked();

    void on_radioButton_1_2_clicked();

    void on_radioButton_2_1_clicked();

    void on_radioButton_2_2_clicked();

    void on_radioButton_3_1_clicked();

    void on_radioButton_3_2_clicked();

private:
    Ui::MainWindow *ui;
    QVector<int> comands;
    QMutex mutex;
    QVector<int> times;
};
#endif // MAINWINDOW_H
