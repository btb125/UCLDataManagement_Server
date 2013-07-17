#include "SQLDatabase.h"

SQLDatabase::SQLDatabase()
{
    /*
     * Settings
     */
    this->HOST = "LOCALHOST\\SQLEXPRESS" ;
    this->SYSTEM_DSN = "UCL Data Management" ;
    this->SCHEMA = "dbo" ;
    this->DATABASE_NAME = "dbUCLDataManagement" ;

    /*
     * Database Object
     */
    this->DATABASE = QSqlDatabase::addDatabase("QODBC") ;
    this->DATABASE.setHostName(HOST) ;
    this->DATABASE.setDatabaseName(SYSTEM_DSN) ;

    /*
     * Tables
     */
    APL_TABLE = "AccessPermissionLists" ;
    USERS_TABLE = "Users" ;
    PARTICIPANTS_TABLE = "Participants" ;
    QUESTIONNAIRES_TABLE = "Questionnaires" ;
    QUESTION_BOOLEAN_TABLE = "QuestionsOfTypeBoolean" ;
    QUESTION_NUMBER_TABLE = "QuestionsOfTypeNumber" ;
    QUESTION_TEXT_TABLE = "QuestionsOfTypeText" ;
}

void SQLDatabase::initialiseSQLDatabase()
{
    createDatabase() ;
    createTableForAccessPermissionLists() ;
    createTableForUsers() ;
    insertSuperUser() ;
    createTableForParticipants() ;
    createTableForQuestionnaires() ;
}

void SQLDatabase::createDatabase()
{

}

void SQLDatabase::createTableForAccessPermissionLists()
{

}

void SQLDatabase::createTableForUsers()
{

}

void SQLDatabase::insertSuperUser()
{

}

void SQLDatabase::createTableForParticipants()
{

}

void SQLDatabase::createTableForQuestionnaires()
{
    QString createTableString = "CREATE TABLE [" ;
    createTableString.append(this->DATABASE_NAME) ;
    createTableString.append("].[") ;
    createTableString.append(this->SCHEMA) ;
    createTableString.append("].[") ;
    createTableString.append(QUESTIONNAIRES_TABLE) ;
    createTableString.append("](") ;
    createTableString.append("ID VARCHAR (6) NOT NULL,") ;
    createTableString.append("NOTE VARCHAR (50),") ;
    createTableString.append("PRIMARY KEY (ID)") ;
    createTableString.append(");") ;

    if(this->DATABASE.open())
    {
        qDebug() << "Initialising Questionnaires Table..." ;

        QSqlQuery query ;
        query.prepare(createTableString) ;

        if (query.exec())
        {
            qDebug() << "Success!\n" ;
        }

        this->DATABASE.close() ;
    }
    else
    {
        qDebug() << "Error: " << this->DATABASE.lastError().text() ;
    }

    createTableForQuestionsOfBooleanType() ;
    createTableForQuestionsOfNumberType() ;
    createTableForQuestionsOfTextType() ;
}

void SQLDatabase::createTableForQuestionsOfBooleanType()
{
    QString createTableString = "CREATE TABLE [" ;
    createTableString.append(this->DATABASE_NAME) ;
    createTableString.append("].[") ;
    createTableString.append(this->SCHEMA) ;
    createTableString.append("].[") ;
    createTableString.append(QUESTION_BOOLEAN_TABLE) ;
    createTableString.append("](") ;
    createTableString.append("ID VARCHAR (6) NOT NULL,") ;
    createTableString.append("QUESTIONNAIRE_ID VARCHAR (6) NOT NULL,") ;
    createTableString.append("QUESTION VARCHAR (100) NOT NULL,") ;
    createTableString.append("QNUMBER INT NOT NULL,") ;
    createTableString.append("ANSWER BIT,") ;
    createTableString.append("PRIMARY KEY (ID)") ;
    createTableString.append(");") ;

    if(this->DATABASE.open())
    {
        qDebug() << "Initialising Question(Boolean) Table..." ;

        QSqlQuery query ;
        query.prepare(createTableString) ;

        if (query.exec())
        {
            qDebug() << "Success!\n" ;
        }

        this->DATABASE.close() ;
    }
    else
    {
        qDebug() << "Error: " << this->DATABASE.lastError().text() ;
    }
}

