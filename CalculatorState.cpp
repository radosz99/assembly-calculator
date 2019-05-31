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

bool CalculatorState::isDecValue(const QString& value) const
{
   return (value == "2" ||
           value == "3" ||
           value == "4" ||
           value == "5" ||
           value == "6" ||
           value == "7" ||
           value == "8" ||
           value == "9");
}

bool CalculatorState::isHexValue(const QString& value) const
{
    return (value == "A" ||
            value == "B" ||
            value == "C" ||
            value == "D" ||
            value == "E" ||
            value == "F");
}
