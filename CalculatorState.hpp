#ifndef CALCULATORSTATE_H
#define CALCULATORSTATE_H
#include "ui_AssemblyCalculator.h"
#include "Operation.hpp"
class CalculatorState
{
public:
    CalculatorState(Ui::AssemblyCalculator * ui);
    virtual void valueEntered(const QString& buttonPressed) = 0;
    virtual void operationEntered(const QString& buttonPressed) = 0;
    virtual void equalsPressed() = 0;
    virtual void backspacePressed() = 0;
    virtual void clearDisplays() = 0;
    virtual void resetState();
    virtual void negatePressed();

protected:
    Ui::AssemblyCalculator * ui;
    Operation selectedOperation = Operation::NONE;
    bool resultDisplayed = false;

    bool isDecValue(const QString& value) const;
    bool isHexValue(const QString& value) const;
};

#endif // CALCULATORSTATE_H
