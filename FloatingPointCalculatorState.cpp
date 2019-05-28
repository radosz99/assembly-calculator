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

void FloatingPointCalculatorState::operationEntered(QPushButton * sender)
{
    QString operationPressed = sender->text();
    resultDisplayed = false;

    if (selectedOperation == Operation::NONE)
    {
        firstOperand = ui->F_displayMain->text().toDouble();

        if (operationPressed == "+")
            selectedOperation = Operation::ADD;
        else if (operationPressed == "-")
            selectedOperation = Operation::SUB;
        else if (operationPressed == "×")
            selectedOperation = Operation::MUL;
        else if (operationPressed == "÷")
            selectedOperation = Operation::DIV;
        else if (operationPressed == "√")
        {
            selectedOperation = Operation::SQRT;
            ui->F_displayUpper->setText(operationPressed + QString::number(firstOperand));
            ui->F_displayMain->setText("");
            equalsPressed();
            return;
        }
        else if (sender == ui->F_buttonExp)
        {
            selectedOperation = Operation::EXP;
            ui->F_buttonPoint->setEnabled(false);
            ui->F_displayUpper->setText(QString::number(firstOperand) + " ^");
            ui->F_displayMain->setText("");
            return;
        }

        ui->F_displayUpper->setText(QString::number(firstOperand) + " " + operationPressed);
        ui->F_displayMain->setText("");
    }
    else
    {
        if (operationPressed == "-")
            negatePressed();
    }
}

void FloatingPointCalculatorState::equalsPressed()
{
    if (selectedOperation != Operation::NONE)
    {
        double * result;
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
        else if (selectedOperation == Operation::EXP)
        {
            result = exponentation(firstOperand, (int) secondOperand);
            ui->F_buttonPoint->setEnabled(true);
        }

        ui->F_displayMain->setText(QString::number(*result));
        selectedOperation = Operation::NONE;
        firstOperand = *result;
        resultDisplayed = true;
    }
}

void FloatingPointCalculatorState::resetState()
{
    CalculatorState::resetState();
    firstOperand = 0.0;
    ui->F_buttonExp->setEnabled(true);
}
