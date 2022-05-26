#include "examplemodel.h"
#include <QFile>

ExampleModel::ExampleModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    
}

void ExampleModel::fillDataTable()
{
    for (int i = 0; i < 5; ++i)
    {
        QList<QString> newRow;
        for (int j = 0; j < 8; ++j)
        {
            newRow.append(QStringLiteral("row %1, col %2").arg(i).arg(j));
        }
        dataTable.append(newRow);
    }
}

void ExampleModel::fillDataTableFromFile(QString path)
{
//    QString path = "/home/georgii/WORK/DSBA2021cpp/workshops/week18/workshops-mvc/data/titanic.csv";
    QFile inputFile(path);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);

    QString firstline = inputStream.readLine();

    while(!inputStream.atEnd())
    {
        QString line = inputStream.readLine();
        
        QList<QString> dataRow;
        for (QString& item : line.split(",")) {
            dataRow.append(item);
        }
        dataTable.append(dataRow);
    }
    inputFile.close();
}


int ExampleModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    
    return dataTable.size();
}

int ExampleModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    
    if (dataTable.empty())
        return 0;
    
    return dataTable[0].size();
}

QVariant ExampleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    int row = index.row();
    int column = index.column();
    if (role == Qt::DisplayRole)
    {
        return dataTable[row][column];
    }
    
    return QVariant();
}
