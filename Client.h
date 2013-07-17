#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>

#include <string>
#include <sstream>

#include "Login.h"

#include "SQLMessaging.h"
#include "Connection.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void setSocket(int descriptor) ;

signals:
    
public slots:
    void connected() ;
    void disconnected() ;
    void readyRead() ;
    void readyWrite() ;

private:
    QTcpSocket *socket ;
    Connection connection ;
};

#endif // CLIENT_H
