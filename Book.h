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

        std::vector<Contact *> book;
        int countContacts;
        ASC_DESC_Exception *currentWrong;

    public:

        Book();
        ~Book();
        void addContact(Contact *contact);
        void deleteContact(int id);
        int getCountContacts(){ return countContacts; }
        void kindOfSorting(std::string ASC_or_DESC, std::string ExceptionMessage,
                            function<bool(Contact *a, Contact *b)> sortRuleASC,
                            function<bool(Contact *a, Contact *b)> sortRuleDESC);
        void sortById(std::string ASC_or_DESC);
        void sortByName(std::string ASC_or_DESC);
        void sortByEmail(std::string ASC_or_DESC);
        void sortByBirthday(std::string ASC_or_DESC);
        void sortByAddDate(std::string ASC_or_DESC);
};

#endif // BOOK_H
