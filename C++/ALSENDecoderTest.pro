QT       += core gui testlib multimedia xml charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEPENDPATH  += $$PWD
INCLUDEPATH += $$PWD #$$PWD/include $$PWD/ui

MOC_DIR     += tmp
OBJECTS_DIR += tmp
#UI_DIR      += $$PWD/ui

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

# Отключение предупреждения с QTransform
QMAKE_CFLAGS_WARN_ON += -Wno-class-memaccess
QMAKE_CFLAGS_WARN_ON += -Wno-deprecated-copy
QMAKE_CXXFLAGS_WARN_ON += -Wno-class-memaccess
QMAKE_CXXFLAGS_WARN_ON += -Wno-deprecated-copy
QMAKE_CFLAGS += -Wno-class-memaccess
QMAKE_CFLAGS += -Wno-deprecated-copy
QMAKE_CXXFLAGS += -Wno-class-memaccess
QMAKE_CXXFLAGS += -Wno-deprecated-copy

include(signalview.pri);
#include(logger.pri);
include(alsencomponents.pri);
include(digitalfilters.pri);

SOURCES += \
    main.cpp \
    decodertestmain.cpp

HEADERS += \
    decodertestmain.h

FORMS += \
    decodertestmain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
