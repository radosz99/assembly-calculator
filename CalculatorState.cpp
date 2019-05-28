#include "CalculatorState.hpp"

CalculatorState::CalculatorState(Ui::AssemblyCalculator * ui) : ui(ui)
{

}

void CalculatorState::resetState()
{
    clearDisplays();
    selectedOperation = Operation::NONE;
    resultDisplayed = false;
}

void CalculatorState::negatePressed()
{
    QString displayedNumber = ui->F_displayMain->text();

    if (displayedNumber.contains("-"))
        ui->F_displayMain->setText(displayedNumber.mid(1, displayedNumber.length() - 1));
    else
        ui->F_displayMain->setText("-" + displayedNumber);
}
