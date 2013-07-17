#ifndef SQLMESSAGING_H
#define SQLMESSAGING_H

#include <QObject>
#include <QString>
#include <QDebug>

/*
 * SQL Messaging
 */
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <string>
#include <vector>
#include <algorithm>

#include "Login.h"
#include "User.h"
#include "Person.h"
#include "Participant.h"
#include "AccessPermissionList.h"
#include "Questionnaire.h"
#include "Question.h"

class SQLMessaging : public QObject
{
    Q_OBJECT
public:
    explicit SQLMessaging(QObject *parent = 0);

    void buildMessage() ;
    void sendMessage() ;

    bool checkLoginCredentials(std::string qusername, std::string password) ;

    User getUserFromUsername(std::string username) ;
    std::vector<User> getAllUsers() ;
    bool checkIfUserExists(User user) ;
    bool checkIfUsersExist(std::vector<User> users) ;
    bool addUser(User user) ;
    bool deleteVectorOfUsers(std::vector<User> users) ;
    bool editUser(User user) ;

    std::vector<AccessPermissionList> getAllAccessPermissionLists() ;
    bool checkIfAccessPermissionListExists(AccessPermissionList apl) ;
    bool checkIfAccessPermissionListsExist(std::vector<AccessPermissionList> apls) ;
    bool addAccessPermissionList(AccessPermissionList apl) ;
    bool deleteVectorOfAccessPermissionLists(std::vector<AccessPermissionList> apls) ;
    bool editAccessPermissionList(AccessPermissionList apl) ;

    std::vector<Participant> getAllParticipants() ;
    bool checkIfParticipantExists(Participant participant) ;
    bool checkIfParticipantsExist(std::vector<Participant> participants) ;
    bool addParticipant(Participant participant) ;
    bool deleteVectorOfParticipants(std::vector<Participant> participants) ;
    bool editParticipant(Participant participant) ;

    std::vector<Questionnaire> getAllQuestionnaires() ;
    bool checkIfQuestionnaireExists(Questionnaire questionnaire) ;
    bool checkIfQuestionnairesExist(std::vector<Questionnaire> questionnaires) ;
    bool addQuestionnaire(Questionnaire questionnaire) ;
    bool deleteVectorOfQuestionnaires(std::vector<Questionnaire> questionnaires) ;
    bool editQuestionnaire(Questionnaire questionnaire) ;

signals:
    
public slots:

private:
    QSqlDatabase db ;
    QString HOST ;
    QString DATABASE_NAME ;

    void setDatabase() ;

    std::string trimString(std::string trim) ;
};

#endif // SQLMESSAGING_H
