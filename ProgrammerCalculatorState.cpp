#include "ProgrammerCalculatorState.hpp"

ProgrammerCalculatorState::ProgrammerCalculatorState(Ui::AssemblyCalculator * ui) : CalculatorState(ui)
{
    ui->P_labelBin->setActive(true);
    ui->P_displayBin->setActive(true);
}

void ProgrammerCalculatorState::clearDisplays()
{
    ui->P_displayBin->setText("");
    ui->P_displayDec->setText("");
    ui->P_displayHex->setText("");
    ui->P_displayMain->setText("");
    ui->P_displayUpper->setText("");
}

void ProgrammerCalculatorState::valueEntered(const QString& buttonPressed)
{
    if (buttonPressed == ".")
        return;
    if (base == 'b' && (isDecValue(buttonPressed) || isHexValue(buttonPressed)))
        return;
    if (base == 'd' && (isHexValue(buttonPressed)))
        return;

    if (resultDisplayed)
    {
        firstOperand = "";
        ui->P_displayMain->setText("");
        ui->P_displayUpper->setText("");
        resultDisplayed = false;
    }

    QString displayedNumber = ui->P_displayMain->text();

    QString updatedText = displayedNumber + buttonPressed;
    ui->P_displayMain->setText(updatedText);

    updateDisplays();
}

void ProgrammerCalculatorState::operationEntered(const QString& buttonPressed)
{
    resultDisplayed = false;

    if (selectedOperation == Operation::NONE)
    {
        firstOperand = ui->P_displayMain->text();
        if (firstOperand.length() == 0)
            firstOperand = "0";

        if (buttonPressed == "+")
        {
            selectedOperation = Operation::ADD;
            operationString = "+";
        }
        else if (buttonPressed == "-")
        {
            selectedOperation = Operation::SUB;
            operationString = "-";
        }
        else if (buttonPressed == "×")
        {
            selectedOperation = Operation::MUL;
            operationString = "×";
        }
        else if (buttonPressed == "÷")
        {
            selectedOperation = Operation::DIV;
            operationString = "÷";
        }
        else if (buttonPressed == "√")
        {
            selectedOperation = Operation::SQRT;
            operationString = "√";
            ui->P_displayUpper->setText(buttonPressed + firstOperand);
            ui->P_displayMain->setText("");
            equalsPressed();
            return;
        }
        else if (buttonPressed == "^")
        {
            selectedOperation = Operation::EXP;
            operationString = "^";
            ui->P_buttonPoint->setEnabled(false);
            ui->P_displayUpper->setText(firstOperand + " ^");
            ui->P_displayMain->setText("");
            return;
        }

        ui->P_displayUpper->setText(firstOperand + " " + buttonPressed);
        ui->P_displayMain->setText("");
    }
}

void ProgrammerCalculatorState::equalsPressed()
{
    if (selectedOperation != Operation::NONE)
    {
        char * result;
        QString secondOperand = ui->P_displayMain->text();
        QString operationString = ui->P_displayUpper->text();
        operationString += " " + ui->P_displayMain->text();

        firstOperand += "\n";
        secondOperand += "\n";

        ui->P_displayUpper->setText(operationString);

        if (selectedOperation == Operation::ADD)
            result = P_addition(base, firstOperand.toStdString().c_str(), secondOperand.toStdString().c_str());
        else if (selectedOperation == Operation::SUB)
            result = P_subtraction(base, firstOperand.toStdString().c_str(), secondOperand.toStdString().c_str());
        else if (selectedOperation == Operation::MUL)
            result = P_multiplication(base, firstOperand.toStdString().c_str(), secondOperand.toStdString().c_str());
        else if (selectedOperation == Operation::DIV)
            result = P_division(base, firstOperand.toStdString().c_str(), secondOperand.toStdString().c_str());
        else if (selectedOperation == Operation::EXP)
            result = P_exponentation(base, firstOperand.toStdString().c_str(), secondOperand.toStdString().c_str());
        else if (selectedOperation == Operation::SQRT)
            result = P_squareRoot(base, firstOperand.toStdString().c_str());

        ui->P_displayMain->setText(result);
        firstOperand = result;
        selectedOperation = Operation::NONE;
        resultDisplayed = true;
        updateDisplays();
    }
}

