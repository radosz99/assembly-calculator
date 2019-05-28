#ifndef PROGRAMMERCALCULATORSTATE_H
#define PROGRAMMERCALCULATORSTATE_H
#include "CalculatorState.hpp"

extern "C" char * convertNumber(char from, const char * number, char to);

class ProgrammerCalculatorState : public CalculatorState
{
public:
    ProgrammerCalculatorState(Ui::AssemblyCalculator * ui);
    void baseChanged(QObject * sender);

    virtual void clearDisplays() override;
    virtual void valueEntered(QPushButton * sender) override;
    virtual void operationEntered(QPushButton * sender) override;
    virtual void equalsPressed() override;
    virtual void resetState() override;

private:
    QString firstOperand = "";
    char base = 'b';

    void enableBinMode();
    void enableDecMode();
    void enableHexMode();
    void setDecButtonsActive(bool active);
    void setHexButtonsActive(bool active);
};

#endif // PROGRAMMERCALCULATORSTATE_H
