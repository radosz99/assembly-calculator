#ifndef ASSEMBLYCALCULATOR_HPP
#define ASSEMBLYCALCULATOR_HPP

#include "Operation.hpp"
#include "FloatingPointCalculatorState.hpp"
#include "ProgrammerCalculatorState.hpp"
#include <QMainWindow>

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

    const int marginSize = 3;
    const QString inactiveButtonStylesheet = "QPushButton { color: #cdcdcd; border: 0; background: none; }";
    const QString activeButtonStylesheet = "QPushButton { color: #191919; border: 0; background: none; }";
};

#endif // ASSEMBLYCALCULATOR_HPP
