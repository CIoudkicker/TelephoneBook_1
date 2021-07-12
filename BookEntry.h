#ifndef BOOKENTRY_H
#define BOOKENTRY_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class BookEntry; }
QT_END_NAMESPACE

class BookEntry : public QWidget{

    Q_OBJECT

    public:

        BookEntry( QWidget *parent = nullptr);
        ~BookEntry();



    public slots:
        void pressed_AddButton();

    private:

        Ui::BookEntry *ui;
};

#endif // BOOKENTRY_H
