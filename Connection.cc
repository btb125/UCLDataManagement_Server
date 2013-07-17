#include "Connection.h"

Connection::Connection()
{
    HEADER_START = 0 ;
    HEADER_END = 8 ;
    MESSAGE_START = HEADER_END ;
    MESSAGE_END = -1 ;
}

void Connection::read(std::string messageIn)
{
    decoupleMessage(messageIn) ;

    if (inboundHeader == "login   ")
    {
        login() ;
    }

    if (inboundHeader == "get*Usrs")
    {
        getAllUsers() ;
    }

    if (inboundHeader == "delxUsrs")
    {
        this->deleteVectorOfUsers() ;
    }

    if (inboundHeader == "editUser")
    {
        this->editUser() ;
    }

    if (inboundHeader == "addUser ")
    {
        this->addUser() ;
    }

    if (inboundHeader == "get*APLs")
    {
        getAllAccessPermissionLists() ;
    }

    if (inboundHeader == "delxAPLs")
    {
        deleteVectorOfAccessPermissionLists();
    }

    if (inboundHeader == "editAPL ")
    {
        editAccessPermissionList();
    }

    if (inboundHeader == "addAPL  ")
    {
        addAccessPermissionList() ;
    }

    if (inboundHeader == "get*Ppts")
    {
        getAllParticipants() ;
    }

    if (inboundHeader == "delxPpts")
    {
        deleteVectorOfParticipants();
    }

    if (inboundHeader == "editPpt ")
    {
        editParticipant();
    }

    if (inboundHeader == "addPpt  ")
    {
        addParticipant() ;
    }

    if (inboundHeader == "get*Ques")
    {
        getAllQuestionnaires(); ;
    }

    if (inboundHeader == "delxQues")
    {
        deleteVectorOfQuestionnaires();
    }

    if (inboundHeader == "editQues")
    {
        editQuestionnaire();
    }

    if (inboundHeader == "addQues ")
    {
        addQuestionnaire() ;
    }
}

std::string Connection::write()
{
    /*
     * Output Message
     */
    return outboundHeader.append(outboundMessage) ;

    /*
     * Clear I/O
     */
    clear() ;
}

std::string Connection::getInboundHeader()
{
    return this->inboundHeader ;
}

void Connection::setInboundHeader(std::string header)
{
    this->inboundHeader = header ;
}

std::string Connection::getOutboundHeader()
{
    return this->outboundHeader ;
}

void Connection::setOutboundHeader(std::string header)
{
    this->outboundHeader = header ;
}

std::string Connection::getInboundMessage()
{
    return this->inboundMessage ;
}

void Connection::setInboundMessage(std::string message)
{
    this->inboundMessage = message ;
}

std::string Connection::getOutboundMessage()
{
    return this->outboundMessage ;
}

void Connection::setOutboundMessage(std::string message)
{
    this->outboundMessage = message ;
}

void Connection::coupleMessage(std::string header, std::string message)
{
    header = message ; //Hide Warning
}

void Connection::decoupleMessage(std::string messageIn)
{
    this->inboundHeader = messageIn.substr(HEADER_START, HEADER_END) ;
    this->inboundMessage = messageIn.substr(MESSAGE_START, messageIn.length()-MESSAGE_END) ;
}

void Connection::clear()
{
    inboundHeader = " " ;
    inboundMessage = " " ;

    outboundHeader = " " ;
    outboundMessage = " " ;
}

void Connection::login()
{
    Login login ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> login ;

        inboundMessage = archiveStream.str() ;
    }

    SQLMessaging sqlMessaging ;
    /*
     * If Login SUCCEEDED
     */
    if (sqlMessaging.checkLoginCredentials(login.getUsername(),
                                           login.getPassword()))
    {
        /*
         * Set Header
         */
        outboundHeader = "user    " ;

        /*
         * Set Message
         */
        //Get User Info
        User user ;
        user = sqlMessaging.getUserFromUsername(login.getUsername()) ;
        //Serialize User Info
        {
            std::ostringstream archiveStream ;
            boost::archive::text_oarchive archive(archiveStream) ;
            archive << user ;
            //Set Outbound Message to Serialized Info
            this->outboundMessage = archiveStream.str() ;
        }
    }
    /*
     * If Login FAILED
     */
    else
    {
        outboundHeader = "retMsg  " ;
        outboundMessage = "Login Failed!\nIncorrect Username or Password." ;
    }

}

void Connection::getAUser()
{

}

