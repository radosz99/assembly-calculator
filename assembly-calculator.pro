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
        P_addition.s \
        P_subtraction.s \
        P_multiplication.s \
        P_division.s \
        P_exponentation.s \
        P_squareRoot.s \
        ClickableQLabel.cpp \
        ClickableQLineEdit.cpp \
        CalculatorState.cpp \
        FloatingPointCalculatorState.cpp \
        ProgrammerCalculatorState.cpp

HEADERS  += AssemblyCalculator.hpp \
    Operation.hpp \
    ClickableQLabel.hpp \
    ClickableQLineEdit.hpp \
    CalculatorState.hpp \
    FloatingPointCalculatorState.hpp \
    ProgrammerCalculatorState.hpp

FORMS    += AssemblyCalculator.ui

DISTFILES += \
    FloatOperations.s \
    Conversions.s \
    P_addition.s \
    P_subtraction.s \
    P_multiplication.s \
    P_division.s \
    P_exponentation.s \
    P_squareRoot.s
