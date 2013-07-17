#include "Questionnaire.h"

Questionnaire::Questionnaire()
{

}

std::string Questionnaire::getQuestionnaireID()
{
    return this->questionnaireID ;
}

void Questionnaire::setQuestionnaireID(std::string id)
{
    this->questionnaireID = id ;
}

std::vector<Question *> Questionnaire::getQuestions()
{
    //Assign Questions Numbers for Order
    for (unsigned i = 0; i < this->questions.size(); i++)
    {
        questions.at(i)->setQNumber(i) ;
    }

    return this->questions ;
}

void Questionnaire::setQuestions(std::vector<Question *> questions)
{
    this->questions = questions ;
}

void Questionnaire::addQuestion(Question *question)
{
    this->questions.push_back(question) ;
}

void Questionnaire::removeQuestion(Question *question)
{
    this->questions.erase(std::remove(this->questions.begin(),
                                      this->questions.end(),
                                      question),
                                      this->questions.end()) ;
}

void Questionnaire::addQuestion(BooleanQuestion *question)
{
    this->questions.push_back(question) ;
}

void Questionnaire::removeQuestion(BooleanQuestion *question)
{
    this->questions.erase(std::remove(this->questions.begin(),
                                      this->questions.end(),
                                      question),
                                      this->questions.end()) ;
}

void Questionnaire::addQuestion(NumberQuestion *question)
{
    this->questions.push_back(question) ;
}

void Questionnaire::removeQuestion(NumberQuestion *question)
{
    this->questions.erase(std::remove(this->questions.begin(),
                                      this->questions.end(),
                                      question),
                                      this->questions.end()) ;
}

void Questionnaire::addQuestion(TextQuestion *question)
{
    this->questions.push_back(question) ;
}

void Questionnaire::removeQuestion(TextQuestion *question)
{
    this->questions.erase(std::remove(this->questions.begin(),
                                      this->questions.end(),
                                      question),
                                      this->questions.end()) ;
}

void Questionnaire::removeQuestionAtLocation(int location)
{
    if (location == -1)
    {
        this->questions.pop_back() ;
    }
    else
    {
        location-- ;
        this->questions.erase (this->questions.begin() + location) ;
    }
}

int Questionnaire::getQuestionCount()
{
    return this->questions.size() ;
}

void Questionnaire::sort()
{
    /*
     * Bubble Sort
     */
    for(unsigned i = 0; i < this->questions.size(); i++)
    {
        for(unsigned j = i +1; j < this->questions.size(); j++)
        {
            if(this->questions[i]->getQNumber() > this->questions[j]->getQNumber())
            {
                std::swap(this->questions[i],
                          this->questions[j]);
            }
        }

    }
}

std::string Questionnaire::getNote()
{
    return this->note ;
}

void Questionnaire::setNote(std::string note)
{
    this->note = note ;
}
