#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Adapter_Creator.h"

class Adapter_Creator;

MainWindow::MainWindow(QString filename, QWidget *parent)
    : QMainWindow(parent),
      filename(filename),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bookEntry = new BookEntry(this);

    ui->centralwidget->layout()->addWidget(bookEntry);

    QStringList headers = QStringList() << "ID" << "Name" << "Email" << "Birthday" << "Add date";

    itemModel.setHorizontalHeaderLabels(headers);
    itemModel.setColumnCount(headers.size());

    loadJsontable();

    ui->tableView->setModel(&itemModel);


}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::saveJsonTable(){

    QFile file(filename);

    if(!(file.open(QFile::WriteOnly))){
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject jsonUserDataObj;

    jsonUserDataObj["rowCount"] = itemModel.rowCount();
    jsonUserDataObj["columnCount"] = itemModel.columnCount();

    QJsonArray jsonArr;

    for(int i = 0; i < itemModel.rowCount(); i++){
        QJsonArray row;

        for(int j = 0; j < itemModel.columnCount(); j++){
            QString s = itemModel.item(i, j)->text();
            row.append(QJsonValue(s));
        }

        jsonArr.append(row);
    }

    jsonUserDataObj["User data"] = jsonArr;
    QJsonDocument saveDoc(jsonUserDataObj);
    file.write(saveDoc.toJson());

    return true;
}

bool MainWindow::loadJsontable(){
    QFile file(filename);

    if(!(file.open(QFile::ReadOnly))){
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc = QJsonDocument::fromJson(saveData);
    QJsonObject json = loadDoc.object();

    // Очистка модели
    while (itemModel.rowCount() > 0) {
        itemModel.invisibleRootItem()->removeRow(0);
    }

    const int rowCount = json["rowCount"].toInt();


    QJsonArray data = json["User data"].toArray();

    Adapter_Creator adapt_create(this);

    for(int i = 0; i < rowCount; i++){
        QJsonArray row = data[i].toArray();
        adapt_create.addRowToTable(row);
    }

    return true;
}


void MainWindow::addRowToTable(const QJsonArray &jsonRow){

    const int columnCount = jsonRow.size();
    int i = itemModel.rowCount();
    for(int j = 0; j < columnCount; j++){
        QString s = jsonRow[j].toString();
        itemModel.setItem(i, j, new QStandardItem(s));
    }
}
