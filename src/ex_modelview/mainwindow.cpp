#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    
    exampleModel = new ExampleModel(this);
    
    ui->setupUi(this);
    ui->tableView->setModel(exampleModel);
    
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(loadFileSlot()));
//    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(loadFileSlot()));
    QObject::connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeCurrentRowSlot(QModelIndex)));
}

void MainWindow::loadFileSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "../", "Images (*.csv)");
    delete exampleModel;
    exampleModel = new ExampleModel(this);
    exampleModel->fillDataTableFromFile(fileName);
    ui->tableView->setModel(exampleModel);
}

void MainWindow::changeCurrentRowSlot(const QModelIndex &index) // also add this to mainwindow.h
{
    
    int row = index.row();
    int column = 5;
    
    QModelIndex ageIndex = exampleModel->index(row, column);
    QVariant ageData = exampleModel->data(ageIndex);
    ui->ageLabel->setText(ageData.toString());
    
    
    QModelIndex dataIndex = exampleModel->index(row, 10);
    QVariant dataData = exampleModel->data(dataIndex);
    ui->dataLabel->setText(dataData.toString());
    
}

MainWindow::~MainWindow()
{
    delete ui;
}
