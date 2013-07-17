#include "Client.h"

Client::Client(QObject *parent) :
    QObject(parent)
{
    //QThreadPool::globalInstance()->setMaxThreadCount(15) ;
}

void Client::setSocket(int descriptor)
{
    socket = new QTcpSocket(this) ;

    connect(socket, SIGNAL(connected()), this, SLOT(connected())) ;
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected())) ;
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead())) ;

    socket->setSocketDescriptor(descriptor) ;

    qDebug() << "Client Connected" ;
}

void Client::connected()
{
    qDebug() << "Client Connected (Event)" ;
}

void Client::disconnected()
{
    qDebug() << "Client Disconnected" ;
}

void Client::readyRead()
{
    //Prepare Data to be read from Socket
    QString inboundQData = socket->readAll() ;

    //Delete This
    qDebug() << "In-" << inboundQData ;

    //Read
    this->connection.read(inboundQData.toStdString());

    //Connection Works On Incoming Message

    //Delete This
    qDebug() << "Out-" << QString::fromStdString(this->connection.getOutboundHeader())
                       << QString::fromStdString(this->connection.getOutboundMessage()) ;

    //Write Message
    readyWrite() ;
}

void Client::readyWrite()
{
    QByteArray buffer ;

    buffer.append(QString::fromStdString(this->connection.write())) ;

    socket->write(buffer) ;
}
