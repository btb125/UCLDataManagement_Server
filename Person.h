#ifndef PERSON_H
#define PERSON_H

/*
 * Boost Serialization
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

#include <string>

// Forward declaration of class boost::serialization::access
namespace boost
{
    namespace serialization
    {
        class access ;
    }
}

class Person
{
public:
    Person();
    Person(std::string forename, std::string surname) ;

    std::string getForename() ;
    void setForename(std::string forename) ;

    std::string getSurname() ;
    void setSurname(std::string surname) ;

    std::string getFullName() ;
    void setFullName(std::string forename, std::string surname) ;

private:
    std::string forename ;
    std::string surname ;

    friend class boost::serialization::access ;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & forename & surname ;
    }
};

#endif // PERSON_H
