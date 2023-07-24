#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->comands.append(1);
    this->comands.append(1);
    this->comands.append(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QVector<QString> params;
    params.append(ui->lineEdit_1->text());
    params.append(ui->lineEdit_2->text());
    params.append(ui->lineEdit_4->text());
    bool tag;
    if(!this->times.empty()) this->times[this->times.size() - 1] = 0;
    this->times.push_back(ui->lineEdit_3->text().toInt(&tag));
    if(tag){
        controller ctrl(ui->textEdit,&this->mutex, &this->times[this->times.size() - 1], this->comands, params);
        ctrl.makeThread();
    }

}

void MainWindow::on_radioButton_1_1_clicked()
{
    this->comands[0] = 1;
}


void MainWindow::on_radioButton_1_2_clicked()
{
    this->comands[0] = 2;
}


void MainWindow::on_radioButton_2_1_clicked()
{
    this->comands[1] = 1;
}


void MainWindow::on_radioButton_2_2_clicked()
{
    this->comands[1] = 2;
}


void MainWindow::on_radioButton_3_1_clicked()
{
    this->comands[2] = 1;
}


void MainWindow::on_radioButton_3_2_clicked()
{
    this->comands[2] = 2;
}

