

#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <QDebug>
#include "Contact.h"
#include "BookEntry.h"
#include "Book.h"
#include <time.h>

#include "Adapter_Creator.h"

using namespace std;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;

    Adapter_Creator adapt_create(&w);

    QObject::connect(w.bookEntry, &BookEntry::incoming_NewContact, &adapt_create, &Adapter_Creator::addRowToTable);
    QObject::connect(w.bookEntry, &BookEntry::saveEvent, &w, &MainWindow::saveJsonTable);
    QObject::connect(&a, &QApplication::aboutToQuit, &w, &MainWindow::saveJsonTable);

    w.show();

    return a.exec();

}


