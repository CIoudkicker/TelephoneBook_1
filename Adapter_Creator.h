#ifndef ADAPTER_H
#define ADAPTER_H
#include <mainwindow.h>
#include "Contact.h"
#include "Book.h"


class Adapter_Creator : public Contact, public MainWindow
{
    public:

        Adapter_Creator(MainWindow *mainwindow_) : mainwindow(mainwindow_){};

        void addRowToTable(const QJsonArray &jsonRow) override;

    private:

        MainWindow *mainwindow;


};

#endif // ADAPTER_H
