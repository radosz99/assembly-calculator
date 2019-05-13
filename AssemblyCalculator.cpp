#include "AssemblyCalculator.hpp"
#include "ui_AssemblyCalculator.h"
#include <QTextDocument>
#include <QPainter>

AssemblyCalculator::AssemblyCalculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssemblyCalculator)
{
    ui->setupUi(this);

    ui->centralWidget->layout()->setMargin(0);
    ui->centralWidget->layout()->setSpacing(0);
    ui->pageFloating->layout()->setMargin(marginSize);
    ui->pageFloating->layout()->setSpacing(marginSize);
    ui->pageProgrammer->layout()->setMargin(marginSize);
    ui->pageProgrammer->layout()->setSpacing(marginSize);

    QTextDocument exponentationButtonText;
    exponentationButtonText.setHtml("<big>x<sup>y</sup></big>");

    QPixmap exponentationButtonPixmap(exponentationButtonText.size().width(), exponentationButtonText.size().height());
    exponentationButtonPixmap.fill(Qt::transparent);
    QPainter painter(&exponentationButtonPixmap);
    exponentationButtonText.drawContents(&painter, exponentationButtonPixmap.rect());
    QIcon buttonIcon(exponentationButtonPixmap);

    ui->F_buttonExp->setText("");
    ui->F_buttonExp->setIcon(buttonIcon);
    ui->F_buttonExp->setIconSize(exponentationButtonPixmap.rect().size());
    ui->P_buttonExp->setText("");
    ui->P_buttonExp->setIcon(buttonIcon);
    ui->P_buttonExp->setIconSize(exponentationButtonPixmap.rect().size());

    // set floating calculator as default
    on_buttonFloating_clicked();

    for (int i = 0; i < 10; i++)
    {
        QString F_buttonName = "F_button" + QString::number(i);
        QPushButton * F_numberButton = AssemblyCalculator::findChild<QPushButton *>(F_buttonName);
        connect(F_numberButton, SIGNAL(released()), this, SLOT(valueEntered()));

        QString P_buttonName = "P_button" + QString::number(i);
        QPushButton * P_numberButton = AssemblyCalculator::findChild<QPushButton *>(P_buttonName);
        connect(P_numberButton, SIGNAL(released()), this, SLOT(valueEntered()));
    }

    connect(ui->P_buttonA, SIGNAL(released()), this, SLOT(valueEntered()));
    connect(ui->P_buttonB, SIGNAL(released()), this, SLOT(valueEntered()));
    connect(ui->P_buttonC, SIGNAL(released()), this, SLOT(valueEntered()));
    connect(ui->P_buttonD, SIGNAL(released()), this, SLOT(valueEntered()));
    connect(ui->P_buttonE, SIGNAL(released()), this, SLOT(valueEntered()));
    connect(ui->P_buttonF, SIGNAL(released()), this, SLOT(valueEntered()));

    connect(ui->F_buttonPoint, SIGNAL(released()), this, SLOT(valueEntered()));
    connect(ui->F_buttonAdd, SIGNAL(released()), this, SLOT(operationEntered()));
    connect(ui->F_buttonSub, SIGNAL(released()), this, SLOT(operationEntered()));
    connect(ui->F_buttonMul, SIGNAL(released()), this, SLOT(operationEntered()));
    connect(ui->F_buttonDiv, SIGNAL(released()), this, SLOT(operationEntered()));
    connect(ui->F_buttonExp, SIGNAL(released()), this, SLOT(operationEntered()));
    connect(ui->F_buttonSqrt, SIGNAL(released()), this, SLOT(operationEntered()));
    connect(ui->F_buttonEquals, SIGNAL(released()), this, SLOT(equalsPressed()));
    connect(ui->F_buttonClear, SIGNAL(released()), this, SLOT(clearPressed()));
    connect(ui->F_buttonNeg, SIGNAL(released()), this, SLOT(negatePressed()));

    connect(ui->P_buttonAdd, SIGNAL(released()), this, SLOT(operationEntered()));
    connect(ui->P_buttonClear, SIGNAL(released()), this, SLOT(clearPressed()));

    connect(ui->P_labelBin, SIGNAL(clicked()), this, SLOT(baseChanged()));
    connect(ui->P_labelDec, SIGNAL(clicked()), this, SLOT(baseChanged()));
    connect(ui->P_labelHex, SIGNAL(clicked()), this, SLOT(baseChanged()));


    activeDisplayMain = ui->F_displayMain;
    activeDisplayUpper = ui->F_displayUpper;
    ui->P_labelBin->setActive(true);
    ui->P_displayBin->setActive(true);
}