void Connection::getAUserFromUsername()
{

}

void Connection::getAllUsers()
{
    SQLMessaging sqlMessaging ;

    /*
     * Set Header
     */
    outboundHeader = "ret*Usrs" ;

    /*
     * Set Message
     */
    //Get User Info
    std::vector<User> users ;
    users = sqlMessaging.getAllUsers() ;

    //Serialize User Info
    {
        std::ostringstream archiveStream ;
        boost::archive::text_oarchive archive(archiveStream) ;
        archive << BOOST_SERIALIZATION_NVP(users) ;

        //Set Outbound Message to Serialized Info
        this->outboundMessage = archiveStream.str() ;
    }
}

void Connection::addUser()
{
    //Deserialize APL
    User user ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> user ;

        inboundMessage = archiveStream.str() ;
    }

    //Outbound Header remains the same regardless of outcome
    outboundHeader = "retMsg  " ;

    SQLMessaging sqlMessaging ;

    //If DOESN'T Exist
    if (!sqlMessaging.checkIfUserExists(user))
    {
        //Message to Reply IF Added
        if (sqlMessaging.addUser(user))
        {
            outboundHeader = "updMsg  " ;
            outboundMessage = "User" ;
        }
        else
        {
            outboundMessage = "Error: Couldn't Add User\nPlease Contact System Administrator." ;
        }
    }
    else
    {
        outboundMessage = "Error: User Already Exists!" ;
    }
}

void Connection::deleteVectorOfUsers()
{
    //Deserialize Users
    std::vector<User> usersToBeDeleted ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> BOOST_SERIALIZATION_NVP(usersToBeDeleted) ;
    }

    //Outbound Header remains the same regardless of outcome
    outboundHeader = "retMsg  " ;

    SQLMessaging sqlMessaging ;

    //If All APLs Exist
    if (sqlMessaging.checkIfUsersExist(usersToBeDeleted))
    {
        //Message to Reply IF All Deleted
        if (sqlMessaging.deleteVectorOfUsers(usersToBeDeleted))
        {
            outboundHeader = "updMsg  " ;
            outboundMessage = "User" ;
        }
        else
        {
            outboundMessage = "Error: Couldn't Delete User(s)\nPlease Contact System Administrator." ;
        }
    }
    else
    {
        outboundMessage = "Error: User(s) Non-Existent!" ;
    }
}

void Connection::editUser()
{
    //Deserialize User
    User userToBeEditted ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> userToBeEditted ;
    }

    //Outbound Header remains the same regardless of outcome
    outboundHeader = "retMsg  " ;

    SQLMessaging sqlMessaging ;

    //If All APLs Exist
    if (sqlMessaging.checkIfUserExists(userToBeEditted))
    {
        //Message to Reply IF All Deleted
        if (sqlMessaging.editUser(userToBeEditted))
        {
            outboundHeader = "updMsg  " ;
            outboundMessage = "User" ;
        }
        else
        {
            outboundMessage = "Error: Couldn't Edit User\nPlease Contact System Administrator." ;
        }
    }
    else
    {
        outboundMessage = "Error: User Non-Existent!" ;
    }
}

void Connection::getAllAccessPermissionLists()
{
    SQLMessaging sqlMessaging ;

    /*
     * Set Header
     */
    outboundHeader = "ret*APLs" ;

    /*
     * Set Message
     */
    //Get User Info
    std::vector<AccessPermissionList> apls ;
    apls = sqlMessaging.getAllAccessPermissionLists() ;

    //Serialize User Info
    {
        std::ostringstream archiveStream ;
        boost::archive::text_oarchive archive(archiveStream) ;
        archive << BOOST_SERIALIZATION_NVP(apls) ;

        //Set Outbound Message to Serialized Info
        this->outboundMessage = archiveStream.str() ;
    }
}

void Connection::addAccessPermissionList()
{
    //Deserialize APL
    AccessPermissionList apl ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> apl ;

        inboundMessage = archiveStream.str() ;
    }

    //Outbound Header remains the same regardless of outcome
    outboundHeader = "retMsg  " ;

    SQLMessaging sqlMessaging ;

    //If DOESN'T Exist
    if (!sqlMessaging.checkIfAccessPermissionListExists(apl))
    {
        //Message to Reply IF Added
        if (sqlMessaging.addAccessPermissionList(apl))
        {
            outboundHeader = "updMsg  " ;
            outboundMessage = "APL" ;
        }
        else
        {
            outboundMessage = "Error: Couldn't Add Access Permission List\nPlease Contact System Administrator." ;
        }
    }
    else
    {
        outboundMessage = "Error: Access Permission List Already Exists!" ;
    }
}

