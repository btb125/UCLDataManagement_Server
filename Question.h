#ifndef QUESTION_H
#define QUESTION_H

/*
 * Serialization (Boost)
 */
//#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>

#include <iostream>
#include <string>
#include <algorithm>

#include <QString>

// Forward declaration of class boost::serialization::access
namespace boost
{
    namespace serialization
    {
        class access ;
    }
}

class Question
{
public:
    Question();
    virtual ~Question() ;

    virtual std::string getQuestion() = 0 ;
    virtual void setQuestion(std::string q) = 0 ;

    virtual int getQNumber() ;
    virtual void setQNumber(int qNum) ;

    virtual std::string getQuestionID() ;
    virtual void setQuestionID(std::string id) ;
    virtual void setQuestionID(QString id) ;

protected:
    std::string question ;
    int number ;
    std::string id ;

private:
    friend class boost::serialization::access ;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & question
           & number
           & id ;
    }
};

BOOST_CLASS_EXPORT_KEY(Question)

#endif // QUESTION_H
