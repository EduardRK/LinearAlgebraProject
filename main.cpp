#include <iostream>
#include <string>

#include "Validator.hpp"
#include "architecture.hpp"
#include "Writer.hpp"
#include "Reader.hpp"
#include "Parser.hpp"
#include "Operations.hpp"

using namespace algb::libr;

void print(std::vector<float> vect)
{
  for (float &element : vect)
  {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

void print(std::vector<std::string> vect)
{
  for (std::string &element : vect)
  {
    std::cout << element << std::endl;
  }
  std::cout << std::endl;
}

int main(int argc, char **argv)
{
  algb::libr::CommandValidator validator(' ');
  validator.generateRegex();

  std::string command = "SET v1 CROSS v2 v3";
  std::cout << validator.isValid(command) << std::endl;

  system("pause");
  return 0;
}