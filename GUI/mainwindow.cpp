#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "lector.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString url = R"(C:\Users\porgois\Desktop\24.bmp)";
    QPixmap img(url);
    ui->label->setPixmap(img);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    std::string nombre;
    read("C:/Users/porgois/Desktop/", "24");

    QString url1 = R"(C:\Users\porgois\Desktop\24_edited.bmp)";
    QPixmap img1(url1);
    ui->label_2->setPixmap(img1);
}


