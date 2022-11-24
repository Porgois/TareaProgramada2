#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "lector.cpp"
#include <QInputDialog>
#include <QFileDialog>


std::string name, full_name, edited_name;

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

   //read the image specified by path and name.
   read(path, name);

   //display the image read.
   QString url = file_name;
   QPixmap img(url);
   ui->imagen->setPixmap(img);

   //Align Image to center.
   ui->imagen->setAlignment(Qt::AlignCenter);

   //Scale Image.
   ui->imagen->setScaledContents(true);

}

void MainWindow::on_negative_clicked()
{

    apply_negative(path, name);

    //Traductor para C++ <---> NASM.
    translateCPP(pixels, vacio);

    //Apply new colors to image
    image.getColors() = vacio;

    //Export image with  newly-edited colors
    image.Export(path + file_name + "_edited.BMP");

    //sets filter image to the edited one.
    edited_name = path + name + "_edited.BMP";

    //displays the edited image.
    QString url1 = edited_name.c_str();
    QPixmap img1(url1);
    ui->imagen_editada->setPixmap(img1);

    //Align Image to center.
    ui->imagen_editada->setAlignment(Qt::AlignCenter);

    //Scale Image.
    ui->imagen_editada->setScaledContents(true);
}

void MainWindow::on_brightnessPlus_clicked()
{

    //Sets brillo to SpinBox Value.
    int brillo = (int)ui->spinBox->value();

    //c++ function to edit image at path/name.bmp.
    apply_brilloAdd(path, name, brillo);

    //sets filter image to the edited one.
    edited_name = path + name + "_edited.BMP";

    //displays the edited image.
    QString url1 = edited_name.c_str();
    QPixmap img1(url1);
    ui->imagen_editada->setPixmap(img1);

    //Align Image to center.
    ui->imagen_editada->setAlignment(Qt::AlignCenter);

    //Scale Image.
    ui->imagen_editada->setScaledContents(true);
}

void MainWindow::on_contrast_clicked()
{
    //c++ function to edit image at path/name.bmp.
    apply_contrast(path, name);

    //sets filter image to the edited one.
    edited_name = path + name + "_edited.BMP";

    //displays the edited image.
    QString url1 = edited_name.c_str();
    QPixmap img1(url1);
    ui->imagen_editada->setPixmap(img1);

    //Align Image to center.
    ui->imagen_editada->setAlignment(Qt::AlignCenter);

    //Scale Image.
    ui->imagen_editada->setScaledContents(true);
}

/*
Referencias:
1) "Qt Tutorials For Beginners 23 - QFileDialog", ProgrammingKnowledge:
https://www.youtube.com/watch?v=Fgt4WWdn3Ko&ab_channel=ProgrammingKnowledge
*/

void MainWindow::on_brightnessLess_clicked()
{

    //Sets brillo to SpinBox Value.
    int brillo = (int)ui->spinBox->value();

    //c++ function to edit image at path/name.bmp.
    apply_brilloSub(path, name, brillo);

    //sets filter image to the edited one.
    edited_name = path + name + "_edited.BMP";

    //displays the edited image.
    QString url1 = edited_name.c_str();
    QPixmap img1(url1);
    ui->imagen_editada->setPixmap(img1);

    //Align Image to center.
    ui->imagen_editada->setAlignment(Qt::AlignCenter);

    //Scale Image.
    ui->imagen_editada->setScaledContents(true);
}

