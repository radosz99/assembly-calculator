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
    void valueEntered(const QString& value);
    void operationEntered();
    void operationEntered(const QString& value);
    void equalsPressed();
    void clearPressed();
    void negatePressed();
    void backspacePressed();
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

    void keyReleaseEvent(QKeyEvent * event);
    bool isValueKey(Qt::Key key) const;
    bool isOperationKey(Qt::Key key) const;
};

#endif // ASSEMBLYCALCULATOR_HPP
