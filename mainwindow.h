#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "BookEntry.h"
#include <QStandardItemModel>
#include <QStringList>
#include <QFile>
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QThread>
#include <stdio.h>
#include <iostream>

#include "Exceptions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:

        MainWindow(QString filename = NULL, QWidget *parent = nullptr);
        ~MainWindow();

        void fillTableView();
        bool saveJsonTable();
        bool loadJsontable();
        void addRowToTable(const QJsonArray &jsonRow);

        QString filename;

        BookEntry *bookEntry;
        QStandardItemModel itemModel;


    private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
