#-------------------------------------------------
#
# Project created by QtCreator 2019-05-05T11:42:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = assembly-calculator
TEMPLATE = app


SOURCES += main.cpp\
        AssemblyCalculator.cpp\
        FloatOperations.s \
        Conversions.s \
        ClickableQLabel.cpp \
        ClickableQLineEdit.cpp

HEADERS  += AssemblyCalculator.hpp \
    Operation.hpp \
    CalculatorMode.hpp \
    ClickableQLabel.hpp \
    ClickableQLineEdit.hpp

FORMS    += AssemblyCalculator.ui

DISTFILES += \
    FloatOperations.s \
    Conversions.s
