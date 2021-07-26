#ifndef BOOKENTRY_H
#define BOOKENTRY_H

#include <QWidget>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class BookEntry; }
QT_END_NAMESPACE

class BookEntry : public QWidget{

    Q_OBJECT

    public:
        BookEntry( QWidget *parent = nullptr);
        ~BookEntry();

    signals:
        void incoming_NewContact(const QJsonArray &changes);
        bool saveEvent();

    public slots:
        void pressed_AddButton();
        QJsonArray toJsonArray();

    private:

        Ui::BookEntry *ui;
};

#endif // BOOKENTRY_H
