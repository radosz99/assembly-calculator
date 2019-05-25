#include <iostream>

extern "C" const char * addition(char, const char *, const char *);

int main(int argc, char const *argv[])
{
  std::cout << addition('b', "100\n", "1000\n");
  return 0;
}
