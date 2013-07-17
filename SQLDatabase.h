#ifndef SQLDATABASE_H
#define SQLDATABASE_H

/*
 * C++ Classes
 */
#include <string>

/*
 * SQL Messaging
 */
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

class SQLDatabase
{
public:
    SQLDatabase();

    void initialiseSQLDatabase() ;

    void insertDummyDataForTesting() ;

private:
    QString HOST ;
    QString SYSTEM_DSN ;
    QString SCHEMA ;
    QString DATABASE_NAME ;

    QSqlDatabase DATABASE ;

    QString APL_TABLE ;
    QString USERS_TABLE ;
    QString PARTICIPANTS_TABLE ;
    QString QUESTIONNAIRES_TABLE ;
    QString QUESTION_BOOLEAN_TABLE ;
    QString QUESTION_NUMBER_TABLE ;
    QString QUESTION_TEXT_TABLE ;

    void createDatabase() ;

    void createTableForAccessPermissionLists() ;
    void createTableForUsers() ;
    void createTableForParticipants() ;
    void createTableForQuestionnaires() ;
    void createTableForQuestionsOfBooleanType() ;
    void createTableForQuestionsOfNumberType() ;
    void createTableForQuestionsOfTextType() ;

    void insertSuperUser() ;

    void backUpToFile() ;
    void restoreFromBackUpFile() ;
};

#endif // SQLDATABASE_H
