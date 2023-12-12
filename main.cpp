#include <iostream>
#include <string>

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
  using namespace algb::arch;

  std::vector<float> scalar{3};
  std::vector<float> vector1{9, 2, 3};
  std::vector<float> vector2{3, 4, 6};

  // test operations
  print(Oprt::dotProduct(vector1, vector2));
  print(Oprt::crossProduct(vector1, vector2));
  print(Oprt::sum(vector1, vector2));
  print(Oprt::sub(vector1, vector2));
  print(Oprt::norm(vector1));
  print(Oprt::normalizeVector(vector1));
  print(Oprt::increment(scalar));
  print(Oprt::decrement(scalar));
  print(Oprt::pow(scalar, scalar));
  print(Oprt::multiplyByScalar(vector2, scalar));
  print(Oprt::divisionByScalar(vector1, scalar));
  print(Oprt::getAngleBetweenVectors(vector1, vector2));

  system("pause");
  return 0;
}