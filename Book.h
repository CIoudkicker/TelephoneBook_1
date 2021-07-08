#ifndef BOOK_H
#define BOOK_H


#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Contact.h"
#include "Exceptions.h"




using namespace std;

class Book{

    private:

        std::vector<Contact *> book;
        int countContacts;
        ASC_DESC_Exception *ASC_DESC_Wrong = new ASC_DESC_Exception("Wrong \"ASC\" or \"DESC\" parameter");

    public:

        Book();
        ~Book();
        void addContact(Contact *contact);
        void deleteContact(int id);
        int getCountContacts(){ return countContacts; }
        void sortById(std::string ASC_or_DESC);
        void sortByName(std::string ASC_or_DESC);

};

#endif // BOOK_H
