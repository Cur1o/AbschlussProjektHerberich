QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addtask.cpp \
    databasemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    taskelement.cpp

HEADERS += \
    addtask.h \
    databasemanager.h \
    enums.h \
    mainwindow.h \
    taskelement.h

FORMS += \
    addtask.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	data.qrc

TRANSLATIONS += \
	AbschlussprojektHerberich_de_DE.ts \
	AbschlussprojektHerberich_en_GB.ts
