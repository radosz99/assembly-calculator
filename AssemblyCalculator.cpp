#include "AssemblyCalculator.hpp"
#include "ui_AssemblyCalculator.h"
#include <QTextDocument>
#include <QPainter>
#include <QKeyEvent>

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

    fState = new FloatingPointCalculatorState(ui);
    pState = new ProgrammerCalculatorState(ui);
    activeState = fState;

    QTextDocument exponentationButtonText;
    exponentationButtonText.setHtml("<big>x<sup>y</sup></big>");
    QPixmap exponentationButtonPixmap(exponentationButtonText.size().width(), exponentationButtonText.size().height());
    exponentationButtonPixmap.fill(Qt::transparent);
    QPainter exponentationPainter(&exponentationButtonPixmap);
    exponentationButtonText.drawContents(&exponentationPainter, exponentationButtonPixmap.rect());
    QIcon exponentationButtonIcon(exponentationButtonPixmap);

    ui->F_buttonExp->setText("");
    ui->F_buttonExp->setIcon(exponentationButtonIcon);
    ui->F_buttonExp->setIconSize(exponentationButtonPixmap.rect().size());
    ui->P_buttonExp->setText("");
    ui->P_buttonExp->setIcon(exponentationButtonIcon);
    ui->P_buttonExp->setIconSize(exponentationButtonPixmap.rect().size());

    QTextDocument squareButtonText;
    squareButtonText.setHtml("<big>x<sup>2</sup></big>");
    QPixmap squareButtonPixmap(squareButtonText.size().width(), squareButtonText.size().height());
    squareButtonPixmap.fill(Qt::transparent);
    QPainter squarePainter(&squareButtonPixmap);
    squareButtonText.drawContents(&squarePainter, squareButtonPixmap.rect());
    QIcon squareButtonIcon(squareButtonPixmap);

    ui->P_buttonSquare->setText("");
    ui->P_buttonSquare->setIcon(squareButtonIcon);
    ui->P_buttonSquare->setIconSize(squareButtonPixmap.rect().size());

    // set floating calculator as default
    enableFloatingPointMode();

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
    connect(ui->P_buttonSub, SIGNAL(released()), this, SLOT(operationEntered()));
    connect(ui->P_buttonMul, SIGNAL(released()), this, SLOT(operationEntered()));
    connect(ui->P_buttonDiv, SIGNAL(released()), this, SLOT(operationEntered()));
    connect(ui->P_buttonExp, SIGNAL(released()), this, SLOT(operationEntered()));
    connect(ui->P_buttonSquare, SIGNAL(released()), this, SLOT(operationEntered()));
    connect(ui->P_buttonSqrt, SIGNAL(released()), this, SLOT(operationEntered()));
    connect(ui->P_buttonEquals, SIGNAL(released()), this, SLOT(equalsPressed()));
    connect(ui->P_buttonClear, SIGNAL(released()), this, SLOT(clearPressed()));
    connect(ui->P_buttonClearEntry, SIGNAL(released()), this, SLOT(backspacePressed()));

    connect(ui->P_labelBin, SIGNAL(clicked()), this, SLOT(baseChanged()));
    connect(ui->P_labelDec, SIGNAL(clicked()), this, SLOT(baseChanged()));
    connect(ui->P_labelHex, SIGNAL(clicked()), this, SLOT(baseChanged()));
    connect(ui->P_displayBin, SIGNAL(clicked()), this, SLOT(baseChanged()));
    connect(ui->P_displayDec, SIGNAL(clicked()), this, SLOT(baseChanged()));
    connect(ui->P_displayHex, SIGNAL(clicked()), this, SLOT(baseChanged()));

    connect(ui->buttonFloating, SIGNAL(released()), this, SLOT(enableFloatingPointMode()));
    connect(ui->buttonProgrammer, SIGNAL(released()), this, SLOT(enableProgrammerMode()));
}

AssemblyCalculator::~AssemblyCalculator()
{
    delete fState;
    delete pState;
    delete ui;
}

void AssemblyCalculator::baseChanged()
{
    pState->baseChanged((QObject *) sender());
}

void AssemblyCalculator::valueEntered()
{
    QPushButton * buttonPressed = (QPushButton *) sender();
    activeState->valueEntered(buttonPressed->text());
}

void AssemblyCalculator::valueEntered(const QString& value)
{
    activeState->valueEntered(value);
}

