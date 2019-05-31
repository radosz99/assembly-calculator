#ifndef PROGRAMMERCALCULATORSTATE_H
#define PROGRAMMERCALCULATORSTATE_H
#include "CalculatorState.hpp"

extern "C" char * convertNumber(char from, const char * number, char to);
extern "C" char * P_addition(char base, const char * number1, const char * number2);
extern "C" char * P_subtraction(char base, const char * number1, const char * number2);
extern "C" char * P_multiplication(char base, const char * number1, const char * number2);
extern "C" char * P_division(char base, const char * number1, const char * number2);
extern "C" char * P_exponentation(char base, const char * number1, const char * number2);
extern "C" char * P_squareRoot(char base, const char * number);

class ProgrammerCalculatorState : public CalculatorState
{
public:
    ProgrammerCalculatorState(Ui::AssemblyCalculator * ui);
    void baseChanged(QObject * sender);

    virtual void clearDisplays() override;
    virtual void valueEntered(const QString& buttonPressed) override;
    virtual void operationEntered(const QString& buttonPressed) override;
    virtual void equalsPressed() override;
    virtual void backspacePressed() override;
    virtual void resetState() override;

    void squarePressed();

private:
    QString firstOperand = "";
    QString operationString = "";
    char base = 'b';

    void updateDisplays();
    void enableBinMode();
    void enableDecMode();
    void enableHexMode();
    void setDecButtonsActive(bool active);
    void setHexButtonsActive(bool active);
};

#endif // PROGRAMMERCALCULATORSTATE_H