void Connection::deleteVectorOfAccessPermissionLists()
{
    //Deserialize APLs
    std::vector<AccessPermissionList> aplsToBeDeleted ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> BOOST_SERIALIZATION_NVP(aplsToBeDeleted) ;
    }

    //Outbound Header remains the same regardless of outcome
    outboundHeader = "retMsg  " ;

    SQLMessaging sqlMessaging ;

    //If All APLs Exist
    if (sqlMessaging.checkIfAccessPermissionListsExist(aplsToBeDeleted))
    {
        //Message to Reply IF All Deleted
        if (sqlMessaging.deleteVectorOfAccessPermissionLists(aplsToBeDeleted))
        {
            outboundHeader = "updMsg  " ;
            outboundMessage = "APL" ;
        }
        else
        {
            outboundMessage = "Error: Couldn't Delete Access Permission List\nPlease Contact System Administrator." ;
        }
    }
    else
    {
        outboundMessage = "Error: Access Permission List(s) Non-Existent!" ;
    }
}

void Connection::editAccessPermissionList()
{
    //Deserialize APL
    AccessPermissionList aplToBeEdited ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> aplToBeEdited ;
    }

    //Outbound Header remains the same regardless of outcome
    outboundHeader = "retMsg  " ;

    SQLMessaging sqlMessaging ;

    //If All APLs Exist
    if (sqlMessaging.checkIfAccessPermissionListExists(aplToBeEdited))
    {
        //Message to Reply IF All Deleted
        if (sqlMessaging.editAccessPermissionList(aplToBeEdited))
        {
            outboundHeader = "updMsg  " ;
            outboundMessage = "APL" ;
        }
        else
        {
            outboundMessage = "Error: Couldn't Edit Access Permission List\nPlease Contact System Administrator." ;
        }
    }
    else
    {
        outboundMessage = "Error: Access Permission List(s) Non-Existent!" ;
    }
}

void Connection::getAllParticipants()
{
    SQLMessaging sqlMessaging ;

    /*
     * Set Header
     */
    outboundHeader = "ret*Ppts" ;

    /*
     * Set Message
     */
    //Get User Info
    std::vector<Participant> participants ;
    participants = sqlMessaging.getAllParticipants() ;

    //Serialize User Info
    {
        std::ostringstream archiveStream ;
        boost::archive::text_oarchive archive(archiveStream) ;
        archive << BOOST_SERIALIZATION_NVP(participants) ;

        //Set Outbound Message to Serialized Info
        this->outboundMessage = archiveStream.str() ;
    }
}

void Connection::addParticipant()
{
    //Deserialize Participant
    Participant participant ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> participant ;

        inboundMessage = archiveStream.str() ;
    }

    //Outbound Header remains the same regardless of outcome
    outboundHeader = "retPpt  " ;

    SQLMessaging sqlMessaging ;

    //If DOESN'T Exist
    if (!sqlMessaging.checkIfParticipantExists(participant))
    {
        //Message to Reply IF Added
        if (sqlMessaging.addParticipant(participant))
        {
            outboundHeader = "updMsg  " ;
            outboundMessage = "Participant" ;
        }
        else
        {
            outboundMessage = "Error: Couldn't Add Participant\nPlease Contact System Administrator." ;
        }
    }
    else
    {
        outboundMessage = "Error: Participant Already Exists!" ;
    }
}

void Connection::deleteVectorOfParticipants()
{
    //Deserialize Participants
    std::vector<Participant> participantsToBeDeleted ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> BOOST_SERIALIZATION_NVP(participantsToBeDeleted) ;
    }

    //Outbound Header remains the same regardless of outcome
    outboundHeader = "retMsg  " ;

    SQLMessaging sqlMessaging ;

    //If All Participants Exist
    if (sqlMessaging.checkIfParticipantsExist(participantsToBeDeleted))
    {
        //Message to Reply IF All Deleted
        if (sqlMessaging.deleteVectorOfParticipants(participantsToBeDeleted))
        {
            outboundHeader = "updMsg  " ;
            outboundMessage = "Participant" ;
        }
        else
        {
            outboundMessage = "Error: Couldn't Delete Participant(s)\nPlease Contact System Administrator." ;
        }
    }
    else
    {
        outboundMessage = "Error: Participant(s) Non-Existent!" ;
    }
}

