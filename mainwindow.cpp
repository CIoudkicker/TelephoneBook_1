#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bookEntry = new BookEntry(this);
    ui->centralwidget->layout()->addWidget(bookEntry);
}

MainWindow::~MainWindow()
{
    delete ui;
}

