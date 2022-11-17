#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "lector.cpp"
#include <QInputDialog>

std::string path, name;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //c++ function to interpret and edit image at path/name.bmp
    read(path, name);

    //sets filter image to the edited one.
    QString url1 = R"(path + name + "_edited.bmp")";
    QPixmap img1(url1);
    ui->label_2->setPixmap(img1);
}

void MainWindow::on_ingresar_clicked()
{
   QString Qpath = QInputDialog::getText(this, " ", "Enter path:");
   path = Qpath.toStdString();

   QString Qname = QInputDialog::getText(this, " ", "Enter name:");
   name = Qname.toStdString();

   //sets image to the one read
   QString url = R"(path + name + ".bmp")";
   QPixmap img(url);
   ui->label->setPixmap(img);
}

