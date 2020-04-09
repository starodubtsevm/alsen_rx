INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD

HEADERS +=  \
    $$PWD/alsenSignalGen.h \
    $$PWD/alsenconst.h \
    $$PWD/alsensignaldecoder.h \
    $$PWD/alsensignaliodevice.h \
    $$PWD/alsen_rx.h \
    $$PWD/decode.h \
    $$PWD/pll2.h
SOURCES +=  \
    $$PWD/alsenSignalGen.cpp \
    $$PWD/alsensignaldecoder.cpp \
    $$PWD/alsensignaliodevice.cpp \
    $$PWD/alsen_rx.cpp \
    $$PWD/decode.cpp \
    $$PWD/pll2.cpp
