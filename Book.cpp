#include "Book.h"

Book::Book(){
    countContacts = 0;
    currentWrong = new ASC_DESC_Exception("");
}

Book::~Book(){
    delete currentWrong;
}

void Book::addContact(Contact *contact){
    book.push_back(contact);
    countContacts++;
}

void Book::deleteContact(int id){
    book.erase(book.begin() + id);
    countContacts--;
}

void Book::kindOfSorting(std::string ASC_or_DESC, std::string ExceptionMessage,
                         function<bool(Contact *a, Contact *b)> sortRuleASC,
                         function<bool(Contact *a, Contact *b)> sortRuleDESC)
{
    try {
        if(ASC_or_DESC == "ASC"){
            sort(book.begin(), book.end(), sortRuleASC);
        }else
        if (ASC_or_DESC == "DESC"){
            sort(book.begin(), book.end(), sortRuleDESC);
        }else{
            delete currentWrong;
            ASC_DESC_Exception currentWrong(ExceptionMessage);
            throw currentWrong;
        }
    }  catch (Exceptions *e) {
        e->what();
    }

}

void Book::sortById(std::string ASC_or_DESC){
    kindOfSorting(ASC_or_DESC, "sortById",
                  [](Contact* a,  Contact* b){ return a->getId() < b->getId();},
                  [](Contact* a,  Contact* b){ return a->getId() > b->getId();});
}

void Book::sortByName(std::string ASC_or_DESC){
    kindOfSorting(ASC_or_DESC, "sortByName",
                  [](Contact* a,  Contact* b){ return a->getName() < b->getName();},
                  [](Contact* a,  Contact* b){ return a->getName() > b->getName();});
}

void Book::sortByEmail(std::string ASC_or_DESC){
    kindOfSorting(ASC_or_DESC, "sortByEmail",
                  [](Contact* a,  Contact* b){ return a->getEmail() < b->getEmail();},
                  [](Contact* a,  Contact* b){ return a->getEmail() > b->getEmail();});
}

void Book::sortByBirthday(std::string ASC_or_DESC){
    kindOfSorting(ASC_or_DESC, "sortByBirthday",
                  [](Contact* a,  Contact* b){ return a->getBirthday("reverse") < b->getBirthday("reverse");},
                  [](Contact* a,  Contact* b){ return a->getBirthday("reverse") > b->getBirthday("reverse");});
}

void Book::sortByAddDate(std::string ASC_or_DESC){
    kindOfSorting(ASC_or_DESC, "sortByAddDate",
                  [](Contact* a,  Contact* b){ return a->getAddDate("reverse") < b->getAddDate("reverse");},
                  [](Contact* a,  Contact* b){ return a->getAddDate("reverse") > b->getAddDate("reverse");});
}

