QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barchart.cpp \
    chartv.cpp \
    datastructure.cpp \
    graphviewer.cpp \
    linechart.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    nestedDonut.cpp

HEADERS += \
    barchart.h \
    chartv.h \
    datastructure.h \
    graphviewer.h \
    linechart.h \
    mainwindow.h \
    model.h \
    nestedDonut.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
