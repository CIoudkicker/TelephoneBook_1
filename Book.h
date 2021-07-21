#ifndef BOOK_H
#define BOOK_H


#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include "Contact.h"
#include "Exceptions.h"



using namespace std;

class Book{

    private:
        int countContacts;
        std::vector<Contact> book;
        ASC_DESC_Exception *currentWrong;

    public:

        Book();
        ~Book();
        void addContact(Contact &contact);
        void deleteContact(int id);
        void clearBook();
        int getCountContacts(){ return countContacts; }
        std::vector<Contact> getBookOfContacts(){ return book; }


        void kindOfSorting(std::string ASC_or_DESC, std::string ExceptionMessage,
                                 function<bool(Contact &a, Contact &b)> sortRuleASC,
                                 function<bool(Contact &a, Contact &b)> sortRuleDESC);
        virtual void sortById(std::string ASC_or_DESC);
        virtual void sortByName(std::string ASC_or_DESC);
        virtual void sortByEmail(std::string ASC_or_DESC);
        virtual void sortByBirthday(std::string ASC_or_DESC);
        virtual void sortByAddDate(std::string ASC_or_DESC);
};

#endif // BOOK_H
