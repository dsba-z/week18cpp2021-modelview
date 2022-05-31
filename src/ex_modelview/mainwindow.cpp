#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    examplemodel = new ExampleModel(this);
    ui->tableView->setModel(examplemodel);
    
    
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(loadFileSlot()));
    QObject::connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(slotName(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::loadFileSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "..",
                                                    "Data (*.csv)");
    
    delete examplemodel;
    
    examplemodel = new ExampleModel(this);
    examplemodel->fillDataTableFromFile(fileName);
    
    ui->tableView->setModel(examplemodel);
    
}

void MainWindow::slotName(const QModelIndex &index)
{
    int row = index.row();
    int column = 5;
    
    QModelIndex ageIndex = examplemodel->index(row, column);
    
    QVariant ageData = examplemodel->data(ageIndex);
    
    ui->labelAgeData->setText(ageData.toString());
}

