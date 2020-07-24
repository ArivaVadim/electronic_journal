QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clientdelete.cpp \
    clients.cpp \
    clientscategory.cpp \
    clientsinsert.cpp \
    clientupdate.cpp \
    journal.cpp \
    journaladdclient.cpp \
    main.cpp \
    mainwindow.cpp \
    masterdelete.cpp \
    masters.cpp \
    mastersinsert.cpp \
    mastersupdate.cpp \
    yslugi.cpp \
    yslygidelete.cpp \
    yslygiinsert.cpp \
    yslygiupdate.cpp

HEADERS += \
    clientdelete.h \
    clients.h \
    clientscategory.h \
    clientsinsert.h \
    clientupdate.h \
    journal.h \
    journaladdclient.h \
    mainwindow.h \
    masterdelete.h \
    masters.h \
    mastersinsert.h \
    mastersupdate.h \
    yslugi.h \
    yslygidelete.h \
    yslygiinsert.h \
    yslygiupdate.h

FORMS += \
    clientdelete.ui \
    clients.ui \
    clientscategory.ui \
    clientsinsert.ui \
    clientupdate.ui \
    journal.ui \
    journaladdclient.ui \
    mainwindow.ui \
    masterdelete.ui \
    masters.ui \
    mastersinsert.ui \
    mastersupdate.ui \
    yslugi.ui \
    yslygidelete.ui \
    yslygiinsert.ui \
    yslygiupdate.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
