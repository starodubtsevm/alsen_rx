#QT += charts
INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD

LIBS += -lfftw3

HEADERS += \
    $$PWD/ChartsViewForm.h \
    $$PWD/chartViewDinamicForm.h \
    $$PWD/chartviewform.h

SOURCES += \
    $$PWD/ChartsViewForm.cpp \
    $$PWD/chartViewDinamicForm.cpp \
    $$PWD/chartviewform.cpp

FORMS += \
    $$PWD/ChartsViewFform.ui \
    $$PWD/chartViewDinamicForm.ui \
    $$PWD/chartviewform.ui
