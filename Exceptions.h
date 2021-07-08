#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Exceptions{

    private:

        std::string message;

    public:

        Exceptions();
        Exceptions(std::string arg_message);
        Exceptions(Exceptions *arg);
        ~Exceptions();

        std::string what();
};


class ASC_DESC_Exception : public Exceptions
{


    public:

    explicit ASC_DESC_Exception(std::string arg);

    explicit ASC_DESC_Exception(ASC_DESC_Exception *arg);

};

#endif // EXCEPTIONS_H