void SQLDatabase::createTableForQuestionsOfNumberType()
{
    QString createTableString = "CREATE TABLE [" ;
    createTableString.append(this->DATABASE_NAME) ;
    createTableString.append("].[") ;
    createTableString.append(this->SCHEMA) ;
    createTableString.append("].[") ;
    createTableString.append(QUESTION_NUMBER_TABLE) ;
    createTableString.append("](") ;
    createTableString.append("ID VARCHAR (6) NOT NULL,") ;
    createTableString.append("QUESTIONNAIRE_ID VARCHAR (6) NOT NULL,") ;
    createTableString.append("QUESTION VARCHAR (100) NOT NULL,") ;
    createTableString.append("QNUMBER INT NOT NULL,") ;
    createTableString.append("ANSWER INT,") ;
    createTableString.append("BASE INT,") ;
    createTableString.append("RANGE INT,") ;
    createTableString.append("PRIMARY KEY (ID)") ;
    createTableString.append(");") ;

    if(this->DATABASE.open())
    {
        qDebug() << "Initialising Question(Number) Table..." ;

        QSqlQuery query ;
        query.prepare(createTableString) ;

        if (query.exec())
        {
            qDebug() << "Success!\n" ;
        }

        this->DATABASE.close() ;
    }
    else
    {
        qDebug() << "Error: " << this->DATABASE.lastError().text() ;
    }
}

void SQLDatabase::createTableForQuestionsOfTextType()
{
    QString createTableString = "CREATE TABLE [" ;
    createTableString.append(this->DATABASE_NAME) ;
    createTableString.append("].[") ;
    createTableString.append(this->SCHEMA) ;
    createTableString.append("].[") ;
    createTableString.append(QUESTION_TEXT_TABLE) ;
    createTableString.append("](") ;
    createTableString.append("ID VARCHAR (6) NOT NULL,") ;
    createTableString.append("QUESTIONNAIRE_ID VARCHAR (6) NOT NULL,") ;
    createTableString.append("QUESTION VARCHAR (100) NOT NULL,") ;
    createTableString.append("QNUMBER INT NOT NULL,") ;
    createTableString.append("ANSWER VARCHAR (100),") ;
    createTableString.append("PRIMARY KEY (ID)") ;
    createTableString.append(");") ;

    if(this->DATABASE.open())
    {
        qDebug() << "Initialising Question(Text) Table..." ;

        QSqlQuery query ;
        query.prepare(createTableString) ;

        if (query.exec())
        {
            qDebug() << "Success!\n" ;
        }

        this->DATABASE.close() ;
    }
    else
    {
        qDebug() << "Error: " << this->DATABASE.lastError().text() ;
    }
}

void SQLDatabase::backUpToFile()
{

}

void SQLDatabase::restoreFromBackUpFile()
{

}

