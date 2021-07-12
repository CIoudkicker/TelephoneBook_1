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
        Exceptions(Exceptions &arg);
        ~Exceptions();

        std::string what();
};


class ASC_DESC_Exception : public Exceptions
{


    public:

    ASC_DESC_Exception(std::string arg);

    ASC_DESC_Exception(ASC_DESC_Exception &arg);

};

class Date_Exception : public Exceptions
{


    public:

    Date_Exception(std::string arg);

    Date_Exception(Date_Exception &arg);

};

class Date_Exception_WrongCountOfParameters : public Date_Exception
{

    public:

    Date_Exception_WrongCountOfParameters(std::string arg);

    Date_Exception_WrongCountOfParameters(Date_Exception_WrongCountOfParameters &arg);

};

class Date_Exception_AlphaInside : public Date_Exception
{

    public:

    Date_Exception_AlphaInside(std::string arg);

    Date_Exception_AlphaInside(Date_Exception_AlphaInside &arg);

};

class Date_Exception_OutOfRangeOfParam : public Date_Exception
{

    public:

    Date_Exception_OutOfRangeOfParam(std::string arg);

    Date_Exception_OutOfRangeOfParam(Date_Exception_OutOfRangeOfParam &arg);

};

class Date_Exception_ReverseOrNot : public Date_Exception
{

    public:

    Date_Exception_ReverseOrNot(std::string arg);

    Date_Exception_ReverseOrNot(Date_Exception_ReverseOrNot &arg);

};


#endif // EXCEPTIONS_H
