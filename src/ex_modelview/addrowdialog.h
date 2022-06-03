#ifndef ADDROWDIALOG_H
#define ADDROWDIALOG_H

#include <QDialog>

namespace Ui {
class AddRowDialog;
}

class AddRowDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddRowDialog(QWidget *parent = nullptr);
    ~AddRowDialog();
    const QList<QString>& getNewRow();
    
private slots:
    void saveAddedRow();
    
    
private:
    
    QList<QString> newRow;
    Ui::AddRowDialog *ui;
};

#endif // ADDROWDIALOG_H
