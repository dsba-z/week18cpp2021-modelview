#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    examplemodel = new ExampleModel(this);
    ui->tableView->setModel(examplemodel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

