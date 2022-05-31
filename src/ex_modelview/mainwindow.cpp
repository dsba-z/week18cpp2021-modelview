#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadFile()));
    QObject::connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadFile()));
    
    _exampleModel = new ExampleModel(this);
    ui->tableView->setModel(_exampleModel);
}


void MainWindow::loadFile()
{
    delete _exampleModel;
    
    _exampleModel = new ExampleModel(this);
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "../",
                                                    "Data (*.csv)");
    _exampleModel->fillDataTableFromFile(fileName);
    
    ui->tableView->setModel(_exampleModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