void AssemblyCalculator::enableFloatingPointMode()
{
    ui->stackedWidget->setCurrentWidget(ui->pageFloating);
    ui->buttonFloating->setStyleSheet(activeButtonStylesheet);
    ui->buttonProgrammer->setStyleSheet(inactiveButtonStylesheet);
    activeState = fState;
    activeState->resetState();
}

void AssemblyCalculator::enableProgrammerMode()
{
    ui->stackedWidget->setCurrentWidget(ui->pageProgrammer);
    ui->buttonProgrammer->setStyleSheet(activeButtonStylesheet);
    ui->buttonFloating->setStyleSheet(inactiveButtonStylesheet);
    activeState = pState;
    activeState->resetState();
}

void AssemblyCalculator::operationEntered()
{
    QPushButton * buttonPressed = (QPushButton *) sender();
    QString buttonValue = buttonPressed->text();

    if (buttonPressed == ui->F_buttonExp || buttonPressed == ui->P_buttonExp)
        buttonValue = "^";
    else if (buttonPressed == ui->P_buttonSquare)
    {
        // no square operation defined in FP State
        buttonValue = "^2";
        pState->operationEntered(buttonValue);
        return;
    }

    activeState->operationEntered(buttonValue);
}

void AssemblyCalculator::operationEntered(const QString& value)
{
    activeState->operationEntered(value);
}

void AssemblyCalculator::equalsPressed()
{
    activeState->equalsPressed();
}

void AssemblyCalculator::clearPressed()
{
    activeState->resetState();
}

void AssemblyCalculator::negatePressed()
{
    activeState->negatePressed();
}

void AssemblyCalculator::backspacePressed()
{
    activeState->backspacePressed();
}

void AssemblyCalculator::keyReleaseEvent(QKeyEvent * event)
{
    Qt::Key keyPressed = (Qt::Key) event->key();
    QString value;

    switch(keyPressed)
    {
    case Qt::Key_0:
        value = "0";
        break;

    case Qt::Key_1:
        value = "1";
        break;

    case Qt::Key_2:
        value = "2";
        break;

    case Qt::Key_3:
        value = "3";
        break;

    case Qt::Key_4:
        value = "4";
        break;

    case Qt::Key_5:
        value = "5";
        break;

    case Qt::Key_6:
        value = "6";
        break;

    case Qt::Key_7:
        value = "7";
        break;

    case Qt::Key_8:
        value = "8";
        break;

    case Qt::Key_9:
        value = "9";
        break;

    case Qt::Key_A:
        value = "A";
        break;

    case Qt::Key_B:
        value = "B";
        break;

    case Qt::Key_C:
        value = "C";
        break;

    case Qt::Key_D:
        value = "D";
        break;

    case Qt::Key_E:
        value = "E";
        break;

    case Qt::Key_F:
        value = "F";
        break;

    case Qt::Key_Comma:
    case Qt::Key_Period:
        value = ".";
        break;

    case Qt::Key_Plus:
        value = "+";
        break;

    case Qt::Key_Minus:
        value = "-";
        break;

    case Qt::Key_Asterisk:
        value = "×";
        break;

    case Qt::Key_Slash:
        value = "÷";
        break;

    case Qt::Key_Enter:
        value = "=";
        break;

    case Qt::Key_Backspace:
        value = "backspace";
        break;

    case Qt::Key_Escape:
        value = "clear";
        break;
    }

    if (value == "=")
        equalsPressed();
    else if (value == "backspace")
        backspacePressed();
    else if (value == "clear")
        clearPressed();
    else if (isValueKey(keyPressed))
        valueEntered(value);
    else if (isOperationKey(keyPressed))
        operationEntered(value);
}

bool AssemblyCalculator::isValueKey(Qt::Key key) const
{
    return (key == Qt::Key_0 ||
            key == Qt::Key_1 ||
            key == Qt::Key_2 ||
            key == Qt::Key_3 ||
            key == Qt::Key_4 ||
            key == Qt::Key_5 ||
            key == Qt::Key_6 ||
            key == Qt::Key_7 ||
            key == Qt::Key_8 ||
            key == Qt::Key_9 ||
            key == Qt::Key_A ||
            key == Qt::Key_B ||
            key == Qt::Key_C ||
            key == Qt::Key_D ||
            key == Qt::Key_E ||
            key == Qt::Key_F ||
            key == Qt::Key_Comma ||
            key == Qt::Key_Period);
}

bool AssemblyCalculator::isOperationKey(Qt::Key key) const
{
    return (key == Qt::Key_Plus ||
            key == Qt::Key_Minus ||
            key == Qt::Key_Asterisk ||
            key == Qt::Key_Slash);
}
