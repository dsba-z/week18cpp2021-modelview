# DSBA Introduction to Programming // Workshops 34+ for Model-View
Spring semester 2021/22

Qt Framework. Models, views.

Tasks:

https://github.com/dsba-z/week18cpp2021-modelview/blob/master/Tasks_1.md


# Tasks

## Task 1. Setup.

Make a project with a `QTableView` and a model derived from `QAbstractTableModel`. Connect them. Make sure the code runs.

Try manually setting some return values in `rowCount`, `columnCount` and `data` in the model. See if the view shows data you set.

## Task 2. Data table

Add a private variable `QList<QList<QString>> dataTable` to your model.

In the constructor of the model, add some data to the table. Set `rowCount()`, `columnCount()` and `data()` to show data from the table.

## Task 3. Loading data from a file.

In the constructor of the model, open the data file and fill `dataTable` with data from the file.

Here is an example of how this code may look like. It uses Qt File interface.

```cpp
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
```

Test that this works.


## Task 4. Editing data table

Edit data in `dataTable`, using the approach above with `setData`. Make sure you write the function `flags`.

To convert variable `value` from QVariant to QString, use method `.toString()`.

Check if you can edit the data through `QTableView`.


## Task 5. Adding new rows.

Make a new model class and check the option "Rows and columns can be added". Alternatively, use the code above in the section "Rows and columns can be added".

Add a button that adds a new row to your data. Fill the new row with whatever you want, for example, constant strings.


## Task 6. Custom header data.

Add functions from the instruction to set custom header data. Make a new `QList<QString>` that stores headers. Fill it together with data (as the first line of the csv file). Return it in `headerData()`. You should return it for `Qt::DisplayRole` and when orientation is `Qt::Horizontal`.

## Task 7. Displaying details.

Hide some columns from the view.

You can use `ui->tableView->setColumnHidden(0, true);` to hide the first column.

Leave the column with name and 2-3 other columns you would like to leave.

