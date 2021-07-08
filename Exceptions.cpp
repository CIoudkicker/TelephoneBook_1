#include "Exceptions.h"

Exceptions::Exceptions()
{

}
Exceptions::Exceptions(std::string arg_message){
    message = arg_message;
}

Exceptions::Exceptions(Exceptions *arg){

    message = arg->message;
}

Exceptions::~Exceptions(){
    //delete message;
}

std::string Exceptions::what(){
    return message;
}

ASC_DESC_Exception::ASC_DESC_Exception(std::string arg) : Exceptions("ASC_DESC_Exception: " + arg){

}

ASC_DESC_Exception::ASC_DESC_Exception(ASC_DESC_Exception *arg) : Exceptions(arg){

}
