#ifndef CONNECTION_H
#define CONNECTION_H

/*
 * Boost Serialization
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

#include "Login.h"
#include "User.h"
#include "Person.h"
#include "AccessPermissionList.h"
#include "Participant.h"
#include "Questionnaire.h"
#include "Question.h"
#include "BooleanQuestion.h"
#include "NumberQuestion.h"
#include "TextQuestion.h"

#include <QDebug>
#include <QString>

#include <string>
#include <vector>

#include "SQLMessaging.h"

class Connection
{
public:
    Connection();

    void read(std::string) ;
    std::string write() ;

    std::string getInboundHeader() ;
    void setInboundHeader(std::string header) ;
    std::string getOutboundHeader() ;
    void setOutboundHeader(std::string header) ;

    std::string getInboundMessage() ;
    void setInboundMessage(std::string message) ;
    std::string getOutboundMessage() ;
    void setOutboundMessage(std::string message) ;

private:
    int HEADER_START ; //= 0 ;
    int HEADER_END ; //= 8 ;
    int MESSAGE_START ; //= HEADER_END ;
    int MESSAGE_END ; //= -1 ;

    std::string inboundHeader ;
    std::string inboundMessage ;

    std::string outboundHeader ;
    std::string outboundMessage ;

    void coupleMessage(std::string header, std::string message) ;
    void decoupleMessage(std::string messageIn) ;

    void clear() ;

    void login() ;

    void getAUser() ;
    void getAUserFromUsername() ;
    void getAllUsers() ;
    void addUser() ;
    void deleteVectorOfUsers() ;
    void editUser() ;

    void getAllAccessPermissionLists() ;
    void addAccessPermissionList() ;
    void deleteVectorOfAccessPermissionLists() ;
    void editAccessPermissionList() ;

    void getAllParticipants() ;
    void addParticipant() ;
    void deleteVectorOfParticipants() ;
    void editParticipant() ;

    void getAllQuestionnaires() ;
    void addQuestionnaire() ;
    void deleteVectorOfQuestionnaires() ;
    void editQuestionnaire() ;
};

#endif // CONNECTION_H
