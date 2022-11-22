#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "lector.cpp"
#include <QInputDialog>
#include <QFileDialog>

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
   QString file_name = QFileDialog::getOpenFileName(this, tr(""), "C://", "Image File (*.BMP)");
   size_t found_slash, found_dot;

   std::string full_path = file_name.toStdString();
   found_slash = full_path.find_last_of("/\\");

   //get path and name substring from "full_path"
   path = full_path.substr(0, found_slash) + "/";
   name = full_path.substr(found_slash+1);
   found_dot = name.find_last_of(".");
   name = name.substr(0, found_dot);

   //read the image specificied by path and name.
   read(path, name);

   //display the image read.
   QString url = file_name;
   QPixmap img(url);
   ui->imagen->setPixmap(img);

   //Align Image to center.
   ui->imagen->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_negative_clicked()
{
    //c++ function to edit image at path/name.bmp.
    apply_negative(path, name);

    //sets filter image to the edited one.
    edited_name = path + name + "_edited.BMP";

    //displays the edited image.
    QString url1 = edited_name.c_str();
    QPixmap img1(url1);
    ui->imagen_editada->setPixmap(img1);

    //Align Image to center.
    ui->imagen_editada->setAlignment(Qt::AlignCenter);
}


