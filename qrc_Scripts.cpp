/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 5.1.1
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtCore/qglobal.h>

static const unsigned char qt_resource_data[] = {
  // /home/afreak/vimplusspluss/ORFEditor/ORF/Editor/JS/testscript.js
  0x0,0x0,0x0,0x3f,
  0x76,
  0x61,0x72,0x20,0x54,0x69,0x74,0x6c,0x65,0x43,0x6f,0x6c,0x6f,0x72,0x20,0x3d,0x20,
  0x5b,0x30,0x2e,0x30,0x2c,0x31,0x2e,0x30,0x2c,0x31,0x2e,0x30,0x5d,0x3b,0xa,0x76,
  0x61,0x72,0x20,0x54,0x65,0x78,0x74,0x43,0x6f,0x6c,0x6f,0x72,0x20,0x3d,0x20,0x5b,
  0x30,0x2e,0x30,0x2c,0x31,0x2e,0x30,0x2c,0x30,0x2e,0x30,0x5d,0x3b,0xa,
  
};

static const unsigned char qt_resource_name[] = {
  // testscript.js
  0x0,0xd,
  0xc,0x92,0x7,0xb3,
  0x0,0x74,
  0x0,0x65,0x0,0x73,0x0,0x74,0x0,0x73,0x0,0x63,0x0,0x72,0x0,0x69,0x0,0x70,0x0,0x74,0x0,0x2e,0x0,0x6a,0x0,0x73,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
  // :/testscript.js
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,

};

QT_BEGIN_NAMESPACE

extern Q_CORE_EXPORT bool qRegisterResourceData
    (int, const unsigned char *, const unsigned char *, const unsigned char *);

extern Q_CORE_EXPORT bool qUnregisterResourceData
    (int, const unsigned char *, const unsigned char *, const unsigned char *);

QT_END_NAMESPACE


int QT_MANGLE_NAMESPACE(qInitResources_Scripts)()
{
    QT_PREPEND_NAMESPACE(qRegisterResourceData)
        (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_Scripts))

int QT_MANGLE_NAMESPACE(qCleanupResources_Scripts)()
{
    QT_PREPEND_NAMESPACE(qUnregisterResourceData)
       (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

Q_DESTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qCleanupResources_Scripts))

