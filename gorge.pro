TEMPLATE = app
TARGET = gorge
CONFIG += debug
CONFIG -= QT
DEFINES -= UNICODE
unix {
    # ikke akkurat portabelt, men jeg har ogre 1.8 som jeg syntes er mindre bugs i i /usr/
    INCLUDEPATH += /home/afreak/ogre/OGRE19/sinbad-ogre-f7da7fe2d384/OgreMain/include/
    INCLUDEPATH += /home/afreak/ogre/OGRE19/sinbad-ogre-f7da7fe2d384/Samples/Common/include/
    INCLUDEPATH += /home/afreak/ogre/OGRE19/sinbad-ogre-f7da7fe2d384/Components/Overlay/include/
    INCLUDEPATH += /home/afreak/ogre/OGRE19/MADE/include/
    INCLUDEPATH += /home/afreak/Downloads/Gui3D-master/build/source/
    INCLUDEPATH += /home/afreak/Downloads/Gui3D-master/examples/build/
    INCLUDEPATH += /usr/include/OIS/
    LIBS += /home/afreak/libs/Gui3D/gui3dBuilt/bin/Debug/libgui3dBuilt.a
    LIBS += -L/home/afreak/ogre/OGRE19/MADE/lib/
    LIBS *= -lOgreMain -lOIS -lOgreOverlay
}
INCLUDEPATH += ./source
SOURCES += \
    source/main.cpp \
    source/OgreFramework.cpp \
    source/DemoApp.cpp \
    source/MyPurplePanelColors.cpp \
    source/Mode.cpp \
    source/MenuMode.cpp \
    source/InsertMode.cpp \

HEADERS += \
    source/OgreFramework.h \
    source/DemoApp.h \
    source/MyPurplePanelColors.h \
    source/Mode.h \
    source/MenuMode.h \
    source/InsertMode.h \


