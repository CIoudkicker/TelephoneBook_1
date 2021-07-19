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
    date(const std::string &string_date){  // формирование даты
        int start = 0;
        int lenght = 0;
        int count = 0;
        // функция чисто для того чтобы сформировать строку по определенному шаблону
        std::function<std::string(int, std::string)> templateNum = [&string_date](int len, std::string s_){
            if(len < (int)s_.size()){
                Date_Exception_OutOfRangeOfParam da("constructor date(" + string_date +")");
                throw da;
            }
            int position = len - (int)s_.size();
            std::string s(position, '0');
            s.insert( position, s_);
            return s;
        };

        try {
            for (std::string::size_type i = 0; i < string_date.size()+1; i++) { // разбиение строки даты на составляющие

                if(std::isdigit(string_date[i])) {
                    lenght++;
                }
                else
                // понадобилось сделать так, чтобы строки дня, месяца, года подчинялась определенному шаблону
                // это нужно было в дальнейшем для алгоритма сортировки контактов по дате
                if (string_date[i] == '.' || i == string_date.size() ){
                    if(i + 1 == string_date.size()) lenght++, count++;
                    count++;
                    std::string s = string_date.substr(start, lenght);
                    if(count == 1) s = templateNum(2, s);
                    if(count == 2) s = templateNum(2, s);
                    if(count == 3) s = templateNum(4, s);
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

    std::string getDate(std::string reverse){ // Тут reverse нужен ждя сортировки по датам,
        std::string s = "";
        try {
            if(reverse == "reverse"){
                s += date_int_string[2].second + '.';
                s += date_int_string[1].second + '.';
                s += date_int_string[0].second;
            }
            else
            if(reverse == "no_reverse"){
                s += date_int_string[0].second + '.';
                s += date_int_string[1].second + '.';
                s += date_int_string[2].second;
            }
            else{
                Date_Exception_ReverseOrNot d("getDate(\"" + reverse + "\")");
                throw d;
            }
        }  catch (Exceptions &e) {
            e.what();
        }

        return s;
    }
    std::string getDate(){
        std::string s = "";
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

        int countOfParameters = 5;

    public:

        Contact();
        Contact(int id_, std::string name_, std::string email_, date birthday_, date add_date_):
                    id(id_), name(name_), email(email_), birthday(birthday_), add_date(add_date_){}

        Contact(const std::vector<std::string> &vectorParam){
            if((int)vectorParam.size() == countOfParameters){
                id = std::stoi(vectorParam[0]);
                name = vectorParam[1];
                email = vectorParam[2];
                birthday = date(vectorParam[3]);
                add_date = date(vectorParam[4]);
            }
        }

        int getId(){ return id; }
        std::string getName(){ return name; }
        std::string getEmail(){ return email; }
        std::string getBirthday(std::string reverse){ return birthday.getDate(reverse); }
        std::string getAddDate(std::string reverse){ return add_date.getDate(reverse); }
        int getCountOfParameters(){ return countOfParameters; }

};

#endif // CONTACT_H
