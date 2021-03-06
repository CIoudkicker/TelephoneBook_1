
#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "Adapter_Creator.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    bookEntry = new BookEntry(this);

    ui->centralwidget->layout()->addWidget(bookEntry);

    QStringList headers = QStringList() << "ID" << "Name" << "Email" << "Birthday" << "Add date";

    itemModel.setHorizontalHeaderLabels(headers);
    itemModel.setColumnCount(headers.size());

    ui->tableView->setModel(&itemModel);

}


void MainWindow::show(){
    determineConnects();
    loadJsontable();
    this->QMainWindow::show();
}

void MainWindow::determineConnects(){

    connect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);

    connect(ui->comboBox_SortBook, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int sortType){
                currentSort = sortType;
                initiateSort();
                updateTable();
            }
    );

    connect(ui->comboBox_ASCorDESC, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int asc_or_desc_){
                asc_or_desc = asc_or_desc_;
                initiateSort();
                updateTable();
            }
    );

    QObject::connect(bookEntry, &BookEntry::incoming_NewContact, this, [this](const QJsonArray &jsonRow){
                                                                            Adapter_Creator adapt_create(this);
                                                                            adapt_create.addRowToTable(jsonRow);
                                                                        });
    QObject::connect(bookEntry, &BookEntry::saveEvent, this, &MainWindow::saveJsonTable);

    connect(ui->pushButton_Delete, &QPushButton::clicked, this, &MainWindow::deleteRow);
    connect(ui->pushButton_RestoreTable, &QPushButton::clicked, this, &MainWindow::messageAboutResetTable);

    connect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);
}

void MainWindow::changeContact(QStandardItem *item){

    int m = item->row();
    int n = item->column();
    std::string s = itemModel.item(m,n)->text().toStdString();

    Contact &c = book[m];

    try {
        switch (n) {
            case 0: c.setId(s); break;
            case 1: c.setName(s); break;
            case 2: c.setEmail(s); break;
            case 3: c.setBirthday(s); break;
            case 4: c.setAddDate(s); break;
        }
    }  catch (Exceptions *e) {
        updateTable();
        e->endOfChain();
    }
    return;
}

void MainWindow::messageAboutResetTable(){

    QMessageBox::StandardButton resetOrNot;
    resetOrNot = QMessageBox::question(this, "Reset table", "Are you sure you want to reset table?",
                                       QMessageBox::Yes | QMessageBox::No);
    if(resetOrNot == QMessageBox::Yes){
        backUpTable();
    }
    else{
        return;
    }

}

void MainWindow::resizeEvent(QResizeEvent *event){


    // ???????????? ?????? ?????????? ?????? ???????? ?????????? ???????????? ?????????????? ???????????? ?????????????? ?????????????? ?? ?????????????????????? ??????????????????
    // ?????? ?????????????????? ?????????????? ????????
    ui->tableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);


    ui->tableView->horizontalHeader()->adjustSize();


    int widgetWidth = ui->tableView->viewport()->size().width();
    int tableWidth = 0;

    for(int i = 0; i< itemModel.columnCount(); ++i)
        tableWidth += ui->tableView->horizontalHeader()->sectionSize(i);

    if(tableWidth > widgetWidth){
        return;
    }

    double scale = (double)widgetWidth/tableWidth;
    for(int i = 0; i< itemModel.columnCount(); ++i){

        int selfMadeSize = ui->tableView->horizontalHeader()->sectionSize(i) * scale;
        int hintSize = ui->tableView->horizontalHeader()->sectionSize(i);
        if(selfMadeSize < hintSize) ui->tableView->setColumnWidth(i, hintSize);
        else ui->tableView->setColumnWidth(i, selfMadeSize);

    }
    ui->tableView->horizontalHeader()->setCascadingSectionResizes(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::saveJsonTable(){

    QFile file(filename);

    if(!(file.open(QFile::WriteOnly))){
        qWarning("saveJsonTable: Couldn't open save file.");
        return false;
    }

    QJsonObject jsonUserDataObj;

    jsonUserDataObj["rowCount"] = itemModel.rowCount();
    jsonUserDataObj["columnCount"] = itemModel.columnCount();
    jsonUserDataObj["sortType"] = currentSort;
    jsonUserDataObj["ASC_or_DESC"] = asc_or_desc;

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

    disconnect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);

    if(file.open(QFile::ReadOnly)){
        qWarning("loadJsontable: Success open!");
    }else{
        qWarning("loadJsontable: Couldn't open save file.");
        return false;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc = QJsonDocument::fromJson(saveData);
    QJsonObject json = loadDoc.object();


    int rowCount = json["rowCount"].toInt();
    currentSort =  json["sortType"].toInt();
    asc_or_desc =  json["ASC_or_DESC"].toInt();

    ui->comboBox_SortBook->setCurrentIndex(currentSort);
    ui->comboBox_ASCorDESC->setCurrentIndex(asc_or_desc);

    QJsonArray data = json["User data"].toArray();

    Adapter_Creator adapt_create(this);

    for(int i = 0; i < rowCount; i++){
        QJsonArray row = data[i].toArray();
        adapt_create.addRowToTable(row);
    }

    initiateSort();
    updateTable();

    connect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);

    return true;
}

