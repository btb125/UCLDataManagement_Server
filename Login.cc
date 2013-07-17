#include "Login.h"

Login::Login()
{

}

Login::Login(QString username, QString password)
{
    this->username = username.toStdString() ;
    this->password = password.toStdString() ;
}

Login::~Login()
{
//    delete this->username ;
//    delete this->password ;
}

QString Login::getQUsername()
{
    return QString::fromStdString(this->username) ;
}

void Login::setQUsername(QString username)
{
    this->username = username.toStdString() ;
}

QString Login::getQPassword()
{
    return QString::fromStdString(this->password) ;
}

void Login::setQPassword(QString password)
{
    this->password = password.toStdString() ;
}

std::string Login::getUsername()
{
    return this->username ;
}

void Login::setUsername(std::string username)
{
    this->username = username ;
}

std::string Login::getPassword()
{
    return this->password ;
}

void Login::setPassword(std::string password)
{
    this->password = password ;
}
