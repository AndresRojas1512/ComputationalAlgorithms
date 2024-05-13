QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Include Python headers
INCLUDEPATH += /usr/include/python3.10

# Include your custom headers
# INCLUDEPATH += /home/andres/Desktop/4Semester/CA/ComputationalAlgorithms/Lab_04/inc

# Include Boost headers
INCLUDEPATH += /home/andres/BoostCpp/boost_1_85_0

# Link against the Python library
LIBS += -lpython3.10

# Link against Boost libraries
LIBS += -L/home/andres/BoostCpp/boost_1_85_0/stage/lib -lboost_math_c99

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mfile.cpp \
    ode.cpp \
    point.cpp \
    polynomial.cpp \
    slae.cpp \
    table.cpp


HEADERS += \
    mainwindow.h \
    mfile.h \
    ode.h \
    point.h \
    polynomial.h \
    slae.h \
    table.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    odeplot.py
