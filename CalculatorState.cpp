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
