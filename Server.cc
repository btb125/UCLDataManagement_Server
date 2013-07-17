#include "Server.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
}

void Server::startServer()
{
    if (listen(QHostAddress::Any, 1234))
    {
        qDebug() << "Server Started";
    }
    else
    {
        qDebug() << "Server Did NOT Start!";
    }
}

void Server::incomingConnection(int handle)
{
    Client *client = new Client(this) ;
    client->setSocket(handle) ;
}
