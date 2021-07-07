#include "mainwindow.h"

#include <QApplication>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "Contact.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*
    Contact *con1 = new Contact(1, "dds", "hgf", "gfdg", "yui");
    Contact *con2 = new Contact(2, "bgf", "bft", "fzwe", "ojn");
    Contact *con3 = new Contact(3, "cfdg", "xsa", "chy", "qwex");
    Contact *con4 = new Contact(4, "adgb", "nyf", "qwr", "gyh");
    Contact *con5 = new Contact(5, "gbc", "zcw", "qer", "yui");
    */
    Contact *con1 = new Contact(1, "dds", "hgf", "gfdg", "yui");
    Contact *con2 = new Contact(2, "bgf", "bft", "fzwe", "ojn");
    Contact *con3 = new Contact(3, "cfdg", "xsa", "chy", "qwex");
    Contact *con4 = new Contact(4, "adgb", "nyf", "qwr", "gyh");
    Contact *con5 = new Contact(5, "gbc", "zcw", "qer", "yui");

    std::vector<Contact *> vect;
    vect.push_back(con1);
    vect.push_back(con2);
    vect.push_back(con3);
    vect.push_back(con4);
    vect.push_back(con5);

    std::vector<Contact *> vect2;
    /*
    sort(vect.begin(), vect.end(), [] ( Contact* a,  Contact* b){
        return a->getId() > b->getId();
    });
    */

    sort(vect.begin(), vect.end(), [] ( Contact* a,  Contact* b){
        return a->getName() < b->getName();
    });

    std::cout << __cplusplus << std::endl;
    return 1;
    /*
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    */
}
