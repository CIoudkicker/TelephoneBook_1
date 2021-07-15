#include "BookEntry.h"
#include "ui_BookEntry.h"

BookEntry::BookEntry(QWidget *parent) :
    QWidget(parent), ui(new Ui::BookEntry)
{

    ui->setupUi(this);

    connect(ui->pushButton_Save, &QPushButton::clicked, this, &BookEntry::pressed_AddButton);

}


BookEntry::~BookEntry(){
    delete ui;
}


void BookEntry::pressed_AddButton(){
    ui->pushButton_Save->setText("dsad");
    emit incoming_Changes(toJSON());
}


QJsonObject BookEntry::toJSON(){

    QJsonObject JsonContact;

    JsonContact["ID"]       = ui->lineEdit_ID->text();
    JsonContact["Name"]     = ui->lineEdit_Name->text();
    JsonContact["Birthday"] = ui->lineEdit_Bithday->text();
    JsonContact["Add date"] = ui->lineEdit_AddDate->text();

    return JsonContact;
}
