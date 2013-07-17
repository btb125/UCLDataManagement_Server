#ifndef BOOLEANQUESTION_H
#define BOOLEANQUESTION_H

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

class BooleanQuestion : public Question
{
public:
    BooleanQuestion() ;
//    ~BooleanQuestion() ;

    std::string getQuestion() ;
    void setQuestion(std::string q) ;

    bool getAnswer() ;
    void setAnswer(bool ans) ;

private:
    //Inherited Question String

    bool answer ;

    typedef Question _super;

    friend class boost::serialization::access ;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & boost::serialization::base_object<_super>(*this) ;
        ar & answer ;
    }
} ;

BOOST_CLASS_EXPORT_KEY(BooleanQuestion)

#endif // BOOLEANQUESTION_H
