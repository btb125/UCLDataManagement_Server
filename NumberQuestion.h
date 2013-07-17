#ifndef NUMBERQUESTION_H
#define NUMBERQUESTION_H

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

#include "Question.h"

#include <string>

// Forward declaration of class boost::serialization::access
namespace boost
{
    namespace serialization
    {
        class access ;
    }
}

class NumberQuestion : public Question
{
public:
    NumberQuestion() ;

    std::string getQuestion() ;
    void setQuestion(std::string q) ;

    int getAnswer() ;
    void setAnswer(int ans) ;

    int getBase() ;
    void setBase(int base) ;

    int getRange() ;
    void setRange(int range) ;

private:
    //Inherited Question String

    int range ;
    int base ;

    int answer ;

    typedef Question _super;

    friend class boost::serialization::access ;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & boost::serialization::base_object<_super>(*this) ;
        ar & range & base ;
        ar & answer ;
    }
};

BOOST_CLASS_EXPORT_KEY(NumberQuestion)

#endif // NUMBERQUESTION_H
