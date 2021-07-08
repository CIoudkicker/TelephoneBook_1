#ifndef CONTACT_H
#define CONTACT_H
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class Contact{

    private:

        int id;
        std::string name;
        std::string email;
        std::string birthday;
        std::string add_date;

    public:

        Contact();
        Contact(int id_, std::string name_, std::string email_, std::string birthday_, std::string add_date_):
                    id(id_), name(name_), email(email_), birthday(birthday_), add_date(add_date_){}

        int getId(){ return id; }
        std::string getName(){ return name; }
        std::string getEmail(){ return email; }
        std::string getBirthday(){ return birthday; }
        std::string getAdd_date(){ return add_date; }

};

#endif // CONTACT_H
