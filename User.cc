#include "User.h"

User::User()
{
    this->accessPermissionList.setAllPermissionsAsFalse() ;
}

User::User(std::string forename, std::string surname,
     std::string userId, std::string password, std::string department,
     std::string role, AccessPermissionList accessPermissionList,
     bool isAccountActive)
    : Person(forename, surname)
{
    this->userId = userId ;
    this->password = password ;
    this->department = department ;
    this->role = role ;
    this->accessPermissionList = accessPermissionList ;
    this->isAccountActive = isAccountActive ;
}

//Inherited Name Functions

std::string User::getUserId()
{
    return this->userId ;
}

void User::setUserId(std::string userId)
{
    this->userId = userId ;
}

std::string User::getPassword()
{
    return this->password ;
}

void User::setPassword(std::string password)
{
    this->password = password ;
}

std::string User::getDepartment()
{
    return this->department ;
}

void User::setDepartment(std::string department)
{
    this->department = department ;
}

std::string User::getRole()
{
    return this->role ;
}

void User::setRole(std::string role)
{
    this->role = role ;
}

AccessPermissionList User::getAccessPermissionList()
{
    return this->accessPermissionList ;
}

void User::setAccessPermissionList(AccessPermissionList accessPermissionList)
{
    this->accessPermissionList.setName(accessPermissionList.getName()) ;
    this->accessPermissionList.simpleDeserialize(accessPermissionList.simpleSerialize()) ;
}

bool User::getIsAccountActive()
{
    return this->isAccountActive ;
}

void User::setIsAccountActive(bool isAccountActive)
{
    this->isAccountActive = isAccountActive ;
}
