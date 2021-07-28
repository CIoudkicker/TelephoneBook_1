

#include "mainwindow.h"

#include <QApplication>
#include <stdio.h>
#include <iostream>


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

bool saveJsonTable(QString nameOfFile, std::string f[10][5]){

    QFile file(nameOfFile);

    if(!(file.open(QFile::WriteOnly))){
        qWarning("saveJsonTable: Couldn't open save file.");
        return false;
    }

    QJsonObject jsonUserDataObj;

    jsonUserDataObj["rowCount"] = 10;
    jsonUserDataObj["columnCount"] = 5;
    jsonUserDataObj["sortType"] = 0;
    jsonUserDataObj["ASC_or_DESC"] = 0;

    QJsonArray jsonArr;


    for(int i = 0; i < 10; i++){
        QJsonArray row;

        for(int j = 0; j < 5; j++){
            QString s = QString::fromStdString(f[i][j]);
            row.append(QJsonValue(s));
        }

        jsonArr.append(row);
    }

    jsonUserDataObj["User data"] = jsonArr;
    QJsonDocument saveDoc(jsonUserDataObj);
    file.write(saveDoc.toJson());

    return true;
}


int main(int argc, char *argv[])
{

   std::string Back_Up[10][5] = {
       {"1","Bikbavleev Alex","sanya@mail.ru","30.05.2000","20.07.2021"},
       {"2","Zuckerberg Mark","reptilian@gmail.com","14.05.1984","18.04.2020"},
       {"3","Musk Ilon","dogiecoin@gmail.com","28.06.1971","14.05.2019"},
       {"4","Bezos Jeff","baldbillionare@gmail.com","12.01.1964","19.09.2021"},
       {"5","Gates Bill","chipeveryone@gmail.com","28.10.1955","30.11.2021"},
       {"6","Darkholme Van","DeepDarkFantasies@gachimail.com","24.10.1972","01.02.2020"},
       {"7","Clarke Isaac","deadspace@gmail.com","05.06.2465","01.02.2497"},
       {"8","Tarkovsky Andrei","mirror@mail.ru","04.04.1932","23.09.1967"},
       {"9","Tolstoy Lev","WarAndPeace@mail.ru","24.10.1828","20.11.1900"},
       {"10","Ray Amuro","gundam@gmail.com","03.07.1979","25.03.2019"}
                          };



    MyApplication myApp(argc, argv);

    MainWindow w;

    saveJsonTable(QCoreApplication::applicationDirPath() + "/TelBook_BackUp.json", Back_Up);

    myApp.setMainWidget(&w);

    QObject::connect(&myApp, &QApplication::aboutToQuit, &w, &MainWindow::saveJsonTable);

    myApp.startProg();

    return 1;

}


