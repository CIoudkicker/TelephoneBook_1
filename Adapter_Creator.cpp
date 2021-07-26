#include "Adapter_Creator.h"

Adapter_Creator::Adapter_Creator(MainWindow *mainwindow_) : mainwindow(mainwindow_){};

void Adapter_Creator::addRowToTable(const QJsonArray &jsonRow) {

    const int columnCount = jsonRow.size();
    std::vector<std::string> vectorParameters;

    for(int j = 0; j < columnCount; j++){
        QString s = jsonRow[j].toString();
        vectorParameters.push_back(s.toStdString());
    }
    try {
        Contact contact = Contact(vectorParameters);
        mainwindow->book.addContact(contact);
        mainwindow->MainWindow::addRowToTable(jsonRow);
    }  catch (Exceptions *e) {
        e->what();
    }

}

void Adapter_Creator::updateTable(){

    mainwindow->itemModel.removeRows(0, mainwindow->itemModel.rowCount());

    std::vector<Contact> bookContacts = mainwindow->book.getBookOfContacts();

    const int rowCount = bookContacts.size();

    for(int i = 0; i < rowCount; i++){
        QJsonArray row;

        row.append(QJsonValue(QString::number(bookContacts[i].getId())));
        row.append(QJsonValue(QString::fromStdString(bookContacts[i].getName())));
        row.append(QJsonValue(QString::fromStdString(bookContacts[i].getEmail())));
        row.append(QJsonValue(QString::fromStdString(bookContacts[i].getBirthday("no_reverse"))));
        row.append(QJsonValue(QString::fromStdString(bookContacts[i].getAddDate("no_reverse"))));

        mainwindow->MainWindow::addRowToTable(row);
    }
}

