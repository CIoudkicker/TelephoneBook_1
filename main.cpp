#include "mainwindow.h"

#include <QApplication>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "Contact.h"
#include "Book.h"
#include <time.h>

using namespace std;

void fill (Book &book_1){
    Contact con1(1, "dds", "hgf", date("19.12.2004"), date("19.02.2020"));
    Contact con2(2, "bgf", "bft", date("03.6.2015"), date("02.03.2020"));
    Contact con3(3, "cfdg", "xsa", date("04.07.2020"), date("13.05.2022"));
    Contact con4(4, "adgb", "nyf", date("12.08.2021"), date("09.08.2003"));
    Contact con5(5, "gbc", "zcw", date("30.05.2000"), date("31.03.2015"));

    book_1.addContact(con1);
    book_1.addContact(con2);
    book_1.addContact(con3);
    book_1.addContact(con4);
    book_1.addContact(con5);
}

int main(int argc, char *argv[])
{

    std::string f = "02020";



    Book book_1;

    fill(book_1);

    book_1.sortByBirthday("ASC");

    const time_t timer = time(NULL);

    //cout << timer << endl;



    std::cout << __cplusplus << std::endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
