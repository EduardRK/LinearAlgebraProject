#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "architecture.hpp"
#include "variables.hpp"

using namespace algb::libr;
using namespace algb::vrbl;

int main(int argc, char **argv)
{
  using namespace algb::arch;

  Database<std::string, std::vector<double>> db;
  db.setVariable("b", std::vector<std::string>());

  std::vector<float> f;

  try
  {
    db.getVariable(f, "b");
  }
  catch (const std::invalid_argument &e)
  {
    std::cout << e.what();
  }

  std::cout << f.at(1);

  system("pause");
  return 0;
}