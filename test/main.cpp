#include <iostream>

extern "C" char * P_addition(char base, const char * number1, const char * number2);
extern "C" char * P_subtraction(char base, const char * number1, const char * number2);
// extern "C" char * P_multiplication(char base, const char * number1, const char * number2);
// extern "C" char * P_division(char base, const char * number1, const char * number2);
// extern "C" char * P_exponentation(char base, const char * number1, const char * number2);
// extern "C" char * P_squareRoot(char base, const char * number);
// extern "C" double addition(double, double);
// extern "C" double subtraction(double, double);
// extern "C" double multiplication(double, double);
// extern "C" double division(double, double);
// extern "C" double exponentation(double, int);
// extern "C" double * log(double);
// extern "C" double * sin(double);
// extern "C" double * cos(double);
// extern "C" double * tan(double);


int main(int argc, char const *argv[])
{
    char * result = P_addition('b', "1000\n", "1\n");

    std::cout << result << '\n';
    
    return 0;
}
