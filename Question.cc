#include "Question.h"

Question::Question()
{

}

Question::~Question()
{

}

int Question::getQNumber()
{
    return this->number ;
}

void Question::setQNumber(int qNum)
{
    this->number = qNum ;
}

std::string Question::getQuestionID()
{
    return this->id ;
}

void Question::setQuestionID(std::string id)
{
    this->id = id ;
}

void Question::setQuestionID(QString id)
{
    this->id = id.toStdString() ;
}

BOOST_CLASS_EXPORT_IMPLEMENT(Question)
