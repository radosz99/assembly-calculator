#include "AssemblyCalculator.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AssemblyCalculator w;
    w.show();

    return a.exec();
}
