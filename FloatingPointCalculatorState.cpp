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

void FloatingPointCalculatorState::valueEntered(const QString& buttonPressed)
{
    if (isHexValue(buttonPressed))
        return;

    if (resultDisplayed)
    {
        clearDisplays();
        resultDisplayed = false;
    }

    QString displayedNumber = ui->F_displayMain->text();

    if (buttonPressed == ".")
    {
        // already one point in value
        if (displayedNumber.contains("."))
            return;

        // point pressed first
        if (displayedNumber.length() == 0)
            displayedNumber = "0";
    }

    QString updatedText = displayedNumber + buttonPressed;
    ui->F_displayMain->setText(updatedText);
}

void FloatingPointCalculatorState::operationEntered(const QString& buttonPressed)
{
    resultDisplayed = false;

    if (selectedOperation == Operation::NONE)
    {
        firstOperand = ui->F_displayMain->text().toDouble();

        if (buttonPressed == "+")
            selectedOperation = Operation::ADD;
        else if (buttonPressed == "-")
            selectedOperation = Operation::SUB;
        else if (buttonPressed == "×")
            selectedOperation = Operation::MUL;
        else if (buttonPressed == "÷")
            selectedOperation = Operation::DIV;
        else if (buttonPressed == "^")
        {
            selectedOperation = Operation::EXP;
            ui->F_buttonPoint->setEnabled(false);
            ui->F_displayUpper->setText(QString::number(firstOperand) + " ^");
            ui->F_displayMain->setText("");
            return;
        }
        else if (buttonPressed == "√")
        {
            selectedOperation = Operation::SQRT;
            ui->F_displayUpper->setText(buttonPressed + QString::number(firstOperand));
            ui->F_displayMain->setText("");
            equalsPressed();
            return;
        }
        else if (buttonPressed == "log" ||
                 buttonPressed == "sin" ||
                 buttonPressed == "cos" ||
                 buttonPressed == "tan")
        {
            if (buttonPressed == "√")
                selectedOperation = Operation::SQRT;
            else if (buttonPressed == "log")
                selectedOperation = Operation::LOG;
            else if (buttonPressed == "sin")
                selectedOperation = Operation::SIN;
            else if (buttonPressed == "cos")
                selectedOperation = Operation::COS;
            else if (buttonPressed == "tan")
                selectedOperation = Operation::TAN;

            ui->F_displayUpper->setText(buttonPressed + "(" + QString::number(firstOperand) + ")");
            ui->F_displayMain->setText("");
            equalsPressed();
            return;
        }

        ui->F_displayUpper->setText(QString::number(firstOperand) + " " + buttonPressed);
        ui->F_displayMain->setText("");
    }
    else if (selectedOperation != Operation::NONE)
    {
        equalsPressed();
        operationEntered(buttonPressed);
    }
    else if (buttonPressed == "-")
            negatePressed();
}

void FloatingPointCalculatorState::backspacePressed()
{
    QString displayedValue = ui->F_displayMain->text();
    displayedValue.chop(1);
    ui->F_displayMain->setText(displayedValue);
}

void FloatingPointCalculatorState::equalsPressed()
{
    if (selectedOperation != Operation::NONE)
    {
        double result;
        double secondOperand = ui->F_displayMain->text().toDouble();
        QString operationString = ui->F_displayUpper->text();
        operationString += " " + ui->F_displayMain->text();

        ui->F_displayUpper->setText(operationString);

        if (selectedOperation == Operation::ADD)
            result = addition(firstOperand, secondOperand);
        else if (selectedOperation == Operation::SUB)
            result = subtraction(firstOperand, secondOperand);
        else if (selectedOperation == Operation::MUL)
            result = multiplication(firstOperand, secondOperand);
        else if (selectedOperation == Operation::DIV)
            result = division(firstOperand, secondOperand);
        else if (selectedOperation == Operation::SQRT)
            result = squareRoot(firstOperand);
        else if (selectedOperation == Operation::LOG)
            result = log(firstOperand);
        else if (selectedOperation == Operation::SIN)
            result = sin(firstOperand);
        else if (selectedOperation == Operation::COS)
            result = cos(firstOperand);
        else if (selectedOperation == Operation::TAN)
            result = tan(firstOperand);
        else if (selectedOperation == Operation::EXP)
        {
            result = exponentation(firstOperand, (int) secondOperand);
            ui->F_buttonPoint->setEnabled(true);
        }

        ui->F_displayMain->setText(QString::number(result));
        selectedOperation = Operation::NONE;
        firstOperand = result;
        resultDisplayed = true;
    }
}

void FloatingPointCalculatorState::resetState()
{
    CalculatorState::resetState();
    firstOperand = 0.0;
    ui->F_buttonExp->setEnabled(true);
}
