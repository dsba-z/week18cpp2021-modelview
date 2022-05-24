#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    exampleModel = new ExampleModel(this);
    ui->setupUi(this);
    ui->tableView->setModel(exampleModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

