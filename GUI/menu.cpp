#include "menu.h"
#include "ui_menu.h"
#include <iostream>

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);

    //carga la imagen base en original.
    QString url = R"(C:\Users\porgois\Desktop\koala.bmp)";
    QPixmap img(url);
    ui->porg->setPixmap(img); //usar setPixmap para cambiar la imagen.

    //carga la imagen "blank" en editada.
    QString orl = R"(C:\Users\porgois\Desktop\blank.bmp)";
    QPixmap imag(orl);
    ui->nev->setPixmap(imag); //usar setPixmap para cambiar la imagen.
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_b_negativo_clicked()
{
    std::cout<<"Negativo\n";
    QString url = R"(C:\Users\porgois\Desktop\koala_negativo.bmp)"; //carga la imagen generada por el programa C++ y NASM.
    QPixmap img(url);
    ui->nev->setPixmap(img); //usar setPixmap para cambiar la imagen.
}

void Menu::on_b_borrar_clicked()
{
    QString orl = R"(C:\Users\porgois\Desktop\blank.bmp)";
    QPixmap imag(orl);
    ui->nev->setPixmap(imag); //usar setPixmap para cambiar la imagen.
}

