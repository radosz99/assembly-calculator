#ifndef FLOATINGPOINTCALCULATORSTATE_H
#define FLOATINGPOINTCALCULATORSTATE_H
#include "CalculatorState.hpp"

class FloatingPointCalculatorState : public CalculatorState
{
public:
    FloatingPointCalculatorState(Ui::AssemblyCalculator * ui);
    virtual void clearDisplays() override;
    virtual void valueEntered(QPushButton * sender) override;
    virtual void resetState() override;

private:
    double firstOperand = 0.0;
};

#endif // FLOATINGPOINTCALCULATORSTATE_H
