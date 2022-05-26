#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "examplemodel.h"

#include <QMainWindow>

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
    void loadFileSlot();
    
private:
    Ui::MainWindow *ui;
    ExampleModel *examplemodel;
};
#endif // MAINWINDOW_H
