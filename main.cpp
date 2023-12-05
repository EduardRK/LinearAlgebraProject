#include <iostream>
#include <string>

#include "architecture.hpp"

int main(int argc, char **argv)
{
  using namespace algb::arch;

  std::string path = argv[0];
  auto pos = path.find_last_of('\\');
  path = path.substr(0, pos);
  pos = path.find_last_of('\\');
  path = path.substr(0, pos + 1);

  try
  {
    //Interpreter itpt(path + "..\\data\\log.txt", ',');
    Interpreter itpt("..\\data\\log.txt", ',');
    // Interpreter itpt("D:\\GerasimovOV\\CPP\\05-201\\3rd_semester\\2023.11.28(1)\\data\\log.txt", ',');
  }
  catch (std::runtime_error const &exc)
  {
    std::cout << exc.what() << std::endl;
  }

  std::cout << "Ok" << std::endl;
  system("pause");
  return 0;
}