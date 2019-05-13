#ifndef ASSEMBLYCALCULATOR_HPP
#define ASSEMBLYCALCULATOR_HPP

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

private:
    Ui::AssemblyCalculator *ui;
};

#endif // ASSEMBLYCALCULATOR_HPP
