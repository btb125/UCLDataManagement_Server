#include "TextQuestion.h"

TextQuestion::TextQuestion()
{

}

std::string TextQuestion::getQuestion()
{
    return this->question ;
}

void TextQuestion::setQuestion(std::string q)
{
    this->question = q ;
}

std::string TextQuestion::getAnswer()
{
    return this->answer ;
}

void TextQuestion::setAnswer(std::string ans)
{
    this->answer = ans ;
}

BOOST_CLASS_EXPORT_IMPLEMENT(TextQuestion)
