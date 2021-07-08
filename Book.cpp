#include "Book.h"

Book::Book(){
    countContacts = 0;
}

Book::~Book(){

}

void Book::addContact(Contact *contact){
    book.push_back(contact);
    countContacts++;
}

void Book::deleteContact(int id){
    book.erase(book.begin() + id);
    countContacts--;
}


void Book::sortById(std::string ASC_or_DESC){
    try {
        if(ASC_or_DESC == "ASC"){
            sort(book.begin(), book.end(), [] ( Contact* a,  Contact* b){ return a->getName() < b->getName(); });
        }else
        if (ASC_or_DESC == "DESC"){
            sort(book.begin(), book.end(), [] ( Contact* a,  Contact* b){ return a->getName() > b->getName(); });
        }else{
            ASC_DESC_Exception *sortById_Wrong = new ASC_DESC_Exception("sortById: " + ASC_DESC_Wrong->what());
            throw sortById_Wrong;
        }
    }  catch (Exceptions *e) {
        e->what();
    }
}

void Book::sortByName(std::string ASC_or_DESC){
    try {
        if(ASC_or_DESC == "ASC"){
            sort(book.begin(), book.end(), [] ( Contact* a,  Contact* b){ return a->getName() < b->getName(); });
        }else
        if (ASC_or_DESC == "DESC"){
            sort(book.begin(), book.end(), [] ( Contact* a,  Contact* b){ return a->getName() > b->getName(); });
        }else{
            ASC_DESC_Exception *sortByName_Wrong = new ASC_DESC_Exception("sortByName: " + ASC_DESC_Wrong->what());
            throw sortByName_Wrong;
        }
    }  catch (Exceptions *e) {
        e->what();
    }
}
