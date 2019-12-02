TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        brake.cpp \
        optcontrolproblem.cpp \
        solution.cpp \
        solutiongenerator.cpp \
        stretch.cpp \
        train.cpp \
        main.cpp

HEADERS += \
    brake.h \
    map_table.h \
    optcontrolproblem.h \
    solution.h \
    solutiongenerator.h \
    stretch.h \
    tools.h \
    train.h \
    weather.h
