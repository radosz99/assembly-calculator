#include "AssemblyCalculator.hpp"
#include "ui_AssemblyCalculator.h"

AssemblyCalculator::AssemblyCalculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssemblyCalculator)
{
    ui->setupUi(this);
}

AssemblyCalculator::~AssemblyCalculator()
{
    delete ui;
}
