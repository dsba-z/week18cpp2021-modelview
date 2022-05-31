# Titanic example

A Qt Model-View based application that allows browsing and modifying the dataset "Titanic".

https://doc.qt.io/qt-5/modelview.html

In this example and the following workshops we will develop an application that uses Qt Model-View tools to display and modify a table of data.

The two main parts of this application are a model - a class that handles managing data and provides an interface for changing and accessing that data - and some views - classes that connect to a model and act as a layer between the user and the data, handling updates, user interactions and so on.

# Setup

First, create an empty Qt Widgets application and make sure you can run it.

Then, add a new model class to your application.

1. Right-click the name of the project (a little hammer icon in project view),
2. "Add new..."
3. "Qt" (left column)" , "Qt Item Model" (right column)
4. Name your model class. For example, `ExampleModel`. Select `QAbstractTableModel` as a base class.
5. Uncheck all checkboxes
6. Check your new header and source files to see templates for the model.


# Explanation for templates

When you check boxes while creating the model, Qt Creator automatically adds templates to your code. You don't have to add them like this, you can just write the mode manually.

The templates we use are:

## Basic functionality

https://doc.qt.io/qt-5/qabstractitemmodel.html#rowCount

https://doc.qt.io/qt-5/qabstractitemmodel.html#columnCount

https://doc.qt.io/qt-5/qabstractitemmodel.html#data



Header:

```cpp
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    
```

Source:
```cpp
QModelIndex ExampleModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex ExampleModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int ExampleModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;
    
    // FIXME: Implement me!
}

int ExampleModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;
    
    // FIXME: Implement me!
}

QVariant ExampleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    
    // FIXME: Implement me!
    return QVariant();
}
```

These are basic function, they are needed even if you can't edit data, you can't customize headers and do other additional things. These functions control how you access the data, even just for reading.

Luckily, for our examples we don't need `parent` and `index`, at least for now. So you can remove these functions from the template.

`rowCount` and `columnCount` return how many rows or columns you have in your data. The way to finish their implementation is to access your data directly. For example, using previous approaches you might make a `std::vector<std::vector<std::string>>> dataTable` containing all your data. Then, `rowCount` would return `dataTable.size()` and `columnCount` would return `dataTable[0].size()`.

However, it's better not to mix Qt code and STL code too much, so we will use `QList<QList<QString> > exampleData` for the data, and `QList<QString> headerList` for the header. The logic itself stays the same, so it's still going to me `exampleData.size()` and `exampleData[0].size()`.

Finally, `data`, the most important function here. It returns data at a particular index, and because Qt models support other types of data than just tables (for example, trees and graphs), `data` uses a single variable `index` to index the data.

The `index` variable has methods `index.row()` and `index.column()` to get a row and column you need. You can use them to access your table like this: `exampleData.at(row).at(column)`.

`role` in the function `data` is a special parameter that controls which aspect of data you access. There is `Qt::DisplayRole` which is data itself, a string, specifically for display purposes. There are also other roles. `Qt::EditRole` is what appears in the data when you start changing it, `Qt::ToolTipRole` is the text that appears in a tooltip when you hover your cursor over data, `Qt::BackgroundRole` is the color of the background in the cell displaying data, and so on.

Explanation of roles: https://doc.qt.io/qt-5/modelview.html#2-2-extending-the-read-only-example-with-roles

More types of roles: https://doc.qt.io/qt-5/qt.html#ItemDataRole-enum

The return data type of `data` is `QVariant`, a special type that can be used for several different types of Qt objects. Sometimes you can assume all your data is `QString`, but if you want to compute something, you can return data as numbers for columns with numerical data, and it will still work.

## Customize header row

https://doc.qt.io/qt-5/qabstractitemmodel.html#headerData

https://doc.qt.io/qt-5/qabstractitemmodel.html#setHeaderData

Header:

```cpp
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;
    
```

Source:

```cpp
QVariant ExampleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

bool ExampleModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role)) {
        // FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

```

These functions let you get and set header data for your model. This way you can set nice readable headers, while keeping the data as it is, with shorter, less readable one.

Here `section` is a column number or a row number (for horizontal or vertical headers), `orientation` is either `Qt::Horizontal` or `Qt::Vertical` and tells whether the header is horizontal or vertical. `role` is a special parameter that will be covered later, an explanation is available here - https://doc.qt.io/qt-5/modelview.html#2-2-extending-the-read-only-example-with-roles. For now you can use `Qt::DisplayRole` for it.

The return value type of `headerData` is `QVariant`, so just like for `data`, it can be one of several types. Here, headers will almost always be `QString`.

Same can be said about the `value` argument of `setHeaderData`. It can be one of several different types, but for now (for `Qt::DisplayRole`) it will be `QString`.

The `if` statement in `setHeaderData` checks whether new header value is different from the old one, so you don't perform unnecessary actions.

Finally, the line `emit headerDataChanged(orientation, section, section);` emits a **signal**. It's the same signal as the ones used in user interface, a signal connected to a slot. After this signal is emitted, every slot connected to it will run its code. What it usually means is after you update header data, the display widgets need to update what they draw on the screen.

As for the code in `FIXME`, that's where you can write anything. Like with `data()`, instead of a previous approach with  `std::vector<std::string> headerVector`, it's better to use `QList<QString> headerList` containing all header names, return data from that list in `headerData` or modify it in `setHeaderData`.

## Items are editable

Docs example: https://doc.qt.io/qt-5/modelview.html#2-5-the-minimal-editing-example

https://doc.qt.io/qt-5/qabstractitemmodel.html#setData

https://doc.qt.io/qt-5/qabstractitemmodel.html#flags

Header:

```cpp
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    
    Qt::ItemFlags flags(const QModelIndex& index) const override;
``` 

Source:

```cpp
bool ExampleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ExampleModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}
```

Function `flags` only controls flags, showing different states and permissions for data. For example, here it returns a flag `Qt::ItemIsEditable` which will allow editing of all items.

The main function here is `setData`. It works similarly to `setHeaderData` but instead of a header, it changes data itselt. The logic is similar: check if new data is different from the old data, change the underlying data representation, emit signal `dataChanged` so the views know they have to update themselves.



## Rows and columns can be added

https://doc.qt.io/qt-5/qabstractitemmodel.html#beginInsertRows


Header:

```cpp
    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
```


Source:

```cpp
bool addRowsCheck::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();
    return true;
}

bool addRowsCheck::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);
    // FIXME: Implement me!
    endInsertColumns();
    return true;
}
```


The important part here is a pair of functions `beginInsertRows` / `endInsertRows` and the same pair for columns. Whenever you modify the data of your model and change the number of columns or rows, you need to wrap the code in this pair of functions.

The arguments here are:
- `row` - the index of the first **new** row. For example, if you have 3 rows (index 0-1-2) and you add a fourth one (index 3), argument `row` must be 3.
- `row + count - 1` - the index of the **last** new row. In the example above, this is also equal to 3.
- `parent` - only relevant for Item model, you can just use the input variable of the function.

# Connecting a model to a view

Setting up a model is a comples task where you have to figure out the data, the functions, the interface and so on. Compared to that, adding a view is pretty simple, as it's a widget like a button or a spin box.

To make a view and connect it to a model

1. Make a private model variable inside `mainwindow.h`. For example, `ExampleModel *exampleModel;`
2. Add a `QTableView` widget to your interface, call it `tableView`.
3. Write `ui->tableView->setModel(titanicModel);` in the constructor of `MainWindow` in `mainwindow.cpp`.

Now the model should be connected to the view.

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

