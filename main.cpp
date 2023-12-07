#include <iostream>
#include <string>

#include "architecture.hpp"

using namespace algb::libr;

void print(std::vector<float> vect)
{
  for (float &element : vect)
  {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

int main(int argc, char **argv)
{
  using namespace algb::arch;

  std::string path = argv[0];
  auto pos = path.find_last_of('\\');
  path = path.substr(0, pos);
  pos = path.find_last_of('\\');
  path = path.substr(0, pos + 1);

  std::vector<float> scalar{3};
  std::vector<float> vector1{1, 2, 3};
  std::vector<float> vector2{5, 2, 1};

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

  std::cout << "Ok" << std::endl;
  system("pause");
  return 0;
}