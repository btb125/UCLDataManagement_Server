#ifndef USER_H
#define USER_H

/*
 * Boost Serialization
 */
#include <sstream>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>

#include <string>

#include "Person.h"
#include "AccessPermissionList.h"

// Forward declaration of class boost::serialization::access
namespace boost
{
    namespace serialization
    {
        class access ;
    }
}

class User : public Person
{
public:
    User();
    User(std::string forename, std::string surname,
         std::string userId, std::string password, std::string department,
         std::string role, AccessPermissionList accessPermissionList,
         bool isAccountActive) ;

    //Inherited Name Functions

    std::string getUserId() ;
    void setUserId(std::string userId) ;

    std::string getPassword() ;
    void setPassword(std::string password) ;

    std::string getDepartment() ;
    void setDepartment(std::string department) ;

    std::string getRole() ;
    void setRole(std::string role) ;

    AccessPermissionList getAccessPermissionList() ;
    void setAccessPermissionList(AccessPermissionList accessPermissionList) ;

    bool getIsAccountActive() ;
    void setIsAccountActive(bool isAccountActive) ;

private:
    //Inherted Name Properties

    std::string userId ;
    std::string password ;
    std::string department ;
    std::string role ;
    AccessPermissionList accessPermissionList ;
    bool isAccountActive ;

    typedef Person _super;

    friend class boost::serialization::access ;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & boost::serialization::base_object<_super>(*this);
        ar & userId & password
                & department & role
                & accessPermissionList
                & isAccountActive ;
    }
};

#endif // USER_H
