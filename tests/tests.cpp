#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

extern "C" const char * addition(char, const char *, const char *);

TEST_CASE("PERFORMING ADDITION")
{
  REQUIRE(strcmp(addition('b', "100\n", "1\n"), "101\n\r") == 0);
}