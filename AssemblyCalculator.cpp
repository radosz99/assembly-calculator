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

    fState = new FloatingPointCalculatorState(ui);
    pState = new ProgrammerCalculatorState(ui);
    activeState = fState;

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
    connect(ui->P_buttonClear, SIGNAL(released()), this, SLOT(clearPressed()));

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
    activeState->valueEntered((QPushButton *) sender());
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
    activeState->operationEntered(buttonPressed);
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
