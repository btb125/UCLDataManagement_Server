#include "BooleanQuestion.h"

BooleanQuestion::BooleanQuestion()
{

}

std::string BooleanQuestion::getQuestion()
{
    return this->question ;
}

void BooleanQuestion::setQuestion(std::string q)
{
    this->question = q ;
}

bool BooleanQuestion::getAnswer()
{
    return this->answer ;
}

void BooleanQuestion::setAnswer(bool ans)
{
    this->answer = ans ;
}

BOOST_CLASS_EXPORT_IMPLEMENT(BooleanQuestion)
