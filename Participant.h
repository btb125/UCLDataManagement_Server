#ifndef PARTICIPANT_H
#define PARTICIPANT_H

/*
 * Serialization (Boost)
 */
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>

#include "Person.h"

#include <string>
#include <iostream>

// Forward declaration of class boost::serialization::access
namespace boost
{
    namespace serialization
    {
        class access ;
    }
}

class Participant : public Person
{
public:
    Participant();

    Participant(std::string forename, std::string surname,
                std::string participantID, std::string dateOfBirth, bool sex,
                std::string guardianForename, std::string guardianSurname,
                std::string contactHome, std::string contactWork, std::string contactMobile,
                std::string addressLine1, std::string addressLine2,
                std::string addressLine3, std::string addressLine4,
                std::string addressPostCode) ;

    //Inherited Name Functions

    std::string getParticipantID() ;
    void setParticipantID(std::string id) ;

    std::string getDateOfBirth() ;
    std::string getDateOfBirthAsString() ;
    void setDateOfBirth(std::string dob) ;

    bool getSex() ;
    void setSex(bool sex) ;

    std::string getGuardianForename() ;
    void setGuardianForename(std::string forename) ;

    std::string getGuardianSurname() ;
    void setGuardianSurname(std::string surname) ;

    std::string getContactHome() ;
    void setContactHome(std::string contact) ;

    std::string getContactWork() ;
    void setContactWork(std::string contact) ;

    std::string getContactMobile() ;
    void setContactMobile(std::string contact) ;

    std::string getAddressLine1() ;
    void setAddressLine1(std::string addressLine) ;

    std::string getAddressLine2() ;
    void setAddressLine2(std::string addressLine) ;

    std::string getAddressLine3() ;
    void setAddressLine3(std::string addressLine) ;

    std::string getAddressLine4() ;
    void setAddressLine4(std::string addressLine) ;

    std::string getAddresssPostCode() ;
    void setAddressPostCode(std::string postCode) ;

private:
    //Inheritied Name Properties

    std::string participantID ;
    std::string dateOfBirth ;

    bool sex ; //0: Female, 1:Male

    std::string guardianForename ;
    std::string guardianSurname ;

    std::string contactHome ;
    std::string contactWork ;
    std::string contactMobile ;

    std::string addressLine1 ;
    std::string addressLine2 ;
    std::string addressLine3 ;
    std::string addressLine4 ;
    std::string addressPostCode ;

    typedef Person _super;

    friend class boost::serialization::access ;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & boost::serialization::base_object<_super>(*this) ;
        ar & participantID
            & dateOfBirth
            & sex
            & guardianForename & guardianSurname
            & contactHome & contactWork & contactMobile
            & addressLine1 & addressLine2 & addressLine3
            & addressLine4 & addressPostCode ;
    }
};

#endif // PARTICIPANT_H
