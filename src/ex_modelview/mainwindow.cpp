#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    
    exampleModel = new ExampleModel(this);
    
//    exampleModel->fillDataTableFromFile(fileName);
    
    ui->setupUi(this);
    ui->tableView->setModel(exampleModel);
    
    
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(loadFileSlot()));
    
}

void MainWindow::loadFileSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "/home/georgii/WORK",
                                                    "Images (*.csv)");
//    exampleModel->fillDataTable();
    delete exampleModel;
    exampleModel = new ExampleModel(this);
    exampleModel->fillDataTableFromFile(fileName);
    ui->tableView->setModel(exampleModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