AssemblyCalculator::~AssemblyCalculator()
{
    delete ui;
}

void AssemblyCalculator::baseChanged()
{
    QObject * selectedBaseButton = sender();
    QString selectedBase = selectedBaseButton->objectName().toLower();
    const char * number = ui->P_displayMain->text().toStdString().c_str();

    if (selectedBase.contains("bin"))
    {
        ui->P_labelBin->setActive(true);
        ui->P_labelDec->setActive(false);
        ui->P_labelHex->setActive(false);
        ui->P_displayBin->setActive(true);
        ui->P_displayDec->setActive(false);
        ui->P_displayHex->setActive(false);
        setDecButtonsActive(false);
        setHexButtonsActive(false);

        ui->P_displayMain->setText(convertNumber(base, number, 'b'));

        base = 'b';
    }
    else if (selectedBase.contains("dec"))
    {
        ui->P_labelBin->setActive(false);
        ui->P_labelDec->setActive(true);
        ui->P_labelHex->setActive(false);
        ui->P_displayBin->setActive(false);
        ui->P_displayDec->setActive(true);
        ui->P_displayHex->setActive(false);
        setDecButtonsActive(true);
        setHexButtonsActive(false);

        ui->P_displayMain->setText(convertNumber(base, number, 'd'));

        base = 'd';
    }
    else if (selectedBase.contains("hex"))
    {
        ui->P_labelBin->setActive(false);
        ui->P_labelDec->setActive(false);
        ui->P_labelHex->setActive(true);
        ui->P_displayBin->setActive(false);
        ui->P_displayDec->setActive(false);
        ui->P_displayHex->setActive(true);
        setDecButtonsActive(true);
        setHexButtonsActive(true);

        QString hexNumber(convertNumber(base, number, 'x'));
        ui->P_displayMain->setText(hexNumber.toUpper());

        base = 'x';
    }
}

void AssemblyCalculator::setDecButtonsActive(bool active)
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

void AssemblyCalculator::setHexButtonsActive(bool active)
{
    ui->P_buttonA->setEnabled(active);
    ui->P_buttonB->setEnabled(active);
    ui->P_buttonC->setEnabled(active);
    ui->P_buttonD->setEnabled(active);
    ui->P_buttonE->setEnabled(active);
    ui->P_buttonF->setEnabled(active);
}

void AssemblyCalculator::on_buttonFloating_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFloating);
    ui->buttonFloating->setStyleSheet(activeButtonStylesheet);
    ui->buttonProgrammer->setStyleSheet(inactiveButtonStylesheet);
    calculatorMode = CalculatorMode::FLOATING;
}

void AssemblyCalculator::on_buttonProgrammer_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageProgrammer);
    ui->buttonProgrammer->setStyleSheet(activeButtonStylesheet);
    ui->buttonFloating->setStyleSheet(inactiveButtonStylesheet);
    calculatorMode = CalculatorMode::PROGRAMMER;
}

void AssemblyCalculator::valueEntered()
{
    QPushButton * buttonPressed = (QPushButton *) sender();
    QString valuePressed = buttonPressed->text();

    if (calculatorMode == CalculatorMode::FLOATING)
        floatingValueEntered(valuePressed);
    else if (calculatorMode == CalculatorMode::PROGRAMMER)
        programmerValueEntered(valuePressed);
}