void SQLDatabase::insertDummyDataForTesting()
{
    if(this->DATABASE.open())
    {
        QString insert = "INSERT INTO [dbUCLDataManagement].[dbo].[Questionnaires]([ID],[NOTE]) VALUES ('qu1234','Dummy Questionnaire. Created by DB Init') ;" ;
        QSqlQuery queryQu ;
        queryQu.prepare(insert) ;
        if (queryQu.exec())
        {
            qDebug() << "Questionnaire - Record Inserted" ;
        }

        insert = "INSERT INTO [dbUCLDataManagement].[dbo].[QuestionsOfTypeBoolean]([ID],[QUESTIONNAIRE_ID],[QUESTION],[QNUMBER],[ANSWER]) VALUES ('qb1111','qu1234','Question Boolean A', 1, 1) ;" ;
        QSqlQuery queryQbONE ;
        queryQbONE.prepare(insert) ;
        if (queryQbONE.exec())
        {
            qDebug() << "Question Boolean 1 - Record Inserted" ;
        }

        insert = "INSERT INTO [dbUCLDataManagement].[dbo].[QuestionsOfTypeBoolean]([ID],[QUESTIONNAIRE_ID],[QUESTION],[QNUMBER],[ANSWER]) VALUES ('qb2222','qu1234','Question Boolean B', 5, 0) ;" ;
        QSqlQuery queryQbTWO ;
        queryQbTWO.prepare(insert) ;
        if (queryQbTWO.exec())
        {
            qDebug() << "Question Boolean 1 - Record Inserted" ;
        }

        insert = "INSERT INTO [dbUCLDataManagement].[dbo].[QuestionsOfTypeBoolean]([ID],[QUESTIONNAIRE_ID],[QUESTION],[QNUMBER],[ANSWER]) VALUES ('qb3333','qu1234','Question Boolean C', 2, 1) ;" ;
        QSqlQuery queryQbTHREE ;
        queryQbTHREE.prepare(insert) ;
        if (queryQbTHREE.exec())
        {
            qDebug() << "Question Boolean 1 - Record Inserted" ;
        }

        insert = "INSERT INTO [dbUCLDataManagement].[dbo].[QuestionsOfTypeNumber]([ID],[QUESTIONNAIRE_ID],[QUESTION],[QNUMBER],[ANSWER],[BASE],[RANGE]) VALUES ('qn1111','qu1234','Question Number A', 4, 0, 0, 5) ;" ;
        QSqlQuery queryQnONE ;
        queryQnONE.prepare(insert) ;
        if (queryQnONE.exec())
        {
            qDebug() << "Question Number 1 - Record Inserted" ;
        }

        insert = "INSERT INTO [dbUCLDataManagement].[dbo].[QuestionsOfTypeNumber]([ID],[QUESTIONNAIRE_ID],[QUESTION],[QNUMBER],[ANSWER],[BASE],[RANGE]) VALUES ('qn2222','qu1234','Question Number B', 3, 2, 1, 10) ;" ;
        QSqlQuery queryQnTWO ;
        queryQnTWO.prepare(insert) ;
        if (queryQnTWO.exec())
        {
            qDebug() << "Question Number 2 - Record Inserted" ;
        }

        insert = "INSERT INTO [dbUCLDataManagement].[dbo].[QuestionsOfTypeNumber]([ID],[QUESTIONNAIRE_ID],[QUESTION],[QNUMBER],[ANSWER],[BASE],[RANGE]) VALUES ('qn3333','qu1234','Question Number C', 7, 4, 2, 15) ;" ;
        QSqlQuery queryQnTHREE ;
        queryQnTHREE.prepare(insert) ;
        if (queryQnTHREE.exec())
        {
            qDebug() << "Question Number 3 - Record Inserted" ;
        }

        insert = "INSERT INTO [dbUCLDataManagement].[dbo].[QuestionsOfTypeNumber]([ID],[QUESTIONNAIRE_ID],[QUESTION],[QNUMBER],[ANSWER],[BASE],[RANGE]) VALUES ('qn4444','qu1234','Question Number D', 8, 6, 3, 20) ;" ;
        QSqlQuery queryQnFOUR ;
        queryQnFOUR.prepare(insert) ;
        if (queryQnFOUR.exec())
        {
            qDebug() << "Question Number 4 - Record Inserted" ;
        }

        insert = "INSERT INTO [dbUCLDataManagement].[dbo].[QuestionsOfTypeText]([ID],[QUESTIONNAIRE_ID],[QUESTION],[QNUMBER],[ANSWER]) VALUES ('qt1111','qu1234','Question Text A', 6, 'This is the answer to q1a') ;" ;
        QSqlQuery queryQtONE ;
        queryQtONE.prepare(insert) ;
        if (queryQtONE.exec())
        {
            qDebug() << "Question Text 1 - Record Inserted" ;
        }

        insert = "INSERT INTO [dbUCLDataManagement].[dbo].[QuestionsOfTypeText]([ID],[QUESTIONNAIRE_ID],[QUESTION],[QNUMBER],[ANSWER]) VALUES ('qt2222','qu1234','Question Text B', 0, 'This is the answer to q2b') ;" ;
        QSqlQuery queryQtTWO ;
        queryQtTWO.prepare(insert) ;
        if (queryQtTWO.exec())
        {
            qDebug() << "Question Text 2 - Record Inserted" ;
        }
    }

    this->DATABASE.close() ;
}
