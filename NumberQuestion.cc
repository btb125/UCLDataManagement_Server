#include "NumberQuestion.h"

NumberQuestion::NumberQuestion()
{
    range = 0 ;
}

std::string NumberQuestion::getQuestion()
{
    return this->question ;
}

void NumberQuestion::setQuestion(std::string q)
{
    this->question = q ;
}

int NumberQuestion::getAnswer()
{
    return this->answer ;
}

void NumberQuestion::setAnswer(int ans)
{
    this->answer = ans ;
}

int NumberQuestion::getBase()
{
    return this->base ;
}

void NumberQuestion::setBase(int base)
{
    this->base = base ;
}

int NumberQuestion::getRange()
{
    return this->range ;
}

void NumberQuestion::setRange(int range)
{
    this->range = range ;
}

BOOST_CLASS_EXPORT_IMPLEMENT(NumberQuestion)
