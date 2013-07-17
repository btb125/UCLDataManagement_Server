#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QThreadPool>
#include "Client.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    
    void startServer() ;
    void incomingConnection(int handle) ;

signals:
    
public slots:

};

#endif // SERVER_H
