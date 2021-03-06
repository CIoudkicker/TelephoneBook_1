#include "Contact.h"




date::date(const std::string &string_date){  // формирование даты
    setDate(string_date);
}

std::string date::getDate(std::string reverse){ // Тут reverse нужен ждя сортировки по датам,
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

std::string date::getDate(){
    std::string s = "";
    s += date_int_string[0].second + '.';
    s += date_int_string[1].second + '.';
    s += date_int_string[2].second;
    return s;
}

void date::setDate(const std::string &string_date){
    int start = 0;
    int lenght = 0;
    int count = 0;

    std::vector<std::pair<int, std::string>> draft;

    try {
        for(const char &c : string_date){
            if(std::isalpha(c)) {
                Exceptions *da = new Date_Exception_AlphaInside("constructor date(" + string_date +")");
                throw da;
            }
        }
        
        // функция чисто для того чтобы сформировать строку по определенному шаблону
        std::function<std::string(int, std::string)> templateNum = [&string_date](int len, std::string s_){
            if(len < (int)s_.size()){
                Exceptions *da = new Date_Exception_OutOfRangeOfParam("constructor date(" + string_date +")");
                throw da;
            }
            int position = len - (int)s_.size();
            std::string s(position, '0');
            s.insert( position, s_);
            return s;
        };

        for (std::string::size_type i = 0; i < string_date.size()+1; i++) { // разбиение строки даты на составляющие
            
            if(std::isdigit(string_date[i])) {
                lenght++;
            }
            else{
                // понадобилось сделать так, чтобы строки дня, месяца, года подчинялась определенному шаблону
                // это нужно было в дальнейшем для алгоритма сортировки контактов по дате
                if (string_date[i] == '.' || i == string_date.size()){
                    if(i + 1 == string_date.size()) lenght++, count++;
                    count++;
                    std::string s = string_date.substr(start, lenght);
                    if(count == 1) s = templateNum(2, s);
                    if(count == 2) s = templateNum(2, s);
                    if(count == 3) s = templateNum(4, s);
                    int number = std::stoi(s);
                    draft.push_back(make_pair(number, s));
                    start += lenght + 1;
                    lenght = 0;
                }
            }
        }
        if(draft.size() != 3){
            Exceptions *da = new Date_Exception_WrongCountOfParameters("constructor date(" + string_date +")");
            throw da;
        }
        Exceptions *da = new Date_Exception_OutOfRangeOfParam("constructor date(" + string_date +")");
        
        if (!(0 < draft[0].first && draft[0].first < 32)) throw da;
        if (!(0 < draft[1].first && draft[1].first < 13)) throw da;
        if (!(0 < draft[2].first && draft[2].first < 10000)) throw da;
        delete da;

    }  catch (Exceptions *e) {
        e->what();
    }

    date_int_string = draft;
}


Contact::Contact()
{

}

Contact::Contact(int id_, std::string name_, std::string email_, date birthday_, date add_date_):
            id(id_), name(name_), email(email_), birthday(birthday_), add_date(add_date_){}

Contact::Contact(const std::vector<std::string> &vectorParam){
    if((int)vectorParam.size() == countOfParameters){
        setId(vectorParam[0]);
        name = vectorParam[1];
        email = vectorParam[2];
        birthday = date(vectorParam[3]);
        add_date = date(vectorParam[4]);
    }
}

void Contact::setId(const std::string &id_){
    bool is = true;
    try {
        for(const char &c : id_){
            if(!std::isdigit(c)){ is = false; break; }
        }
        if(is) id = std::stoi(id_);
        else{
            Exceptions *da = new Id_Exception_AlphaInside("set Id("+id_+")");
            throw da;
        }
    }  catch (Exceptions *e) {
        e->what();
    }

}

void Contact::setName(const std::string &name_){
     name = name_;
}

void Contact::setEmail(const std::string &email_){
    email = email_;
}

void Contact::setBirthday(const std::string &birthday_){
    birthday.setDate(birthday_);
}

void Contact::setAddDate(const std::string &birthday_){
    birthday.setDate(birthday_);
}


