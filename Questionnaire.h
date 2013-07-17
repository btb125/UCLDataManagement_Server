#ifndef QUESTIONNAIRE_H
#define QUESTIONNAIRE_H

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

#include <QDebug>

#include <string>
#include <vector>
#include <algorithm>

#include "Question.h"
#include "NumberQuestion.h"
#include "BooleanQuestion.h"
#include "TextQuestion.h"

// Forward declaration of class boost::serialization::access
namespace boost
{
    namespace serialization
    {
        class access ;
    }
}

class Questionnaire
{
public:
    Questionnaire();

    std::string getQuestionnaireID() ;
    void setQuestionnaireID(std::string id) ;

    std::vector<Question *> getQuestions() ;
    void setQuestions(std::vector<Question *> questions) ;

    void addQuestion(Question *question) ;
    void removeQuestion(Question *question) ;

    void addQuestion(BooleanQuestion *question) ;
    void removeQuestion(BooleanQuestion *question) ;
    void removeQuestionAtLocation(int location) ;

    void addQuestion(NumberQuestion *question) ;
    void removeQuestion(NumberQuestion *question) ;

    void addQuestion(TextQuestion *question) ;
    void removeQuestion(TextQuestion *question) ;

    int getQuestionCount() ;

    void sort() ;

    std::string getNote() ;
    void setNote(std::string note) ;

protected:
    std::string questionnaireID ;
    std::vector<Question *> questions ;
    std::string note ;

private:
    friend class boost::serialization::access ;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
//        ar.template register_type<BooleanQuestion>() ;
//        ar.template register_type<NumberQuestion>() ;
//        ar.template register_type<TextQuestion>() ;

        ar & questionnaireID ;
        ar & questions ;
        ar & note ;
    }
};

#endif // QUESTIONNAIRE_H
