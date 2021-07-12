#include "BookEntry.h"
#include "ui_BookEntry.h"

BookEntry::BookEntry(QWidget *parent) :
    QWidget(parent), ui( new Ui::BookEntry )
{
    ui->setupUi(this);

    connect(ui->pushButton_Save, &QPushButton::clicked, this, &BookEntry::pressed_AddButton);


}


BookEntry::~BookEntry(){
    delete ui;
}


void BookEntry::pressed_AddButton(){
    ui->pushButton_Save->setText("dsad");
}

