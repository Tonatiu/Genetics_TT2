QT += core
QT -= gui

CONFIG += c++11

TARGET = PM10_Calculations
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    app/utils/pm10_calculator.cpp \
    app/utils/Genetics/geneticcalculator.cpp \
    app/utils/Genetics/pm10_cromosome.cpp

HEADERS += \
    app/utils/pm10_calculator.h \
    app/utils/Genetics/geneticcalculator.h \
    app/utils/Genetics/pm10_cromosome.h
