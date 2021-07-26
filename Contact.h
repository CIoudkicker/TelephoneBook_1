#ifndef CONTACT_H
#define CONTACT_H
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>
#include <iomanip>
#include <stdio.h>
#include "Exceptions.h"

using namespace std;



struct date{ // Возможно создал велосипед, но я не нашел встроенных структур для даты в C++

    std::vector<std::pair<int, std::string>> date_int_string;


    date(){}
    date(const std::string &string_date);

    std::string getDate(std::string reverse);

    std::string getDate();

    void setDate(const std::string &string_date);
};



class Contact{

    private:

        int id;
        std::string name;
        std::string email;
        date birthday;
        date add_date;

        int countOfParameters = 5;

    public:

        Contact();
        Contact(int id_, std::string name_, std::string email_, date birthday_, date add_date_);

        Contact(const std::vector<std::string> &vectorParam);

        int getId(){ return id; }
        std::string getName(){ return name; }
        std::string getEmail(){ return email; }
        std::string getBirthday(std::string reverse){ return birthday.getDate(reverse); }
        std::string getAddDate(std::string reverse){ return add_date.getDate(reverse); }
        int getCountOfParameters(){ return countOfParameters; }

        void setId(const std::string &id_);
        void setName(const std::string &name_);
        void setEmail(const std::string &email_);
        void setBirthday(const std::string &birthday_);
        void setAddDate(const std::string &birthday_);


        std::string operator[](const int index);

};

#endif // CONTACT_H
