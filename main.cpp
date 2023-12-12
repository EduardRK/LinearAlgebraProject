#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <optional>

#include "architecture.hpp"
#include "variables.hpp"

using namespace algb::libr;
using namespace algb::vrbl;

std::optional<int *> intConv(const lines_type &vars)
{
  ;
  return std::optional(new int(42));
}

std::optional<std::string *> stringConv(const lines_type &vars)
{
  return std::optional(new std::string("0420"));
}

int main(int argc, char **argv)
{
  using namespace algb::arch;
  algb::vrbl::Database<int, std::string> db(intConv, stringConv);


  system("pause");
  return 0;
}