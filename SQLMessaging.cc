#include "SQLMessaging.h"

SQLMessaging::SQLMessaging(QObject *parent) :
    QObject(parent)
{
    db = QSqlDatabase::addDatabase("QODBC") ;
    HOST = "LOCALHOST\\SQLEXPRESS" ;
    DATABASE_NAME = "UCL Data Management" ;

    setDatabase() ;
}

void SQLMessaging::buildMessage()
{

}

void SQLMessaging::sendMessage()
{

}

void SQLMessaging::setDatabase()
{
    this->db.setHostName(HOST) ; //"LOCALHOST\\SQLEXPRESS"
    this->db.setDatabaseName(DATABASE_NAME) ; //"UCL Data Management"
}

std::string SQLMessaging::trimString(std::string trim)
{
    std::string WHITESPACE (" \t\f\v\n\r") ;

    unsigned found = trim.find_last_not_of(WHITESPACE);

    if (found!=std::string::npos)
    {
        trim.erase(found+1);
    }
    else
    {
        trim.clear();
    }

    return trim ;
}

bool SQLMessaging::checkLoginCredentials(std::string username, std::string password)
{
    if(this->db.open())
    {
        QSqlQuery query ;

        if (query.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[Users]"))
        {
            while (query.next())
            {
                std::string queryUsername = query.value(0).toString().toStdString() ;
                queryUsername = trimString(queryUsername) ;

                if (username == queryUsername)
                {
                    std::string queryPassword = query.value(1).toString().toStdString() ;
                    queryPassword = trimString(queryPassword) ;

                    if (password == queryPassword)
                    {
                        return true ;
                    }
                }
            }
        }

        this->db.close() ;
    }
    else
    {
        qDebug() << "Error: " << this->db.lastError().text() ;
    }

    return false ;
}

User SQLMessaging::getUserFromUsername(std::string username)
{
    User user ;

    if(db.open())
    {
        QSqlQuery queryUser ;

        if (queryUser.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[Users]"))
        {
            while (queryUser.next())
            {
                std::string queryUsername = queryUser.value(0).toString().toStdString() ;
                queryUsername = trimString(queryUsername) ;

                if (username == queryUsername)
                {
                    /*
                     * Set User's Values
                     */
                    user.setUserId(queryUser.value(0).toString().toStdString()) ;
                    user.setPassword(queryUser.value(1).toString().toStdString()) ;
                    user.setForename(queryUser.value(2).toString().toStdString()) ;
                    user.setSurname(queryUser.value(3).toString().toStdString()) ;
                    user.setDepartment(queryUser.value(4).toString().toStdString()) ;
                    user.setRole(queryUser.value(5).toString().toStdString()) ;

                    /*
                     * Get AccessPermissionList
                     */
                    QString aplTitle = queryUser.value(6).toString() ;
                    AccessPermissionList apl ;
                    QSqlQuery queryAPL ;

                    if (queryAPL.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[AccessPermissionLists]"))
                    {
                        bool foundAPL = false ;

                        while (queryAPL.next() && foundAPL == false)
                        {
                            std::string queryAplTitle = queryAPL.value(0).toString().toStdString() ;
                            queryAplTitle = trimString(queryAplTitle) ;

                            if (trimString(aplTitle.toStdString()) == trimString(queryAplTitle))
                            {
                                std::string list ;

                                //Set Name
                                apl.setName(trimString(queryAPL.value(0).toString().toStdString()));

                                for (int i = 1; i <= 23; i++)
                                {
                                    if (queryAPL.value(i) == true)
                                    {
                                        list.append("1") ;
                                    }
                                    else
                                    {
                                        list.append("0") ;
                                    }
                                }

                                apl.simpleDeserialize(list) ;
                                foundAPL = true ;
                            }
                        }
                    }

                    //Add APL to User's Values
                    user.setAccessPermissionList(apl) ;

                    //Set isAccountActive
                    if (queryUser.value(7) == true)
                    {
                        user.setIsAccountActive(true) ;
                    }
                    else
                    {
                        user.setIsAccountActive(false) ;
                    }
                }
            }
        }

        db.close() ;
    }
    else
    {
        qDebug() << "Error: " << db.lastError().text() ;
    }

    return user ;
}

std::vector<User> SQLMessaging::getAllUsers()
{
    //Vector Array of Users to Return
    std::vector<User> users ;

    if(db.open())
    {
        QSqlQuery queryUsers ;

        if (queryUsers.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[Users]"))
        {
            while (queryUsers.next())
            {
                User user ;
                /*
                 * Set User's Values
                 */
                user.setUserId(queryUsers.value(0).toString().toStdString()) ;
                user.setPassword(queryUsers.value(1).toString().toStdString()) ;
                user.setForename(queryUsers.value(2).toString().toStdString()) ;
                user.setSurname(queryUsers.value(3).toString().toStdString()) ;
                user.setDepartment(queryUsers.value(4).toString().toStdString()) ;
                user.setRole(queryUsers.value(5).toString().toStdString()) ;

                /*
                 * Get AccessPermissionList
                 */
                QString aplTitle = queryUsers.value(6).toString() ;
                AccessPermissionList apl ;
                QSqlQuery queryAPL ;

                if (queryAPL.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[AccessPermissionLists]"))
                {
                    bool foundAPL = false ;

                    while (queryAPL.next() && foundAPL == false)
                    {
                        std::string queryAplTitle = queryAPL.value(0).toString().toStdString() ;
                        queryAplTitle = trimString(queryAplTitle) ;

                        if (trimString(aplTitle.toStdString()) == trimString(queryAplTitle))
                        {
                            std::string aplList ;

                            //Set Name
                            apl.setName(trimString(queryAPL.value(0).toString().toStdString())) ;

                            for (int i = 1; i <= 23; i++)
                            {
                                if (queryAPL.value(i) == true)
                                {
                                    aplList.append("1") ;
                                }
                                else
                                {
                                    aplList.append("0") ;
                                }
                            }

                            apl.simpleDeserialize(aplList) ;
                            foundAPL = true ;
                        }
                    }
                }

                //Add APL to User's Values
                user.setAccessPermissionList(apl) ;

                //Set isAccountActive
                if (queryUsers.value(7) == true)
                {
                    user.setIsAccountActive(true) ;
                }
                else
                {
                    user.setIsAccountActive(false) ;
                }

                //Add User to Vector<Users>
                users.push_back(user) ;
            }
        }

        db.close() ;
    }
    else
    {
        qDebug() << "Error: " << db.lastError().text() ;
    }

    return users ;
}

bool SQLMessaging::checkIfUserExists(User user)
{
    if(db.open())
    {
        QSqlQuery queryUserExists ;

        if (queryUserExists.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[Users]"))
        {
            while (queryUserExists.next())
            {
                if (trimString(queryUserExists.value(0).toString().toStdString()) == trimString(user.getUserId()))
                {
                    db.close() ;
                    return true ;
                }
            }
        }

        db.close() ;
    }
    else
    {
        qDebug() << "Error: " << db.lastError().text() ;
    }

    return false ;
}

bool SQLMessaging::checkIfUsersExist(std::vector<User> users)
{
    User user ;
    bool allUsersMatch = true ;
    bool singleUserfound ;

    for (unsigned i = 0; i < users.size(); i++)
    {
        if(db.open())
        {
            QSqlQuery queryUsers ;

            if (queryUsers.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[Users]"))
            {
                user = users.at(i) ;
                singleUserfound = false ;

                while (queryUsers.next())
                {
                    if (trimString(queryUsers.value(0).toString().toStdString()) == trimString(user.getUserId()))
                    {
                        singleUserfound = true ;
                    }
                }

                if (singleUserfound && allUsersMatch)
                {
                    allUsersMatch = true ;
                }
                else
                {
                    allUsersMatch = false ;
                }
            }

            db.close() ;
        }
        else
        {
            qDebug() << "Error: " << db.lastError().text() ;
        }
    }

    return allUsersMatch ;
}

bool SQLMessaging::addUser(User user)
{
    if(db.open())
    {
        QString insertString = "INSERT INTO [dbUCLDataManagement].[dbo].[Users]" ;
        insertString.append("([userID],[password],[forename],[surname],[department],[role],[APL],[isAccountActive])") ;
        insertString.append("VALUES (") ;

        insertString.append("'" + QString::fromStdString(user.getUserId()) + "',") ;
        insertString.append("'" + QString::fromStdString(user.getPassword()) + "',") ;
        insertString.append("'" + QString::fromStdString(user.getForename()) + "',") ;
        insertString.append("'" + QString::fromStdString(user.getSurname()) + "',") ;
        insertString.append("'" + QString::fromStdString(user.getDepartment()) + "',") ;
        insertString.append("'" + QString::fromStdString(user.getRole()) + "',") ;
        insertString.append("'" + QString::fromStdString(user.getAccessPermissionList().getName()) + "',") ;

        (user.getIsAccountActive()) ? insertString.append("'1')") : insertString.append("'0')") ;

        QSqlQuery query_in ;
        query_in.prepare(insertString) ;

        if (query_in.exec())
        {
            db.close() ;
            return true ;
        }
    }

    return false ;
}

bool SQLMessaging::deleteVectorOfUsers(std::vector<User> users)
{
    if(db.open())
    {
        bool recordDeleted ;
        std::string insertString ;
        QSqlQuery queryDelete ;

        User user ;

        for (unsigned i = 0; i < users.size(); i++)
        {
            recordDeleted = false ;

            user = users.at(i) ;

            insertString = "DELETE FROM [dbUCLDataManagement].[dbo].[Users] WHERE userID='" ;
            insertString.append(user.getUserId()) ;
            insertString.append("'") ;

            queryDelete.prepare(QString::fromStdString(insertString)) ;

            if (queryDelete.exec())
            {
                recordDeleted = true ;
            }

            if (!recordDeleted)
            {
                return false ;
            }
        }
    }

    return true ;
}

bool SQLMessaging::editUser(User user)
{
    std::vector<User> users ;
    users.push_back(user) ;
    deleteVectorOfUsers(users) ;

    addUser(user) ;

    return true ;
}

std::vector<AccessPermissionList> SQLMessaging::getAllAccessPermissionLists()
{
    //Vector Array of Users to Return
    std::vector<AccessPermissionList> apls ;

    if(db.open())
    {
        QSqlQuery queryAPLs ;

        if (queryAPLs.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[AccessPermissionLists]"))
        {
            while (queryAPLs.next())
            {
                AccessPermissionList apl ;

                /*
                 * Get AccessPermissionLists
                 */
                apl.setName(trimString(queryAPLs.value(0).toString().toStdString())) ;

                std::string aplList ;
                for (int i = 1; i <= 23; i++)
                {
                    if (queryAPLs.value(i) == true)
                    {
                        aplList.append("1") ;
                    }
                    else
                    {
                        aplList.append("0") ;
                    }
                }

                apl.simpleDeserialize(aplList) ;

                //Add User to Vector<Users>
                apls.push_back(apl) ;
            }
        }

        db.close() ;
    }
    else
    {
        qDebug() << "Error: " << db.lastError().text() ;
    }

    return apls ;
}

bool SQLMessaging::checkIfAccessPermissionListExists(AccessPermissionList apl)
{
    if(db.open())
    {
        QSqlQuery queryAPL ;

        if (queryAPL.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[AccessPermissionLists]"))
        {
            while (queryAPL.next())
            {
                if (trimString(queryAPL.value(0).toString().toStdString()) == trimString(apl.getName()))
                {
                    return true ;
                }
            }
        }

        db.close() ;
    }
    else
    {
        qDebug() << "Error: " << db.lastError().text() ;
    }

    return false ;
}
bool SQLMessaging::checkIfAccessPermissionListsExist(std::vector<AccessPermissionList> apls)
{
    AccessPermissionList apl ;
    bool allAPLsMatch = true ;
    bool singleAPLfound ;

    for (unsigned i = 0; i < apls.size(); i++)
    {
        if(db.open())
        {
            QSqlQuery queryAPLs ;

            if (queryAPLs.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[AccessPermissionLists]"))
            {
                apl = apls.at(i) ;
                singleAPLfound = false ;

                while (queryAPLs.next())
                {
                    if (trimString(queryAPLs.value(0).toString().toStdString()) == trimString(apl.getName()))
                    {
                        singleAPLfound = true ;
                    }
                }

                if (singleAPLfound && allAPLsMatch)
                {
                    allAPLsMatch = true ;
                }
                else
                {
                    allAPLsMatch = false ;
                }
            }

            db.close() ;
        }
        else
        {
            qDebug() << "Error: " << db.lastError().text() ;
        }
    }

    return allAPLsMatch ;
}

bool SQLMessaging::addAccessPermissionList(AccessPermissionList apl)
{
    if(db.open())
    {
        QString insertString = "INSERT INTO [dbUCLDataManagement].[dbo].[AccessPermissionLists]" ;
        insertString.append("([APL],[canViewResearchTopics],[canAddResearchTopics],[canRemoveResearchTopics],[canEditResearchTopics],[canViewParticipants],[canAddParticipants],[canRemoveParticipants],[canEditParticipants],[canViewQuestionnaires],[canAddQuestionnaires],[canRemoveQuestionnaires],[canEditQuestionnaires],[canViewUsers],[canAddUsers],[canRemoveUsers],[canEditUsers],[canViewSettings],[canEditSettings],[canSearchDatabase],[canBackUp],[canCollaborate],[canExport],[isAccountActive])") ;
        insertString.append("VALUES (") ;

        insertString.append("'" + QString::fromStdString(apl.getName()) + "',") ;

        (apl.getCanViewResearchTopics()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanAddResearchTopics()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanRemoveResearchTopics()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanEditResearchTopics()) ? insertString.append("'1',") : insertString.append("'0',") ;

        (apl.getCanViewParticipants()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanAddParticipants()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanRemoveParticipants()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanEditParticipants()) ? insertString.append("'1',") : insertString.append("'0',") ;

        (apl.getCanViewQuestionnaires()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanAddQuestionnaires()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanRemoveQuestionnaires()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanEditQuestionnaires()) ? insertString.append("'1',") : insertString.append("'0',") ;

        (apl.getCanViewUsers()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanAddUsers()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanRemoveUsers()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanEditUsers()) ? insertString.append("'1',") : insertString.append("'0',") ;

        (apl.getCanViewSettings()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanEditSettings()) ? insertString.append("'1',") : insertString.append("'0',") ;

        (apl.getCanSearchDatabase()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanBackUp()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanCollaborate()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getCanExport()) ? insertString.append("'1',") : insertString.append("'0',") ;
        (apl.getIsAccountActive()) ? insertString.append("'1')") : insertString.append("'0')") ;

        QSqlQuery query_in ;
        query_in.prepare(insertString) ;

        if (query_in.exec())
        {
            return true ;
        }
    }

    return false ;
}

bool SQLMessaging::deleteVectorOfAccessPermissionLists(std::vector<AccessPermissionList> apls)
{
    if(db.open())
    {
        bool recordDeleted ;

        std::string insertString ;

        QSqlQuery queryDelete ;

        AccessPermissionList apl ;

        for (unsigned i = 0; i < apls.size(); i++)
        {
            qDebug() << i ;
            recordDeleted = false ;

            apl = apls.at(i) ;

            insertString = "DELETE FROM [dbUCLDataManagement].[dbo].[AccessPermissionLists] WHERE APL='" ;
            insertString.append(apl.getName()) ;
            insertString.append("'") ;

            queryDelete.prepare(QString::fromStdString(insertString)) ;

            if (queryDelete.exec())
            {
                recordDeleted = true ;
            }

            if (!recordDeleted)
            {
                return false ;
            }
        }
    }

    return true ;
}

bool SQLMessaging::editAccessPermissionList(AccessPermissionList apl)
{
    std::vector<AccessPermissionList> apls ;
    apls.push_back(apl) ;
    deleteVectorOfAccessPermissionLists(apls) ;

    addAccessPermissionList(apl) ;

    return true ;
}

std::vector<Participant> SQLMessaging::getAllParticipants()
{
    //Vector Array of Users to Return
    std::vector<Participant> participants ;

    if(db.open())
    {
        QSqlQuery queryParticipants ;

        if (queryParticipants.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[Participants]"))
        {
            while (queryParticipants.next())
            {
                Participant participant ;

                /*
                 * Get Participants
                 */
                participant.setParticipantID(trimString(queryParticipants.value(0).toString().toStdString())) ;
                participant.setForename((trimString(queryParticipants.value(1).toString().toStdString()))) ;
                participant.setSurname((trimString(queryParticipants.value(2).toString().toStdString()))) ;
                participant.setDateOfBirth((trimString(queryParticipants.value(3).toString().toStdString()))) ;

                if (queryParticipants.value(4) == true)
                {
                    participant.setSex(true) ;
                }
                else
                {
                    participant.setSex(false) ;
                }

                participant.setGuardianForename((trimString(queryParticipants.value(5).toString().toStdString()))) ;
                participant.setGuardianSurname((trimString(queryParticipants.value(6).toString().toStdString()))) ;
                participant.setContactHome((trimString(queryParticipants.value(7).toString().toStdString()))) ;
                participant.setContactWork((trimString(queryParticipants.value(8).toString().toStdString()))) ;
                participant.setContactMobile((trimString(queryParticipants.value(9).toString().toStdString()))) ;
                participant.setAddressLine1((trimString(queryParticipants.value(10).toString().toStdString()))) ;
                participant.setAddressLine2((trimString(queryParticipants.value(11).toString().toStdString()))) ;
                participant.setAddressLine3((trimString(queryParticipants.value(12).toString().toStdString()))) ;
                participant.setAddressLine4((trimString(queryParticipants.value(13).toString().toStdString()))) ;
                participant.setAddressPostCode((trimString(queryParticipants.value(14).toString().toStdString()))) ;

                //Add Participant to Vector<Participant>
                participants.push_back(participant) ;
            }
        }

        db.close() ;
    }
    else
    {
        qDebug() << "Error: " << db.lastError().text() ;
    }

    return participants ;
}

bool SQLMessaging::checkIfParticipantExists(Participant participant)
{
    if(db.open())
    {
        QSqlQuery queryParticipant ;

        if (queryParticipant.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[Participants]"))
        {
            while (queryParticipant.next())
            {
                if (trimString(queryParticipant.value(0).toString().toStdString()) == trimString(participant.getParticipantID()))
                {
                    return true ;
                }
            }
        }

        db.close() ;
    }
    else
    {
        qDebug() << "Error: " << db.lastError().text() ;
    }

    return false ;
}

bool SQLMessaging::checkIfParticipantsExist(std::vector<Participant> participants)
{
    Participant participant ;
    bool singleParticipantFound ;

    for (unsigned i = 0; i < participants.size(); i++)
    {
        if(db.open())
        {
            QSqlQuery queryParticipants ;

            if (queryParticipants.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[Participants]"))
            {
                participant = participants.at(i) ;
                singleParticipantFound = false ;

                while (queryParticipants.next())
                {
                    if (trimString(queryParticipants.value(0).toString().toStdString()) == trimString(participant.getParticipantID()))
                    {
                        singleParticipantFound = true ;
                    }
                }

                if (!singleParticipantFound)
                {
                    return false ;
                }
            }

            db.close() ;
        }
        else
        {
            qDebug() << "Error: " << db.lastError().text() ;
        }
    }

    return true ;
}

bool SQLMessaging::addParticipant(Participant participant)
{
    if(db.open())
    {
        QString insertString = "INSERT INTO [dbUCLDataManagement].[dbo].[Participants]" ;
        insertString.append("([ParticipantID],[Forename],[Surname],[DateOfBirth],[Sex],[GuardianForename],[GuardianSurname],[ContactHome],[ContactWork],[ContactMobile],[AddressLine1],[AddressLine2],[AddressLine3],[AddressLine4],[AddressPostCode])") ;
        insertString.append("VALUES (") ;

        insertString.append("'" + QString::fromStdString(participant.getParticipantID()) + "',") ;
        insertString.append("'" + QString::fromStdString(participant.getForename()) + "',") ;
        insertString.append("'" + QString::fromStdString(participant.getSurname()) + "',") ;
        insertString.append("'" + QString::fromStdString(participant.getDateOfBirthAsString()) + "',") ;
        if (participant.getSex())
        {
            insertString.append("'1',") ;
        }
        else
        {
            insertString.append("'1',") ;
        }
        insertString.append("'" + QString::fromStdString(participant.getGuardianForename()) + "',") ;
        insertString.append("'" + QString::fromStdString(participant.getGuardianSurname()) + "',") ;
        insertString.append("'" + QString::fromStdString(participant.getContactHome()) + "',") ;
        insertString.append("'" + QString::fromStdString(participant.getContactWork()) + "',") ;
        insertString.append("'" + QString::fromStdString(participant.getContactMobile()) + "',") ;
        insertString.append("'" + QString::fromStdString(participant.getAddressLine1()) + "',") ;
        insertString.append("'" + QString::fromStdString(participant.getAddressLine2()) + "',") ;
        insertString.append("'" + QString::fromStdString(participant.getAddressLine3()) + "',") ;
        insertString.append("'" + QString::fromStdString(participant.getAddressLine4()) + "',") ;
        insertString.append("'" + QString::fromStdString(participant.getAddresssPostCode()) + "')") ;

        QSqlQuery query_in ;
        query_in.prepare(insertString) ;

        if (query_in.exec())
        {
            return true ;
        }
    }

    return false ;
}

bool SQLMessaging::deleteVectorOfParticipants(std::vector<Participant> participants)
{
    if(db.open())
    {
        bool recordDeleted ;

        std::string insertString ;

        QSqlQuery queryDelete ;

        Participant participant ;

        for (unsigned i = 0; i < participants.size(); i++)
        {
            qDebug() << i ;
            recordDeleted = false ;

            participant = participants.at(i) ;

            insertString = "DELETE FROM [dbUCLDataManagement].[dbo].[Participants] WHERE ParticipantID='" ;
            insertString.append(participant.getParticipantID()) ;
            insertString.append("'") ;

            queryDelete.prepare(QString::fromStdString(insertString)) ;

            if (queryDelete.exec())
            {
                recordDeleted = true ;
            }

            if (!recordDeleted)
            {
                return false ;
            }
        }
    }

    return true ;
}

bool SQLMessaging::editParticipant(Participant participant)
{
    std::vector<Participant> participants ;
    participants.push_back(participant) ;
    deleteVectorOfParticipants(participants) ;

    addParticipant(participant) ;

    return true ;
}

std::vector<Questionnaire> SQLMessaging::getAllQuestionnaires()
{
    //Vector of Questionnaires to return
    std::vector<Questionnaire> questionnairesToReturn ;
    db.close() ;
    if(db.open())
    {
        QSqlQuery queryQuestionnaires ;

        if (queryQuestionnaires.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[Questionnaires]"))
        {
            while (queryQuestionnaires.next())
            {
                /*
                 * Set Questionnaire
                 * ID & Note
                 */
                Questionnaire questionnaire ;
                questionnaire.setQuestionnaireID(trimString(queryQuestionnaires.value(0).toString().toStdString())) ;
                questionnaire.setNote(trimString(queryQuestionnaires.value(1).toString().toStdString())) ;

                /*
                 * Get All Questions
                 */
                std::vector<Question *> questions ;

                /*
                 * Get All Boolean Questions
                 */
                QString queryBooleanQuestionsString = "SELECT ID, QUESTION, QNUMBER, ANSWER FROM [dbUCLDataManagement].[dbo].[QuestionsOfTypeBoolean] WHERE [dbUCLDataManagement].[dbo].[QuestionsOfTypeBoolean].QUESTIONNAIRE_ID = " ;
                queryBooleanQuestionsString.append("'" + QString::fromStdString(questionnaire.getQuestionnaireID()) + "' ;") ;

                QSqlQuery queryBooleanQuestions ;
                queryBooleanQuestions.prepare(queryBooleanQuestionsString) ;

                if (queryBooleanQuestions.exec())
                {

                    while (queryBooleanQuestions.next())
                    {
                        BooleanQuestion *booleanQuestion = new BooleanQuestion() ;

                        booleanQuestion->setQuestionID(trimString(queryBooleanQuestions.value(0).toString().toStdString())) ;
                        booleanQuestion->setQuestion(trimString(queryBooleanQuestions.value(1).toString().toStdString())) ;
                        booleanQuestion->setQNumber(queryBooleanQuestions.value(2).toInt()) ;
                        booleanQuestion->setAnswer(queryBooleanQuestions.value(3).toBool()) ;

                        questions.push_back(booleanQuestion) ;
                    }
                }

                /*
                 * Get All Number Questions
                 */
                QString queryNumberQuestionsString = "SELECT ID, QUESTION, QNUMBER, ANSWER, BASE, RANGE FROM [dbUCLDataManagement].[dbo].[QuestionsOfTypeNumber] WHERE [dbUCLDataManagement].[dbo].[QuestionsOfTypeNumber].QUESTIONNAIRE_ID = " ;
                queryNumberQuestionsString.append("'" + QString::fromStdString(questionnaire.getQuestionnaireID()) + "' ;") ;

                QSqlQuery queryNumberQuestions ;
                queryNumberQuestions.prepare(queryNumberQuestionsString) ;

                if (queryNumberQuestions.exec())
                {

                    while (queryNumberQuestions.next())
                    {
                        NumberQuestion *numberQuestion = new NumberQuestion() ;

                        numberQuestion->setQuestionID(trimString(queryNumberQuestions.value(0).toString().toStdString())) ;
                        numberQuestion->setQuestion(trimString(queryNumberQuestions.value(1).toString().toStdString())) ;
                        numberQuestion->setQNumber(queryNumberQuestions.value(2).toInt()) ;
                        numberQuestion->setAnswer(queryNumberQuestions.value(3).toInt()) ;
                        numberQuestion->setBase(queryNumberQuestions.value(4).toInt()) ;
                        numberQuestion->setRange(queryNumberQuestions.value(5).toInt()) ;

                        questions.push_back(numberQuestion) ;
                    }
                }

                /*
                 * Get All Text Questions
                 */
                QString queryTextQuestionsString = "SELECT ID, QUESTION, QNUMBER, ANSWER FROM [dbUCLDataManagement].[dbo].[QuestionsOfTypeText] WHERE [dbUCLDataManagement].[dbo].[QuestionsOfTypeText].QUESTIONNAIRE_ID = " ;
                queryTextQuestionsString.append("'" + QString::fromStdString(questionnaire.getQuestionnaireID()) + "' ;") ;

                QSqlQuery queryTextQuestions ;
                queryTextQuestions.prepare(queryTextQuestionsString) ;

                if (queryTextQuestions.exec())
                {

                    while (queryTextQuestions.next())
                    {
                        TextQuestion *textQuestion = new TextQuestion() ;

                        textQuestion->setQuestionID(trimString(queryTextQuestions.value(0).toString().toStdString())) ;
                        textQuestion->setQuestion(trimString(queryTextQuestions.value(1).toString().toStdString())) ;
                        textQuestion->setQNumber(queryTextQuestions.value(2).toInt()) ;
                        textQuestion->setAnswer(queryTextQuestions.value(3).toString().toStdString()) ;

                        questions.push_back(textQuestion) ;
                    }
                }

                /*
                 * Add Questions to Questionnaire
                 */
                questionnaire.setQuestions(questions) ;

                /*
                 * Sort Questions Into Correct Order
                 */
                questionnaire.sort() ;

                /*
                 * Add Questionnaire to Questionnaire Array
                 */
                questionnairesToReturn.push_back(questionnaire) ;
            }
        }
    }

    return questionnairesToReturn ;
}

bool SQLMessaging::checkIfQuestionnaireExists(Questionnaire questionnaire)
{
    if(db.open())
    {
        QSqlQuery queryQuestionnaire ;

        if (queryQuestionnaire.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[Questionnaires]"))
        {
            while (queryQuestionnaire.next())
            {
                if (trimString(queryQuestionnaire.value(0).toString().toStdString()) == trimString(questionnaire.getQuestionnaireID()))
                {
                    return true ;
                }
            }
        }

        db.close() ;
    }
    else
    {
        qDebug() << "Error: " << db.lastError().text() ;
    }

    return false ;
}

bool SQLMessaging::checkIfQuestionnairesExist(std::vector<Questionnaire> questionnaires)
{
    Questionnaire questionnaire ;
    bool singleQuestionnaireFound ;

    for (unsigned i = 0; i < questionnaires.size(); i++)
    {
        if(db.open())
        {
            QSqlQuery queryQuestionnaires ;

            if (queryQuestionnaires.exec("SELECT * FROM [dbUCLDataManagement].[dbo].[Questionnaires]"))
            {
                questionnaire = questionnaires.at(i) ;
                singleQuestionnaireFound = false ;

                while (queryQuestionnaires.next())
                {
                    if (trimString(queryQuestionnaires.value(0).toString().toStdString()) == trimString(questionnaire.getQuestionnaireID()))
                    {
                        singleQuestionnaireFound = true ;
                    }
                }

                if (!singleQuestionnaireFound)
                {
                    return false ;
                }
            }

            db.close() ;
        }
        else
        {
            qDebug() << "Error: " << db.lastError().text() ;
        }
    }

    return true ;
}

bool SQLMessaging::addQuestionnaire(Questionnaire questionnaire)
{
    bool successful = true ;

    if(db.open())
    {
        /*
         * Add Questionnaire Details to Questionnaire Table
         */
        QString insertQuestionnaireString = "INSERT INTO [dbUCLDataManagement].[dbo].[Questionnaires]" ;
        insertQuestionnaireString.append("([ID], [NOTE]) ") ;
        insertQuestionnaireString.append("VALUES (") ;

        insertQuestionnaireString.append("'" + QString::fromStdString(questionnaire.getQuestionnaireID()) + "',") ;
        insertQuestionnaireString.append("'" + QString::fromStdString(questionnaire.getNote()) + "' ) ;") ;

        QSqlQuery queryInsertQuestionnaire ;
        queryInsertQuestionnaire.prepare(insertQuestionnaireString) ;

        if (queryInsertQuestionnaire.exec())
        {

        }
        else
        {
            successful = false ;
        }

        /*
         * Add Question(s) Details to Respective Table(s)
         */
        for (int i = 0; i < questionnaire.getQuestionCount(); i++)
        {
            //Ensure Question Number is Set
            questionnaire.getQuestions().at(i)->setQNumber(i) ;

            if (dynamic_cast<BooleanQuestion *>(questionnaire.getQuestions().at(i)) != nullptr)
            {
                BooleanQuestion *booleanQuestion = dynamic_cast<BooleanQuestion *>(questionnaire.getQuestions().at(i)) ;

                /*
                 * Add Boolean Question(s) Details to ofTypeBoolean Table
                 */
                QString insertBooleanQString = "INSERT INTO [dbUCLDataManagement].[dbo].[QuestionsOfTypeBoolean]" ;
                insertBooleanQString.append("([ID],[QUESTIONNAIRE_ID],[QUESTION],[QNUMBER],[ANSWER])") ;
                insertBooleanQString.append("VALUES (") ;
                insertBooleanQString.append("'" + QString::fromStdString(booleanQuestion->getQuestionID()) + "', ") ;
                insertBooleanQString.append("'" + QString::fromStdString(questionnaire.getQuestionnaireID()) + "', ") ;
                insertBooleanQString.append("'" + QString::fromStdString(booleanQuestion->getQuestion()) + "', ") ;
                insertBooleanQString.append("'" + QString::number(booleanQuestion->getQNumber()) + "', ") ;
                insertBooleanQString.append("'") ;
                insertBooleanQString.append(booleanQuestion->getAnswer() == 1 ? "1" : "0") ;
                insertBooleanQString.append("') ;") ;

                QSqlQuery queryInsertBooleanQ ;
                queryInsertBooleanQ.prepare(insertBooleanQString) ;

                if (queryInsertBooleanQ.exec())
                {

                }
                else
                {
                    successful = false ;
                }
            }
            else if (dynamic_cast<NumberQuestion *>(questionnaire.getQuestions().at(i)) != NULL)
            {
                NumberQuestion *numberQuestion = dynamic_cast<NumberQuestion *>(questionnaire.getQuestions().at(i)) ;

                /*
                 * Add Number Question(s) Details to ofTypeNumber Table
                 */
                QString insertNumberQString = "INSERT INTO [dbUCLDataManagement].[dbo].[QuestionsOfTypeNumber]" ;
                insertNumberQString.append("([ID],[QUESTIONNAIRE_ID],[QUESTION],[QNUMBER],[ANSWER],[BASE],[RANGE])") ;
                insertNumberQString.append("VALUES (") ;
                insertNumberQString.append("'" + QString::fromStdString(numberQuestion->getQuestionID()) + "', ") ;
                insertNumberQString.append("'" + QString::fromStdString(questionnaire.getQuestionnaireID()) + "', ") ;
                insertNumberQString.append("'" + QString::fromStdString(numberQuestion->getQuestion()) + "', ") ;
                insertNumberQString.append("'" + QString::number(numberQuestion->getQNumber()) + "', ") ;
                insertNumberQString.append("'" + QString::number(numberQuestion->getAnswer()) + "', ") ;
                insertNumberQString.append("'" + QString::number(numberQuestion->getBase()) + "', ") ;
                insertNumberQString.append("'" + QString::number(numberQuestion->getRange()) + "') ;") ;

                QSqlQuery queryInsertNumberQ ;
                queryInsertNumberQ.prepare(insertNumberQString) ;

                if (queryInsertNumberQ.exec())
                {

                }
                else
                {
                    successful = false ;
                }
            }
            else if (dynamic_cast<TextQuestion *>(questionnaire.getQuestions().at(i)) != NULL)
            {
                TextQuestion *textQuestion = dynamic_cast<TextQuestion *>(questionnaire.getQuestions().at(i)) ;

                /*
                 * Add Text Question(s) Details to ofTypeText Table
                 */
                QString insertTextQString = "INSERT INTO [dbUCLDataManagement].[dbo].[QuestionsOfTypeText]" ;
                insertTextQString.append("([ID],[QUESTIONNAIRE_ID],[QUESTION],[QNUMBER],[ANSWER])") ;
                insertTextQString.append("VALUES (") ;
                insertTextQString.append("'" + QString::fromStdString(textQuestion->getQuestionID()) + "', ") ;
                insertTextQString.append("'" + QString::fromStdString(questionnaire.getQuestionnaireID()) + "', ") ;
                insertTextQString.append("'" + QString::fromStdString(textQuestion->getQuestion()) + "', ") ;
                insertTextQString.append("'" + QString::number(textQuestion->getQNumber()) + "', ") ;
                insertTextQString.append("'" + QString::fromStdString(textQuestion->getAnswer()) + "') ;") ;

                QSqlQuery queryInsertTextQ ;
                queryInsertTextQ.prepare(insertTextQString) ;

                if (queryInsertTextQ.exec())
                {

                }
                else
                {
                    successful = false ;
                }
            }
        }
    }

    return successful ;
}

bool SQLMessaging::deleteVectorOfQuestionnaires(std::vector<Questionnaire> questionnaires)
{
    if(db.open())
    {
        QString deleteString ;
        QSqlQuery queryDeleteQuestionnaire ;
        QSqlQuery queryDeleteBooleanQuestions ;
        QSqlQuery queryDeleteNumberQuestions ;
        QSqlQuery queryDeleteTextQuestions ;

        for (unsigned i = 0; i < questionnaires.size(); i++)
        {
            /*
             * Delete Questionnaire from Questionnaire Table
             */
            deleteString = "DELETE FROM [dbUCLDataManagement].[dbo].[Questionnaires] WHERE ID='" ;
            deleteString.append(QString::fromStdString(questionnaires.at(i).getQuestionnaireID())) ;
            deleteString.append("'") ;

            queryDeleteQuestionnaire.prepare(deleteString) ;

            if (queryDeleteQuestionnaire.exec())
            {

            }
            else
            {
                return false ;
            }

            /*
             * Delete Boolean Question(s) from ofTypeBoolean Table
             */
            deleteString = "DELETE FROM [dbUCLDataManagement].[dbo].[QuestionsOfTypeBoolean] WHERE QUESTIONNAIRE_ID='" ;
            deleteString.append(QString::fromStdString(questionnaires.at(i).getQuestionnaireID())) ;
            deleteString.append("'") ;

            queryDeleteBooleanQuestions.prepare(deleteString) ;

            if (queryDeleteBooleanQuestions.exec())
            {

            }
            else
            {
                return false ;
            }

            /*
             * Delete Number Question(s) from ofTypeNumber Table
             */
            deleteString = "DELETE FROM [dbUCLDataManagement].[dbo].[QuestionsOfTypeNumber] WHERE QUESTIONNAIRE_ID='" ;
            deleteString.append(QString::fromStdString(questionnaires.at(i).getQuestionnaireID())) ;
            deleteString.append("'") ;

            queryDeleteNumberQuestions.prepare(deleteString) ;

            if (queryDeleteNumberQuestions.exec())
            {

            }
            else
            {
                return false ;
            }

            /*
             * Delete Text Question(s) from ofTypeText Table
             */
            deleteString = "DELETE FROM [dbUCLDataManagement].[dbo].[QuestionsOfTypeText] WHERE QUESTIONNAIRE_ID='" ;
            deleteString.append(QString::fromStdString(questionnaires.at(i).getQuestionnaireID())) ;
            deleteString.append("'") ;

            queryDeleteTextQuestions.prepare(deleteString) ;

            if (queryDeleteTextQuestions.exec())
            {

            }
            else
            {
                return false ;
            }
        }
    }

    return true ;
}

bool SQLMessaging::editQuestionnaire(Questionnaire questionnaire)
{
    std::vector<Questionnaire> questionnaires ;
    questionnaires.push_back(questionnaire) ;
    deleteVectorOfQuestionnaires(questionnaires) ;

    addQuestionnaire(questionnaire) ;

    return true ;
}
