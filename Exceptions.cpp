#include "Exceptions.h"

Exceptions::Exceptions()
{

}
Exceptions::Exceptions(std::string arg_message){
    message = arg_message;
}

Exceptions::Exceptions(Exceptions &arg){
    message = arg.message;
}

Exceptions::~Exceptions(){
    //delete message;
}

void Exceptions::what(){

    if(executeOnce){
        QString s = QString::fromStdString(message);
        qDebug() << s;
        executeOnce = false;
    }
    throw this;
}

void Exceptions::what(MessageBoxShow msg_box){

    if(executeOnce){
        QString s = QString::fromStdString(message);
        qDebug() << s;
        if(msg_box == MessageBoxShow::Show){
            QWidget widget;
            QMessageBox::warning(&widget, "Exception", s, QMessageBox::Ok, QMessageBox::Ok);
        }
        executeOnce = false;
    }
    throw this;
}

ASC_DESC_Exception::ASC_DESC_Exception(std::string arg) : Exceptions("ASC_DESC_Exception: " + arg + ": Wrong \"ASC\" or \"DESC\" parameter. Please, write parameter correctly"){

}

ASC_DESC_Exception::ASC_DESC_Exception(ASC_DESC_Exception &arg) : Exceptions(arg){

}

Date_Exception::Date_Exception(std::string arg) : Exceptions("Date_Exception: " + arg + ": Wrong data parameter. Please, write parameter correctly"){

}

void Date_Exception::what(){ Exceptions::what(Show); };


Date_Exception::Date_Exception(Date_Exception &arg) : Exceptions(arg){

}

Date_Exception_WrongCountOfParameters::Date_Exception_WrongCountOfParameters(std::string arg) : Date_Exception("WrongCountOfParameters: " + arg + ": Wrong count of data parameters. You need 3 parameters strictly"){

}

Date_Exception_WrongCountOfParameters::Date_Exception_WrongCountOfParameters(Date_Exception_WrongCountOfParameters &arg) : Date_Exception(arg){

}

Date_Exception_AlphaInside::Date_Exception_AlphaInside(std::string arg) : Date_Exception("AlphaInside: " + arg + ": Wrong structure of data. Found alphabet character"){

}

Date_Exception_AlphaInside::Date_Exception_AlphaInside(Date_Exception_AlphaInside &arg) : Date_Exception(arg){

}

Date_Exception_OutOfRangeOfParam::Date_Exception_OutOfRangeOfParam(std::string arg) : Date_Exception("OutOfRangeOfParam: " + arg + ": Wrong range of date parameters"){

}

Date_Exception_OutOfRangeOfParam::Date_Exception_OutOfRangeOfParam(Date_Exception_OutOfRangeOfParam &arg) : Date_Exception(arg){

}

Date_Exception_ReverseOrNot::Date_Exception_ReverseOrNot(std::string arg) : Date_Exception("ReverseOrNot: " + arg + ": Wrong \"reverse date or not\" parameter, be careful!"){

}

Date_Exception_ReverseOrNot::Date_Exception_ReverseOrNot(Date_Exception_ReverseOrNot &arg) : Date_Exception(arg){

}

FileOpen_Exceptions::FileOpen_Exceptions(std::string arg) : Exceptions("FileOpen_Exceptions: " + arg + ": Couldn't open save file!"){

}

FileOpen_Exceptions::FileOpen_Exceptions(FileOpen_Exceptions &arg) : Exceptions(arg){

}
