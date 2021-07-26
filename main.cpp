

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



class MyApplication : public QApplication{

    public:

        MainWindow *w;

        MyApplication(int& argc_, char** argv_) :
            QApplication(argc_, argv_){};

        void setMainWidget(MainWindow *w_){
            w = w_;
        }

        void startProg(){
                w->show();
                this->exec();
        }

        virtual bool notify(QObject* receiver, QEvent* event) override{

            try {
                QApplication::notify(receiver, event);
            }  catch (Exceptions *e) {
                qDebug() << "e->endOfChain();!";
                e->endOfChain();
            }

            return true;
        }
};

int main(int argc, char *argv[])
{

    MyApplication myApp(argc, argv);

    MainWindow w;

    myApp.setMainWidget(&w);

    QObject::connect(&myApp, &QApplication::aboutToQuit, &w, &MainWindow::saveJsonTable);

    myApp.startProg();

    return 1;

}


