TEMPLATE = app
TARGET = Editor

DEFINES -= UNICODE

QT      += opengl widgets

win32 {
    INCLUDEPATH += $(OGRE_HOME)\\include
    INCLUDEPATH += $(OGRE_HOME)\\include\\OIS
    INCLUDEPATH += $(OGRE_HOME)\\include\\OGRE
    INCLUDEPATH += $(OGRE_HOME)\\boost
    INCLUDEPATH += ./include
    LIBS *= user32.lib
    LIBS += -L$(OGRE_HOME)\\boost\\lib
    release:LIBS += -L$(OGRE_HOME)\\lib\\release
    debug:LIBS += -L$(OGRE_HOME)\\lib\\debug
}

debug {
    LIBS *= -lOgreMain_d -lOIS_d -lOgreOverlay_d
}

release
{
    LIBS *= -lOgreMain -lOIS -lOgreOverlay
}

SOURCES += \
    src/OgreWidget.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/OgreWidget.h \
    include/mainwindow.h

FORMS += \
    mainwindow.ui

