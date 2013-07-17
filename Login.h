#ifndef LOGIN_H
#define LOGIN_H

/*
 * Boost Serialization
 */
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>

#include <QObject>
#include <QString>
#include <QMap>

// Forward declaration of class boost::serialization::access
namespace boost
{
    namespace serialization
    {
        class access ;
    }
}


class Login
{
public:
    Login() ;
    Login(QString username, QString password) ;
    ~Login() ;

    QString getQUsername() ;
    void setQUsername(QString username) ;

    QString getQPassword() ;
    void setQPassword(QString password) ;

    std::string getUsername() ;
    void setUsername(std::string username) ;

    std::string getPassword() ;
    void setPassword(std::string password) ;

signals:

public slots:

private:
    std::string username ;
    std::string password ;

    friend class boost::serialization::access ;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar & this->username & this->password ;
    }

private slots:

};

#endif // LOGIN_H
