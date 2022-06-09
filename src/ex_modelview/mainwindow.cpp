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
    QObject::connect(ui->lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(updateFilter2(const QString &)));
    
    QObject::connect(ui->fareFromSlider, SIGNAL(valueChanged(int)), this, SLOT(updateFilterMinFare(int)));
    QObject::connect(ui->fareToSlider, SIGNAL(valueChanged(int)), this, SLOT(updateFilterMaxFare(int)));

    
    _exampleModel = new ExampleModel(this);
//    ui->tableView->setModel(_exampleModel);
    
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel2 = new QSortFilterProxyModel(this);
    proxyModelFare = new CustomProxyModel(this);
    
    // _transposeModel = new QTransposeProxyModel(this);
    proxyModel->setSourceModel(_exampleModel);
    proxyModel2->setSourceModel(proxyModel);
    proxyModelFare->setSourceModel(proxyModel2);
    
    ui->tableDetailsView->setModel(proxyModelFare);
    ui->tableDetailsView->setSortingEnabled(true);

    // proxyModel->sort(2, Qt::AscendingOrder);
    proxyModel->setFilterKeyColumn(3);
    proxyModel2->setFilterKeyColumn(0);

// A common use case is to let the user specify the filter regular expression, wildcard pattern, or fixed string in a QLineEdit and to connect the textChanged() signal to setFilterRegularExpression(), setFilterWildcard(), or setFilterFixedString() to reapply the filter.
    
    
}

void MainWindow::updateFilterMinFare(int value)
{
    proxyModelFare->setFilterMinimumFare(value);
    
}

void MainWindow::updateFilterMaxFare(int value)
{
    proxyModelFare->setFilterMaximumFare(value);
    
}

void MainWindow::updateFilter(const QString & text)
{
    proxyModel->setFilterWildcard(text);
}
void MainWindow::updateFilter2(const QString & text)
{
    proxyModel2->setFilterFixedString(text);
}


void MainWindow::loadFile()
{
    delete _exampleModel;
    
    _exampleModel = new ExampleModel(this);
    QString fileName = QFileDialog::getOpenFileName(this, "Open File",
                                                    "../",
                                                    "Data (*.csv)");
    _exampleModel->fillDataTableFromFile(fileName);
    
//    ui->tableView->setModel(_exampleModel);
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

