#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_negative_clicked();
    void on_leer_clicked();

    void on_brightnessPlus_clicked();

    void on_contrast_clicked();

    void on_brightnessLess_clicked();

    void on_mirrored_clicked();

    void pochita();

    void on_pochita_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
