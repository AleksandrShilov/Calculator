QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    calculate.c \
    creditcalc.cpp \
    depositcalc.cpp \
    graph.cpp \
    input_x.cpp \
    main.cpp \
    mainwindow.cpp \
    pars.c \
    qcustomplot.cpp \
    rpn.c \
    stack.c

HEADERS += \
    calculate.h \
    creditcalc.h \
    depositcalc.h \
    graph.h \
    input_x.h \
    mainwindow.h \
    pars.h \
    qcustomplot.h \
    rpn.h \
    stack.h

FORMS += \
    creditcalc.ui \
    depositcalc.ui \
    graph.ui \
    input_x.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
