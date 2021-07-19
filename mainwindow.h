
#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QMainWindow>

#include "BookEntry.h"
#include <QStandardItemModel>
#include <QStringList>
#include <QFile>
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QMap>
#include <QList>
#include <QByteArray>
#include <QThread>
#include <stdio.h>
#include <iostream>

#include "Exceptions.h"
#include "Book.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:

        enum SortType{
            SortById,
            SortByName,
            SortByEmail,
            SortByBirthday,
            SortByAddDate
        };

        enum ASC_or_DESC{
            ASC,
            DESC
        };

        MainWindow(QString filename = NULL, QWidget *parent = nullptr);
        ~MainWindow();

        void fillTableView();
        bool saveJsonTable();
        bool loadJsontable();

        virtual void addRowToTable(const QJsonArray &jsonRow);
        virtual void updateTable();
        void deleteRow();

        void initiateSort();

        QString filename;

        Book book;
        BookEntry *bookEntry;
        QStandardItemModel itemModel;


    private:

        int currentSort;
        int asc_or_desc;
        Ui::MainWindow *ui;
};
#endif // _MAINWINDOW_H_
