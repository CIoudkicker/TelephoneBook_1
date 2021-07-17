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

using namespace std;

void fill (Book &book_1){
    Contact con1(1, "dds", "hgf", date("19.12.2004"), date("19.02.2020"));
    Contact con2(2, "bgf", "bft", date("03.6.2015"), date("02.03.2020"));
    Contact con3(3, "cfdg", "xsa", date("04.07.2020"), date("13.05.2022"));
    Contact con4(4, "adgb", "nyf", date("12.08.2021"), date("09.08.2003"));
    Contact con5(5, "gbc", "zcw", date("30.05.2000"), date("31.03.2015"));

    book_1.addContact(con1);
    book_1.addContact(con2);
    book_1.addContact(con3);
    book_1.addContact(con4);
    book_1.addContact(con5);
}


void saveToJsonFile(const QString &filename, const QJsonObject &jsonobject){
  //QFileInfo fileInfo(filename);
  //QDir::setCurrent(fileInfo.path());
    QFile file(filename);
    if(file.open(QFile::WriteOnly)){
        QJsonDocument document(jsonobject);
        file.write(document.toJson());
        file.close();
    }
}

QJsonObject loadFromJsonFile(const QString &filename){

    QJsonObject json;
    QFile file(filename);

    if(file.open(QFile::WriteOnly)){
        QJsonDocument document = QJsonDocument::fromJson(file.readAll());
        json = document.object();
        file.close();
    }

    return json;
}


void saveAdressBookEntryPropertiesToFile(const QJsonObject &properties)
{
    qDebug() << "Wer";
    saveToJsonFile("E:\\Qt Projects\\TelephoneBook_1\\AdressBookEntry.json", properties);
}

void somefunc2(const QJsonObject &properties){
    int z = 1;
    cout << "OPPA";
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    QJsonObject obj;

    Book book_1;

    fill(book_1);

    book_1.sortByBirthday("ASC");
    //saveAdressBookEntryPropertiesToFile(obj);

    BookEntry bookEntry;
    //somefunc(obj);

    QJsonObject ob;


    MainWindow w("E:\\Qt Projects\\TelephoneBook_1\\AdressBookEntry.json");
    QObject::connect(w.bookEntry, &BookEntry::incoming_NewContact, &w, &MainWindow::addRowToTable);
    QObject::connect(w.bookEntry, &BookEntry::saveEvent, &w, &MainWindow::saveJsonTable);
    QObject::connect(&a, &QApplication::aboutToQuit, &w, &MainWindow::saveJsonTable);

    w.show();

    return a.exec();

}
