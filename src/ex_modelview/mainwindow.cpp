#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addrowdialog.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadFile()));
    QObject::connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
    QObject::connect(ui->addRowButton, SIGNAL(clicked()), this, SLOT(addRowSlot()));
    QObject::connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(loadFile()));
    QObject::connect(ui->nameFilterlineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateFilter(const QString &)));
    
    
    
    _exampleModel = new ExampleModel(this);
    ui->tableView->setModel(_exampleModel);
    
    proxyModel = new QSortFilterProxyModel(this);

    // _transposeModel = new QTransposeProxyModel(this);
    proxyModel->setSourceModel(_exampleModel);
    ui->tableDetailsView->setModel(proxyModel);
    ui->tableDetailsView->setSortingEnabled(true);

    // proxyModel->sort(2, Qt::AscendingOrder);
    proxyModel->setFilterKeyColumn(3);



// A common use case is to let the user specify the filter regular expression, wildcard pattern, or fixed string in a QLineEdit and to connect the textChanged() signal to setFilterRegularExpression(), setFilterWildcard(), or setFilterFixedString() to reapply the filter.

    _shownDetailsColumn = 0;
}

void MainWindow::updateFilter(const QString & text)
{
    proxyModel->setFilterWildcard(text);
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
    proxyModel->setSourceModel(_exampleModel);

}


void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Open File",
                                                    "../",
                                                    "Data (*.csv)");
    _exampleModel->saveDataTableToFile(fileName);

}

void MainWindow::addRowSlot()
{
    AddRowDialog d(this);
    if (d.exec() == QDialog::Accepted)
    {
        _exampleModel->appendRow(d.getNewRow());
        // ui->tableDetailsView->hideColumn(proxyModel->columnCount() - 1);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinBox_valueChanged(int value)
{
    // ui->tableDetailsView->hideColumn(_shownDetailsColumn);
    // _shownDetailsColumn = value;
    // ui->tableDetailsView->setColumnHidden(value, false);
}


void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    
}