void AssemblyCalculator::floatingValueEntered(QString valuePressed)
{
    if (F_resultDisplayed)
    {
        F_firstOperand = 0.0;
        ui->F_displayMain->setText("");
        ui->F_displayUpper->setText("");
        F_resultDisplayed = false;
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

void AssemblyCalculator::programmerValueEntered(QString valuePressed)
{
    if (P_resultDisplayed)
    {
        P_firstOperand = "";
        ui->P_displayMain->setText("");
        ui->P_displayUpper->setText("");
        P_resultDisplayed = false;
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

void AssemblyCalculator::operationEntered()
{
    QPushButton * buttonPressed = (QPushButton *) sender();
    QString operationPressed = buttonPressed->text();

    if (calculatorMode == CalculatorMode::FLOATING)
        F_resultDisplayed = false;
    else if (calculatorMode == CalculatorMode::PROGRAMMER)
        P_resultDisplayed = false;

    if (selectedOperation == Operation::NONE)
    {
        if (calculatorMode == CalculatorMode::FLOATING)
            F_firstOperand = ui->F_displayMain->text().toDouble();
        else if (calculatorMode == CalculatorMode::PROGRAMMER)
            P_firstOperand = ui->P_displayMain->text();

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

            if (calculatorMode == CalculatorMode::FLOATING)
            {
                ui->F_displayUpper->setText(operationPressed + QString::number(F_firstOperand));
                ui->F_displayMain->setText("");
            }
            equalsPressed();
            return;
        }
        else if (buttonPressed == ui->F_buttonExp)
        {
            selectedOperation = Operation::EXP;

            if (calculatorMode == CalculatorMode::FLOATING)
            {
                ui->F_buttonPoint->setEnabled(false);
                ui->F_displayUpper->setText(QString::number(F_firstOperand) + " ^");
                ui->F_displayMain->setText("");
            }
            return;
        }

        if (calculatorMode == CalculatorMode::FLOATING)
        {
            ui->F_displayUpper->setText(QString::number(F_firstOperand) + " " + operationPressed);
            ui->F_displayMain->setText("");
        }
        else if (calculatorMode == CalculatorMode::PROGRAMMER)
        {
            ui->P_displayUpper->setText(P_firstOperand + " " + operationPressed);
            ui->P_displayMain->setText("");
        }
    }
    else
    {
        if (operationPressed == "-")
            negatePressed();
    }
}

void AssemblyCalculator::equalsPressed()
{
    if (selectedOperation != Operation::NONE)
    {
        double * result;
        double F_secondOperand = ui->F_displayMain->text().toDouble();
        QString operationString = ui->F_displayUpper->text();
        operationString += " " + ui->F_displayMain->text();

        ui->F_displayUpper->setText(operationString);

        if (selectedOperation == Operation::ADD)
            result = addition(F_firstOperand, F_secondOperand);
        else if (selectedOperation == Operation::SUB)
            result = subtraction(F_firstOperand, F_secondOperand);
        else if (selectedOperation == Operation::MUL)
            result = multiplication(F_firstOperand, F_secondOperand);
        else if (selectedOperation == Operation::DIV)
            result = division(F_firstOperand, F_secondOperand);
        else if (selectedOperation == Operation::SQRT)
            result = squareRoot(F_firstOperand);
        else if (selectedOperation == Operation::EXP)
        {
            result = exponentation(F_firstOperand, (int) F_secondOperand);
            ui->F_buttonPoint->setEnabled(true);
        }

        ui->F_displayMain->setText(QString::number(*result));
        selectedOperation = Operation::NONE;
        F_firstOperand = *result;
        F_resultDisplayed = true;
    }
}

void AssemblyCalculator::clearPressed()
{
    if (calculatorMode == CalculatorMode::FLOATING)
    {
        F_firstOperand = 0.0;
        selectedOperation = Operation::NONE;
        ui->F_displayMain->setText("");
        ui->F_displayUpper->setText("");
        ui->F_buttonExp->setEnabled(true);
    }
    else if (calculatorMode == CalculatorMode::PROGRAMMER)
    {
        P_firstOperand = "";
        ui->P_displayBin->setText("");
        ui->P_displayDec->setText("");
        ui->P_displayHex->setText("");
        ui->P_displayUpper->setText("");
        ui->P_displayMain->setText("");
    }
}

void AssemblyCalculator::negatePressed()
{
    QString displayedNumber = ui->F_displayMain->text();

    if (displayedNumber.contains("-"))
        ui->F_displayMain->setText(displayedNumber.mid(1, displayedNumber.length() - 1));
    else
        ui->F_displayMain->setText("-" + displayedNumber);
}