void Connection::editParticipant()
{
    //Deserialize Participant
    Participant participantToBeEdited ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> participantToBeEdited ;
    }

    //Outbound Header remains the same regardless of outcome
    outboundHeader = "retMsg  " ;

    SQLMessaging sqlMessaging ;

    //If All APLs Exist
    if (sqlMessaging.checkIfParticipantExists(participantToBeEdited))
    {
        //Message to Reply IF All Deleted
        if (sqlMessaging.editParticipant(participantToBeEdited))
        {
            outboundHeader = "updMsg  " ;
            outboundMessage = "Participant" ;
        }
        else
        {
            outboundMessage = "Error: Couldn't Edit Participant\nPlease Contact System Administrator." ;
        }
    }
    else
    {
        outboundMessage = "Error: Participant(s) Non-Existent!" ;
    }
}

void Connection::getAllQuestionnaires()
{
    SQLMessaging sqlMessaging ;

    /*
     * Set Header
     */
    outboundHeader = "ret*Ques" ;

    /*
     * Set Message
     */
    //Get User Info

    std::vector<Questionnaire> questionnaires ;
    questionnaires = sqlMessaging.getAllQuestionnaires() ;

    //Serialize Questionnaire Info
    {
        std::ostringstream archiveStream ;
        boost::archive::text_oarchive archive(archiveStream) ;
        archive << BOOST_SERIALIZATION_NVP(questionnaires) ;

        //Set Outbound Message to Serialized Info
        this->outboundMessage = archiveStream.str() ;
    }


}

void Connection::addQuestionnaire()
{
    //Deserialize Participant
    Questionnaire questionnaire ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> questionnaire ;
    }

    //Outbound Header remains the same regardless of outcome
    outboundHeader = "retQues " ;

    SQLMessaging sqlMessaging ;

    //If DOESN'T Exist
    if (!sqlMessaging.checkIfQuestionnaireExists(questionnaire))
    {
        //Message to Reply IF Added
        if (sqlMessaging.addQuestionnaire(questionnaire))
        {
            outboundHeader = "updMsg  " ;
            outboundMessage = "Questionnaire" ;
        }
        else
        {
            outboundMessage = "Error: Couldn't Add Questionnaire Contact System Administrator." ;
        }
    }
    else
    {
        outboundMessage = "Error: Questionnaire Already Exists!" ;
    }
}

void Connection::deleteVectorOfQuestionnaires()
{
    //Deserialize Participants
    std::vector<Questionnaire> questionnairesToBeDeleted ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> BOOST_SERIALIZATION_NVP(questionnairesToBeDeleted) ;
    }

    //Outbound Header remains the same regardless of outcome
    outboundHeader = "retMsg  " ;

    SQLMessaging sqlMessaging ;

    //If All Questionnaires Exist
    if (sqlMessaging.checkIfQuestionnairesExist(questionnairesToBeDeleted))
    {
        //Message to Reply IF All Deleted
        if (sqlMessaging.deleteVectorOfQuestionnaires(questionnairesToBeDeleted))
        {
            outboundHeader = "updMsg  " ;
            outboundMessage = "Questionnaire" ;
        }
        else
        {
            outboundMessage = "Error: Couldn't Delete Questionnaire(s)\nPlease Contact System Administrator." ;
        }
    }
    else
    {
        outboundMessage = "Error: Questionnaire(s) Non-Existent!" ;
    }
}

void Connection::editQuestionnaire()
{
    //Deserialize Questionnaire
    Questionnaire questionnaireToBeEdited ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive & questionnaireToBeEdited ;
    }

    //Outbound Header remains the same regardless of outcome
    outboundHeader = "retMsg  " ;

    SQLMessaging sqlMessaging ;

    //If All APLs Exist
    if (sqlMessaging.checkIfQuestionnaireExists(questionnaireToBeEdited))
    {
        //Message to Reply IF All Deleted
        if (sqlMessaging.editQuestionnaire(questionnaireToBeEdited))
        {
            outboundHeader = "updMsg  " ;
            outboundMessage = "Questionnaire" ;
        }
        else
        {
            outboundMessage = "Error: Couldn't Edit Questionnaire\nPlease Contact System Administrator." ;
        }
    }
    else
    {
        outboundMessage = "Error: Questionnaire(s) Non-Existent!" ;
    }
}
