
#ifndef _ADAPTER_CREATOR_H_
#define _ADAPTER_CREATOR_H_

#include "mainwindow.h"

#include <QString>
#include <QJsonArray>
#include <stdio.h>
#include <iostream>


class Adapter_Creator : public Book, public MainWindow
{
    public:

        Adapter_Creator(MainWindow *mainwindow_);

        void addRowToTable(const QJsonArray &jsonRow) override;
        void updateTable() override;

    private:

        MainWindow *mainwindow;

};

#endif // _ADAPTER_CREATOR_H_
