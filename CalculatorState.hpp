#ifndef CALCULATORSTATE_H
#define CALCULATORSTATE_H
#include "ui_AssemblyCalculator.h"
#include "Operation.hpp"
#include <QPushButton>

class CalculatorState
{
public:
    CalculatorState(Ui::AssemblyCalculator * ui);
    virtual void valueEntered(QPushButton * sender) = 0;
    virtual void operationEntered(QPushButton * sender) = 0;
    virtual void equalsPressed() = 0;
    virtual void clearDisplays() = 0;
    virtual void resetState();
    virtual void negatePressed();

protected:
    Ui::AssemblyCalculator * ui;
    Operation selectedOperation = Operation::NONE;
    bool resultDisplayed = false;
};

#endif // CALCULATORSTATE_H