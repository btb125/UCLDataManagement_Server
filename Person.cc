#include "Person.h"

Person::Person()
{

}

Person::Person(std::string forename, std::string surname)
{
    this->forename = forename ;
    this->surname = surname ;
}

std::string Person::getForename()
{
    return this->forename ;
}

void Person::setForename(std::string forename)
{
    this->forename = forename ;
}

std::string Person::getSurname()
{
    return this->surname ;
}

void Person::setSurname(std::string surname)
{
    this->surname = surname ;
}

std::string Person::getFullName()
{
    return this->forename + " " + this->surname ;
}

void Person::setFullName(std::string forename, std::string surname)
{
    this->forename = forename ;
    this->surname = surname ;
}