void ProgrammerCalculatorState::backspacePressed()
{
    QString displayedValue = ui->P_displayMain->text();
    displayedValue.chop(1);
    ui->P_displayMain->setText(displayedValue);

    updateDisplays();
}

void ProgrammerCalculatorState::resetState()
{
    CalculatorState::resetState();
    firstOperand = "";
    ui->P_buttonExp->setEnabled(true);
}

void ProgrammerCalculatorState::updateDisplays()
{
    const char * number = ui->P_displayMain->text().toStdString().c_str();

    QString binNumber(convertNumber(base, number, 'b'));
    ui->P_displayBin->setText(binNumber);
    QString decNumber(convertNumber(base, number, 'd'));
    ui->P_displayDec->setText(decNumber);
    QString hexNumber(convertNumber(base, number, 'x'));
    ui->P_displayHex->setText(hexNumber.toUpper());
}

void ProgrammerCalculatorState::baseChanged(QObject * sender)
{
    QString selectedBase = sender->objectName().toLower();
    char newBase;
    const char * number = ui->P_displayMain->text().toStdString().c_str();

    if (selectedBase.contains("bin"))
    {
        enableBinMode();
        newBase = 'b';
    }
    else if (selectedBase.contains("dec"))
    {
        enableDecMode();
        newBase = 'd';
    }
    else if (selectedBase.contains("hex"))
    {
        enableHexMode();
        newBase = 'x';
    }

    ui->P_displayMain->setText(convertNumber(base, number, newBase));

    if (firstOperand.length() > 0)
    {
        const char * upperString = firstOperand.toStdString().c_str();
        ui->P_displayUpper->setText(convertNumber(base, upperString, newBase));
        firstOperand = ui->P_displayUpper->text();
        ui->P_displayUpper->setText(ui->P_displayUpper->text().toUpper() + " " + operationString);
    }

    base = newBase;
}

void ProgrammerCalculatorState::enableBinMode()
{
    ui->P_labelBin->setActive(true);
    ui->P_labelDec->setActive(false);
    ui->P_labelHex->setActive(false);
    ui->P_displayBin->setActive(true);
    ui->P_displayDec->setActive(false);
    ui->P_displayHex->setActive(false);
    setDecButtonsActive(false);
    setHexButtonsActive(false);
}

void ProgrammerCalculatorState::enableDecMode()
{
    ui->P_labelBin->setActive(false);
    ui->P_labelDec->setActive(true);
    ui->P_labelHex->setActive(false);
    ui->P_displayBin->setActive(false);
    ui->P_displayDec->setActive(true);
    ui->P_displayHex->setActive(false);
    setDecButtonsActive(true);
    setHexButtonsActive(false);
}

void ProgrammerCalculatorState::enableHexMode()
{
    ui->P_labelBin->setActive(false);
    ui->P_labelDec->setActive(false);
    ui->P_labelHex->setActive(true);
    ui->P_displayBin->setActive(false);
    ui->P_displayDec->setActive(false);
    ui->P_displayHex->setActive(true);
    setDecButtonsActive(true);
    setHexButtonsActive(true);
}

void ProgrammerCalculatorState::setDecButtonsActive(bool active)
{
    ui->P_button2->setEnabled(active);
    ui->P_button3->setEnabled(active);
    ui->P_button4->setEnabled(active);
    ui->P_button5->setEnabled(active);
    ui->P_button6->setEnabled(active);
    ui->P_button7->setEnabled(active);
    ui->P_button8->setEnabled(active);
    ui->P_button9->setEnabled(active);
}

void ProgrammerCalculatorState::setHexButtonsActive(bool active)
{
    ui->P_buttonA->setEnabled(active);
    ui->P_buttonB->setEnabled(active);
    ui->P_buttonC->setEnabled(active);
    ui->P_buttonD->setEnabled(active);
    ui->P_buttonE->setEnabled(active);
    ui->P_buttonF->setEnabled(active);
}
