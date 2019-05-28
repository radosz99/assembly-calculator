#ifndef ASSEMBLYCALCULATOR_HPP
#define ASSEMBLYCALCULATOR_HPP

#include "Operation.hpp"
#include "CalculatorMode.hpp"
#include "FloatingPointCalculatorState.hpp"
#include "ProgrammerCalculatorState.hpp"
#include <QMainWindow>
#include <QLineEdit>

namespace Ui {
class AssemblyCalculator;
}

class AssemblyCalculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit AssemblyCalculator(QWidget *parent = 0);
    ~AssemblyCalculator();

private slots:
//    void on_buttonFloating_clicked();
//    void on_buttonProgrammer_clicked();
    void valueEntered();
    void operationEntered();
    void equalsPressed();
    void clearPressed();
    void negatePressed();
    void baseChanged();
    void enableFloatingPointMode();
    void enableProgrammerMode();

private:
    Ui::AssemblyCalculator *ui;

    CalculatorState * activeState;
    FloatingPointCalculatorState * fState;
    ProgrammerCalculatorState * pState;

    bool F_resultDisplayed = false;
    bool P_resultDisplayed = false;
    double F_firstOperand;
    QString P_firstOperand = "";
    Operation selectedOperation = Operation::NONE;
    CalculatorMode calculatorMode = CalculatorMode::FLOATING;
    char base = 'b';

    const int marginSize = 3;
    const QString inactiveButtonStylesheet = "QPushButton { color: #cdcdcd; border: 0; background: none; }";
    const QString activeButtonStylesheet = "QPushButton { color: #191919; border: 0; background: none; }";
};

#endif // ASSEMBLYCALCULATOR_HPP
