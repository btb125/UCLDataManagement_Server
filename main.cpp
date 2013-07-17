#include <QCoreApplication>

#include "Server.h"

//Delete This:
#include "SQLDatabase.h"

int main(int argc, char *argv[])
{
    //Ignore
    QCoreApplication a(argc, argv);
    
    //Start Server
    Server server ;
    server.startServer() ;

//    SQLDatabase sqlDatabase ;
//    sqlDatabase.initialiseSQLDatabase() ;
//    sqlDatabase.insertDummyDataForTesting() ;

    //Exit
    return a.exec();
}
