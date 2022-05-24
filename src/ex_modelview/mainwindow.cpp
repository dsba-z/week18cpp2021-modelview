#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    exampleModel = new ExampleModel(this);
    
    ui->tableView->setModel(exampleModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

