#-------------------------------------------------
#
# Project created by QtCreator 2013-05-22T17:26:18
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui
QT       += sql

QMAKE_CXXFLAGS += -std=c++0x

TARGET = UCLDataManagement_Server_v001
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Server.cc \
    Client.cc \
    SQLMessaging.cc \
    Log.cc \
    AccessPermissionList.cc \
    User.cc \
    Person.cc \
    Login.cc \
    Connection.cc \
    Participant.cc \
    Questionnaire.cc \
    Question.cc \
    BooleanQuestion.cc \
    NumberQuestion.cc \
    TextQuestion.cc \
    SQLDatabase.cc

HEADERS += \
    Server.h \
    Client.h \
    SQLMessaging.h \
    Log.h \
    AccessPermissionList.h \
    User.h \
    Person.h \
    Login.h \
    Connection.h \
    Participant.h \
    Questionnaire.h \
    Question.h \
    BooleanQuestion.h \
    NumberQuestion.h \
    TextQuestion.h \
    SQLDatabase.h

INCLUDEPATH += C:/boost/boost_1_53_0

LIBS += -LC:/boost_lib/boost/bin.v2/libs/serialization/build/gcc-mingw-4.7.2/debug/link-static/threading-multi -lboost_serialization-mgw47-mt-d-1_53
#LIBS += C:\boost_lib\boost\bin.v2\libs\date_time\build\gcc-mingw-4.7.2\release\link-static\threading-multi\libboost_date_time-mgw47-mt-1_53.a
