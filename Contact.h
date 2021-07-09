#ifndef CONTACT_H
#define CONTACT_H
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "Exceptions.h"

using namespace std;

struct date{

    std::vector<std::pair<int, std::string>> date_int_string;


    date(){}
    date(const std::string &string_date){  // формирование даты
        int start = 0;
        int lenght = 0;
        try {
            for (std::string::size_type i = 0; i < string_date.size()+1; i++) { // разбиение строки даты на составляющие

                if(std::isdigit(string_date[i])) {
                    lenght++;
                }
                else
                if (string_date[i] == '.' || i == string_date.size() ){
                    if(i + 1 == string_date.size()) lenght++;
                    std::string s = string_date.substr(start, lenght);
                    if(s.size() == 1) s = '0' + s;
                    int number = std::stoi(s);
                    date_int_string.push_back(make_pair(number, s));
                    start += lenght + 1;
                    lenght = 0;
                }
                else{
                    Date_Exception_AlphaInside da("constructor date(" + string_date +")");
                    throw da;
                }
            }
            if(date_int_string.size() != 3){
                Date_Exception_WrongCountOfParameters da("constructor date(" + string_date +")");
                throw da;
            }
            Date_Exception_OutOfRangeOfParam da("constructor date(" + string_date +")");

            if (!(0 < date_int_string[0].first && date_int_string[0].first < 32)) throw da;
            if (!(0 < date_int_string[1].first && date_int_string[1].first < 13)) throw da;
            if (!(0 < date_int_string[2].first && date_int_string[2].first < 10000)) throw da;
        }  catch (Exceptions &e) {
            e.what();
        }
    }

    std::string getDate(){
        std::string s;
        s += date_int_string[0].second + '.';
        s += date_int_string[1].second + '.';
        s += date_int_string[2].second;
        return s;
    }
};

class Contact{

    private:

        int id;
        std::string name;
        std::string email;
        date birthday;
        date add_date;

    public:

        Contact();
        Contact(int id_, std::string name_, std::string email_, date birthday_, date add_date_):
                    id(id_), name(name_), email(email_), birthday(birthday_), add_date(add_date_){}

        int getId(){ return id; }
        std::string getName(){ return name; }
        std::string getEmail(){ return email; }
        std::string getBirthday(){ return birthday.getDate(); }
        //std::string getAdd_date(){ return add_date.getDate(); }

};

#endif // CONTACT_H
