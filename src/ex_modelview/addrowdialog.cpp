#include "addrowdialog.h"
#include "ui_addrowdialog.h"
#include <QMessageBox>

AddRowDialog::AddRowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRowDialog)
{
    ui->setupUi(this);
    
    ui->comboBox->addItem("1", 1);
    ui->comboBox->addItem("2", 2);
    ui->comboBox->addItem("3", 3);
    
    QObject::connect(ui->okButton, SIGNAL(clicked()), this, SLOT(saveAddedRow()));
    QObject::connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void AddRowDialog::saveAddedRow()
{
    newRow.push_back(ui->IDLineEdit->text());
    newRow.push_back(ui->comboBox->currentText());
    newRow.push_back(QVariant(ui->checkBox->checkState()).toString());
    newRow.push_back(ui->nameLineEdit->text());
    newRow.push_back(ui->sexLineEdit->text());
    newRow.push_back(ui->spinBox->text());
    // other fields
    newRow.push_back("");
    newRow.push_back("");
    newRow.push_back("");
    newRow.push_back("");
    newRow.push_back("");
    newRow.push_back("");
    
    QMessageBox::warning(this, "Title", "Looooonger Text");
    
    accept();
}

const QList<QString>& AddRowDialog::getNewRow()
{
    return newRow;
}


AddRowDialog::~AddRowDialog()
{
    delete ui;
}