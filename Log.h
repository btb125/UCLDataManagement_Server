#ifndef LOG_H
#define LOG_H

#include <QObject>

class Log : public QObject
{
    Q_OBJECT
public:
    explicit Log(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // LOG_H
