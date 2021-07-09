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

int main(int argc, char *argv[])
{

    std::string f = "02020";


    Contact *con1 = new Contact(1, "dds", "hgf", date("19.12.32"), date("19.02.2020"));
    Contact *con2 = new Contact(2, "bgf", "bft", date("03.6.2020"), date("02.03.2020"));
    Contact *con3 = new Contact(3, "cfdg", "xsa", date("04.07.2020"), date("13.05.2022"));
    Contact *con4 = new Contact(4, "adgb", "nyf", date("12.08.2020"), date("09.08.2003"));
    Contact *con5 = new Contact(5, "gbc", "zcw", date("30.05.2000"), date("31.03.2015"));

    Book *book_1 = new Book();

    book_1->addContact(con1);
    book_1->addContact(con2);
    book_1->addContact(con3);
    book_1->addContact(con4);
    book_1->addContact(con5);

    book_1->sortByEmail("DESC");

    const time_t timer = time(NULL);

    //cout << timer << endl;



    std::cout << __cplusplus << std::endl;
    return 1;
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    */
}
