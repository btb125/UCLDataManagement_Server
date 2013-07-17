#ifndef TEXTQUESTION_H
#define TEXTQUESTION_H

/*
 * Serialization (Boost)
 */
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
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

class TextQuestion : public Question
{
public:
    TextQuestion() ;
//    ~TextQuestion() ;

    std::string getQuestion() ;
    void setQuestion(std::string q) ;

    std::string getAnswer() ;
    void setAnswer(std::string ans) ;

private:
    //Inherited Question String

    std::string answer ;

    typedef Question _super;

    friend class boost::serialization::access ;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & boost::serialization::base_object<_super>(*this) ;
        ar & answer ;
    }
};

BOOST_CLASS_EXPORT_KEY(TextQuestion)

#endif // TEXTQUESTION_H
