#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);//Lance le constructeur de la fenêtre.
}

MainWindow::~MainWindow()
{
    delete ui;
}
