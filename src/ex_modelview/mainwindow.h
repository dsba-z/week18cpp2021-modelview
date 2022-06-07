#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "examplemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void loadFile();
    void saveFile();
    void addRowSlot();
    
    void on_spinBox_valueChanged(int arg1);
    
    void on_tableView_doubleClicked(const QModelIndex &index);
    void updateFilter(const QString & text);

private:
    size_t _shownDetailsColumn;
    ExampleModel *_exampleModel;
    QSortFilterProxyModel *proxyModel;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
