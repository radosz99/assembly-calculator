#include "FloatingPointCalculatorState.hpp"
#include "ui_AssemblyCalculator.h"
#include <QPushButton>

FloatingPointCalculatorState::FloatingPointCalculatorState(Ui::AssemblyCalculator * ui) : CalculatorState(ui)
{

}

void FloatingPointCalculatorState::clearDisplays()
{
    ui->F_displayMain->setText("");
    ui->F_displayUpper->setText("");
}

void FloatingPointCalculatorState::valueEntered(QPushButton * sender)
{
    QString valuePressed = sender->text();

    if (resultDisplayed)
    {
        clearDisplays();
        resultDisplayed = false;
    }

    QString displayedNumber = ui->F_displayMain->text();

    if (valuePressed == ".")
    {
        // already one point in value
        if (displayedNumber.contains("."))
            return;

        // point pressed first
        if (displayedNumber.length() == 0)
            displayedNumber = "0";
    }

    QString updatedText = displayedNumber + valuePressed;
    ui->F_displayMain->setText(updatedText);
}

void FloatingPointCalculatorState::resetState()
{
    CalculatorState::resetState();
    firstOperand = 0.0;
    ui->F_buttonExp->setEnabled(true);
}
