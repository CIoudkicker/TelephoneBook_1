#include "Adapter_Creator.h"



void Adapter_Creator::addRowToTable(const QJsonArray &jsonRow) {

    const int columnCount = jsonRow.size();
    int i = mainwindow->itemModel.rowCount();
    std::vector<std::string> vectorParameters;

    for(int j = 0; j < columnCount; j++){
        QString s = jsonRow[j].toString();
        mainwindow->itemModel.setItem(i, j, new QStandardItem(s));
        vectorParameters.push_back(s.toStdString());
    }
    Contact contact = Contact(vectorParameters);
    mainwindow->book.addContact(contact);
}
