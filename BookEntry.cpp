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

QJsonArray BookEntry::toJsonArray(){

    QJsonArray JsonContact;

    JsonContact.append(ui->lineEdit_ID->text());
    JsonContact.append(ui->lineEdit_Name->text());
    JsonContact.append(ui->lineEdit_Email->text());
    JsonContact.append(ui->lineEdit_Bithday->text());
    JsonContact.append(ui->lineEdit_AddDate->text());

    return JsonContact;
}


void BookEntry::pressed_AddButton(){
    emit incoming_NewContact(toJsonArray());
    emit saveEvent();
}

