QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    WorldController.cpp \
    WorldView.cpp \
    abstracttilecontroller.cpp \
    enemycontroller.cpp \
    healthpackcontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    tilecontroller.cpp

HEADERS += \
    GameData.h \
    WorldController.h \
    WorldView.h \
    abstracttilecontroller.h \
    enemycontroller.h \
    healthpackcontroller.h \
    mainwindow.h \
    pathfinding.h \
    tilecontroller.h

FORMS += \
    mainwindow.ui


DISTFILES += \
    images/maze1.png \
    images/maze2.png \
    images/maze3.png \
    images/worldmap.png \
    images/worldmap.png

RESOURCES += \
    images.qrc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/release/ -lworld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/ -lworld
else:unix: LIBS += -L$$PWD/lib/ -lworld

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
