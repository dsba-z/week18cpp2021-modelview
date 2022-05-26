#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(loadDataSlot()));
    
    exampleModel = new ExampleModel(this);
    
    ui->tableView->setModel(exampleModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loadDataSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "/home/georgii/WORK/DSBA2021cpp/workshops/week18/workshops-mvc/data/",
                                                    "Data (*.csv)");
    delete exampleModel;
    exampleModel = new ExampleModel(this);
    
    exampleModel->loadDataFromFile(fileName);
    ui->tableView->setModel(exampleModel);

    
    
    
}