bool MainWindow::backUpTable(){

    QFile file(backUpFileName);

    disconnect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);

    if(file.open(QFile::ReadOnly)){
        qWarning("loadJsontable: Success open!");
    }else{
        qWarning("loadJsontable: Couldn't open save file.");
        return false;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc = QJsonDocument::fromJson(saveData);
    QJsonObject json = loadDoc.object();

    book.clearBook();

    int rowCount = json["rowCount"].toInt();
    currentSort =  json["sortType"].toInt();
    asc_or_desc =  json["ASC_or_DESC"].toInt();

    ui->comboBox_SortBook->setCurrentIndex(currentSort);
    ui->comboBox_ASCorDESC->setCurrentIndex(asc_or_desc);

    QJsonArray data = json["User data"].toArray();

    Adapter_Creator adapt_create(this);

    for(int i = 0; i < rowCount; i++){
        QJsonArray row = data[i].toArray();
        adapt_create.addRowToTable(row);
    }

    initiateSort();
    updateTable();

    connect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);

    return true;
}


void MainWindow::addRowToTable(const QJsonArray &jsonRow){
    disconnect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);

    const int columnCount = jsonRow.size();
    const int i = itemModel.rowCount();

    for(int j = 0; j < columnCount; j++){
        QString s = jsonRow[j].toString();
        itemModel.setItem(i, j, new QStandardItem(s));
    }

    connect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);
}


void MainWindow::initiateSort(){
    disconnect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);


    std::string ASC_or_DESC;

    switch (asc_or_desc) {
        case ASC:  ASC_or_DESC = "ASC"; break;
        case DESC: ASC_or_DESC = "DESC"; break;
    }

    switch (currentSort) {
        case SortById:       book.sortById(ASC_or_DESC); break;
        case SortByName:     book.sortByName(ASC_or_DESC); break;
        case SortByEmail:    book.sortByEmail(ASC_or_DESC); break;
        case SortByBirthday: book.sortByBirthday(ASC_or_DESC); break;
        case SortByAddDate:  book.sortByAddDate(ASC_or_DESC); break;
    }
    connect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);

}

void MainWindow::updateTable(){
    disconnect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);
    Adapter_Creator adapt_create(this);
    adapt_create.updateTable();
    connect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);
}

void MainWindow::deleteRow(){

    disconnect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);

    QItemSelectionModel *selections = ui->tableView->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    if(selected.isEmpty()) return;

    QModelIndex index = selected.first();

    for(int i = 0; i < selected.size(); i++){
        itemModel.removeRow(index.row());
        book.deleteContact(index.row());
    }
    connect(&itemModel, &QStandardItemModel::itemChanged, this, &MainWindow::changeContact);

}




