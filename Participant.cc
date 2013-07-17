#include "Participant.h"

Participant::Participant()
{
}

Participant::Participant(std::string forename, std::string surname,
            std::string participantID, std::string dob, bool sex,
            std::string guardianForename, std::string guardianSurname,
            std::string contactHome, std::string contactWork, std::string contactMobile,
            std::string addressLine1, std::string addressLine2,
            std::string addressLine3, std::string addressLine4,
            std::string addressPostCode)
            : Person(forename, surname)
{
    this->participantID = participantID ;
    this->dateOfBirth = dob ;
    this->sex = sex ;
    this->guardianForename = guardianForename ;
    this->guardianSurname = guardianSurname ;
    this->contactHome = contactHome ;
    this->contactWork = contactWork ;
    this->contactMobile = contactMobile ;
    this->addressLine1 = addressLine1 ;
    this->addressLine2 = addressLine2 ;
    this->addressLine3 = addressLine3 ;
    this->addressLine4 = addressLine4 ;
    this->addressPostCode = addressPostCode ;
}

std::string Participant::getParticipantID()
{
    return this->participantID ;
}

void Participant::setParticipantID(std::string id)
{
    this->participantID = id ;
}

std::string Participant::getDateOfBirth()
{
    return this->dateOfBirth ;
}

std::string Participant::getDateOfBirthAsString()
{
    return this->dateOfBirth ;
}

void Participant::setDateOfBirth(std::string dob)
{
    this->dateOfBirth = dob ;
}

bool Participant::getSex()
{
    return this->sex ;
}

void Participant::setSex(bool sex)
{
    this->sex = sex ;
}

std::string Participant::getGuardianForename()
{
    return this->guardianForename ;
}

void Participant::setGuardianForename(std::string forename)
{
    this->guardianForename = forename ;
}

std::string Participant::getGuardianSurname()
{
    return this->guardianSurname ;
}

void Participant::setGuardianSurname(std::string surname)
{
    this->guardianSurname = surname ;
}

std::string Participant::getContactHome()
{
    return this->contactHome ;
}

void Participant::setContactHome(std::string contact)
{
    this->contactHome = contact ;
}

std::string Participant::getContactWork()
{
    return this->contactWork ;
}

void Participant::setContactWork(std::string contact)
{
    this->contactWork = contact ;
}

std::string Participant::getContactMobile()
{
    return this->contactMobile ;
}

void Participant::setContactMobile(std::string contact)
{
    this->contactMobile = contact ;
}

std::string Participant::getAddressLine1()
{
    return this->addressLine1 ;
}

void Participant::setAddressLine1(std::string addressLine)
{
    this->addressLine1 = addressLine ;
}

std::string Participant::getAddressLine2()
{
    return this->addressLine2 ;
}

void Participant::setAddressLine2(std::string addressLine)
{
    this->addressLine2 = addressLine ;
}

std::string Participant::getAddressLine3()
{
    return this->addressLine3 ;
}

void Participant::setAddressLine3(std::string addressLine)
{
    this->addressLine3 = addressLine ;
}

std::string Participant::getAddressLine4()
{
    return this->addressLine4 ;
}

void Participant::setAddressLine4(std::string addressLine)
{
    this->addressLine4 = addressLine ;
}

std::string Participant::getAddresssPostCode()
{
    return this->addressPostCode ;
}

void Participant::setAddressPostCode(std::string postCode)
{
    this->addressPostCode = postCode ;
}
