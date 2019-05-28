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

void ProgrammerCalculatorState::valueEntered(QPushButton * sender)
{
    QString valuePressed = sender->text();

    if (resultDisplayed)
    {
        firstOperand = "";
        ui->P_displayMain->setText("");
        ui->P_displayUpper->setText("");
        resultDisplayed = false;
    }

    QString displayedNumber = ui->P_displayMain->text();

    QString updatedText = displayedNumber + valuePressed;
    ui->P_displayMain->setText(updatedText);

    const char * number = updatedText.toStdString().c_str();

    QString binNumber(convertNumber(base, number, 'b'));
    ui->P_displayBin->setText(binNumber);
    QString decNumber(convertNumber(base, number, 'd'));
    ui->P_displayDec->setText(decNumber);
    QString hexNumber(convertNumber(base, number, 'x'));
    ui->P_displayHex->setText(hexNumber.toUpper());
}

void ProgrammerCalculatorState::operationEntered(QPushButton * sender)
{

}

void ProgrammerCalculatorState::equalsPressed()
{

}

void ProgrammerCalculatorState::resetState()
{
    CalculatorState::resetState();
    firstOperand = "";
    ui->P_buttonExp->setEnabled(true);
}

void ProgrammerCalculatorState::baseChanged(QObject * sender)
{
    QString selectedBase = sender->objectName().toLower();
    const char * number = ui->P_displayMain->text().toStdString().c_str();

    if (selectedBase.contains("bin"))
    {
        enableBinMode();
        ui->P_displayMain->setText(convertNumber(base, number, 'b'));
        base = 'b';
    }
    else if (selectedBase.contains("dec"))
    {
        enableDecMode();
        ui->P_displayMain->setText(convertNumber(base, number, 'd'));
        base = 'd';
    }
    else if (selectedBase.contains("hex"))
    {
        enableHexMode();
        QString hexNumber(convertNumber(base, number, 'x'));
        ui->P_displayMain->setText(hexNumber.toUpper());
        base = 'x';
    }
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
