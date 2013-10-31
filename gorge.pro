TEMPLATE = app
TARGET = gorge.xctbl
CONFIG += debug
CONFIG -= QT
DEFINES -= UNICODE
unix {
    #OGRE3D
    INCLUDEPATH += /home/afreak/ogre/OGRE19/sinbad-ogre-f7da7fe2d384/OgreMain/include/
    INCLUDEPATH += /home/afreak/ogre/OGRE19/sinbad-ogre-f7da7fe2d384/Samples/Common/include/
    INCLUDEPATH += /home/afreak/ogre/OGRE19/sinbad-ogre-f7da7fe2d384/Components/Overlay/include/
    INCLUDEPATH += /home/afreak/ogre/OGRE19/MADE/include/
    #GUI3D
    INCLUDEPATH += /home/afreak/Downloads/Gui3D-master/build/source/
    INCLUDEPATH += /home/afreak/Downloads/Gui3D-master/examples/build/ #guitemplate
    #ORFPhysics
    INCLUDEPATH += ./physLib/src/btOgre/
    INCLUDEPATH += ./physLib/src/object/
    INCLUDEPATH += ./physLib/src/world/
    #OIS
    INCLUDEPATH += /usr/include/OIS/
    #BULLET
    INCLUDEPATH += /usr/include/bullet/
    #GUI3D
    LIBS += /home/afreak/libs/Gui3D/gui3dBuilt/bin/Debug/libgui3dBuilt.a
    #OGRE3D
    LIBS += -L/home/afreak/ogre/OGRE19/MADE/lib/
    LIBS *= -lOgreMain -lOIS -lOgreOverlay
    #BULLET
    LIBS *= -lBulletDynamics -lBulletCollision -lLinearMath
    #ORFPhysics
    LIBS += /home/afreak/libs/hPhys/hPhys/bin/Debug/libhPhys.a
}
win32 {
    #OGRE3D & BULLET
    INCLUDEPATH += $(OGRE_HOME)/include/OIS
    INCLUDEPATH += $(OGRE_HOME)/include/OGRE
    INCLUDEPATH += $(OGRE_HOME)/boost
    INCLUDEPATH += $(BULLET_HOME)/src
    LIBS *= user32.lib
    LIBS += -L$(OGRE_HOME)/boost/lib
    LIBS += -L$(BULLET_HOME)/lib/

    #ORFPhysics
    INCLUDEPATH += ./physLib/src/btOgre/
    INCLUDEPATH += ./physLib/src/object/
    INCLUDEPATH += ./physLib/src/world/
    #library built from Physics1 branch
    LIBS += /x/libs/hPhys/hPhys/bin/Debug/libhPhys.a

    #GUI3D link: http://www.valentinfrechaud.fr/GuiWiki/index.php/Main_Page
    INCLUDEPATH += /x/Gui3D-master/build/source/
    INCLUDEPATH += /x/Gui3D-master/examples/build/ #guitemplate
    LIBS += /x/libs/Gui3D/gui3dBuilt/bin/Debug/libgui3dBuilt.a

    debug {
        LIBS += -L$(OGRE_HOME)/lib/Debug
        LIBS *= -lOgreMain_d -lOIS_d -lOgreOverlay_d
        LIBS *= -lBulletDynamics_vs2010_debug  -lBulletCollision_vs2010_debug -lLinearMath_vs2010_debug
    }

    release {
        LIBS += -L$(OGRE_HOME)/lib/Release
        LIBS *= -lOgreMain -lOIS -lOgreOverlay
        LIBS *= -lBulletDynamics_vs2010  -lBulletCollision_vs2010 -lLinearMath_vs2010
    }

}
INCLUDEPATH += ./source
SOURCES += \
    source/main.cpp \
    source/OgreFramework.cpp \
    source/Editor.cpp \
    source/MyPurplePanelColors.cpp \
    source/Mode.cpp \
    source/MenuMode.cpp \
    source/InsertMode.cpp \
    source/FirstPersonNoClip.cpp \
    source/FileIO.cpp \
    source/InputHandling.cpp \

HEADERS += \
    source/OgreFramework.h \
    source/Editor.h \
    source/MyPurplePanelColors.h \
    source/Mode.h \
    source/MenuMode.h \
    source/InsertMode.h \
    source/FirstPersonNoClip.h \
    source/FileIO.h \
    source/InputHandling.h \


