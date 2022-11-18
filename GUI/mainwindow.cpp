#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "lector.cpp"
#include <QInputDialog>

std::string path, name, full_name, edited_name;

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

void MainWindow::on_leer_clicked()
{
   //creates variables path and name for future use.
   QString Qpath = QInputDialog::getText(this, " ", "Enter path:");
   path = Qpath.toStdString();

   QString Qname = QInputDialog::getText(this, " ", "Enter name:");
   name = Qname.toStdString();

   //sets full_name.
   full_name = path + name + ".bmp";

   //display the image read.
   QString url = full_name.c_str();
   QPixmap img(url);
   ui->imagen->setPixmap(img);

   //Align Image to center.
   ui->imagen->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_negative_clicked()
{
    //c++ function to interpret and edit image at path/name.bmp.
    read(path, name);

    //sets filter image to the edited one.
    edited_name = path + name + "_edited.bmp";
    std::cout << "edited name: " << edited_name << std::endl;

    //displays the edited image.
    QString url1 = edited_name.c_str();
    QPixmap img1(url1);
    ui->imagen_editada->setPixmap(img1);

    //Align Image to center.
    ui->imagen_editada->setAlignment(Qt::AlignCenter);

}

//Ejemplo PATH: C:/Users/porgois/Desktop/ (nombre de archivo sin extension)

