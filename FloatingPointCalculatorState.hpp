#ifndef FLOATINGPOINTCALCULATORSTATE_H
#define FLOATINGPOINTCALCULATORSTATE_H
#include "CalculatorState.hpp"

extern "C" double * addition(double, double);
extern "C" double * subtraction(double, double);
extern "C" double * multiplication(double, double);
extern "C" double * division(double, double);
extern "C" double * exponentation(double, int);
extern "C" double * squareRoot(double);

class FloatingPointCalculatorState : public CalculatorState
{
public:
    FloatingPointCalculatorState(Ui::AssemblyCalculator * ui);
    virtual void clearDisplays() override;
    virtual void valueEntered(const QString& buttonPressed) override;
    virtual void operationEntered(const QString& buttonPressed) override;
    virtual void equalsPressed() override;
    virtual void backspacePressed() override;
    virtual void resetState() override;

private:
    double firstOperand = 0.0;
};

#endif // FLOATINGPOINTCALCULATORSTATE_H
