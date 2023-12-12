#pragma once

#include <string> // std::string
#include <vector> // std::vector
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <iostream>

namespace algb
{
  namespace libr
  {
    using char_type = char;
    using value_type = float;
    using message_type = char[];
    using bool_type = bool;
    using path_type = std::string;
    using line_type = std::string;
    using lines_type = std::vector<std::string>;

    template <class T>
    using container_type = std::vector<T>;

    class Parser
    {
    private:
      const char_type separator;

    public:
      Parser(char_type const &separator);
      ~Parser();

      auto parse(line_type const &line) -> lines_type;
    };

    class Oprt
    {
    private:
      Oprt();
      ~Oprt();
      static constexpr value_type DIMENSION_CROSS_PRODUCT = 3;
      static constexpr message_type SHOULD_BE_SCALAR = "Should be scalar";
      static constexpr message_type DIFFERENT_DIMENSIONS = "Different dimensions";
      static constexpr message_type WRONG_DIMENSIONS = "Wrong dimensions";

    public:
      template <class T>
      static auto dotProduct(container_type<T> const &left, container_type<T> const &right) -> container_type<T>;

      template <class T>
      static auto crossProduct(container_type<T> const &left, container_type<T> const &right) -> container_type<T>;

      template <class T>
      static auto pow(container_type<T> const &base, container_type<T> const &exponent) -> container_type<T>;

      template <class T>
      static auto sum(container_type<T> const &left, container_type<T> const &right) -> container_type<T>;

      template <class T>
      static auto increment(container_type<T> &scalar) -> container_type<T>;

      template <class T>
      static auto sub(container_type<T> const &left, container_type<T> const &right) -> container_type<T>;

      template <class T>
      static auto decrement(container_type<T> &scalar) -> container_type<T>;

      template <class T>
      static auto norm(container_type<T> const &vect) -> container_type<T>;

      template <class T>
      static auto multiplyByScalar(container_type<T> const &vect, container_type<T> const &scalar) -> container_type<T>;

      template <class T>
      static auto divisionByScalar(container_type<T> const &vect, container_type<T> const &scalar) -> container_type<T>;

      template <class T>
      static auto normalizeVector(container_type<T> const &vect) -> container_type<T>;

      template <class T>
      static auto getAngleBetweenVectors(container_type<T> const &left, container_type<T> const &right) -> container_type<T>;
    };

    class FileReader
    {
    private:
      const path_type path; // путь к файлу
      std::ifstream input; // поток чтения

    public:
      FileReader(path_type const &path); // конструктор иницилизирует путь и открывает поток чтения
      ~FileReader(); // закрывает поток чтения 

      auto read() -> lines_type; // считывает все строки в std::vector
    };

    class FileWriter
    {
    private:
      const path_type path;
      std::ofstream out; // поток записи

    public:
      FileWriter(path_type const &path);
      ~FileWriter();

      auto write(line_type const &line) -> bool_type; // записывает строку
      auto write(lines_type const &lines) -> bool_type; // записывает вектор строк
      template <class T>
      auto write(container_type<T> const &vect) -> bool_type; // записывает веткор
    };

    class TerminalReader
    {
    private:
      static constexpr message_type END_MESSAGE = "end"; // Константа для прекращения чтения из терминала. Constexpr - то что константа.

    public:
      TerminalReader();
      ~TerminalReader();

      auto read() -> lines_type;
    };

    class TerminalWriter
    {
    public:
      TerminalWriter();
      ~TerminalWriter();

      auto write(line_type const &line) -> bool_type;
      auto write(lines_type const &lines) -> bool_type;
      template <class T>
      auto write(container_type<T> const &vect) -> bool_type;
    };
  }
}

template <class T>
auto algb::libr::Oprt::dotProduct(container_type<T> const &left, container_type<T> const &right) -> container_type<T>
{
  if (left.size() != right.size())
  {
    throw std::invalid_argument(DIFFERENT_DIMENSIONS);
  }

  T temp = 0;

  for (size_t i = 0; i < left.size(); ++i)
  {
    temp += left.at(i) * right.at(i);
  }

  return container_type<T>{temp};
}

template <class T>
auto algb::libr::Oprt::crossProduct(container_type<T> const &left, container_type<T> const &right) -> container_type<T>
{
  if (left.size() != DIMENSION_CROSS_PRODUCT || left.size() != DIMENSION_CROSS_PRODUCT)
  {
    throw std::invalid_argument(WRONG_DIMENSIONS);
  }

  value_type firstCoord = left.at(1) * right.at(2) - left.at(2) * left.at(1);
  value_type secondCoord = -(left.at(0) * right.at(2) - left.at(2) * left.at(0));
  value_type thirdCoord = left.at(0) * right.at(1) - left.at(1) * left.at(0);

  return container_type<T>{firstCoord, secondCoord, thirdCoord};
}

template <class T>
auto algb::libr::Oprt::pow(container_type<T> const &base, container_type<T> const &exponent) -> container_type<T>
{
  if (base.size() != 1 || exponent.size() != 1)
  {
    throw std::invalid_argument(SHOULD_BE_SCALAR);
  }

  return container_type<T>{powf(base.at(0), exponent.at(0))};
}

template <class T>
auto algb::libr::Oprt::sum(container_type<T> const &left, container_type<T> const &right) -> container_type<T>
{
  if (left.size() != right.size())
  {
    throw std::invalid_argument(DIFFERENT_DIMENSIONS);
  }

  container_type<T> result;
  for (size_t i = 0; i < left.size(); ++i)
  {
    result.push_back(left.at(i) + right.at(i));
  }

  return result;
}

template <class T>
auto algb::libr::Oprt::increment(container_type<T> &scalar) -> container_type<T>
{
  if (scalar.size() != 1)
  {
    throw std::invalid_argument(SHOULD_BE_SCALAR);
  }

  ++scalar.at(0);
  return scalar;
}

template <class T>
auto algb::libr::Oprt::sub(container_type<T> const &left, container_type<T> const &right) -> container_type<T>
{
  if (left.size() != right.size())
  {
    throw std::invalid_argument(DIFFERENT_DIMENSIONS);
  }

  container_type<T> result;
  for (size_t i = 0; i < left.size(); ++i)
  {
    result.push_back(left.at(i) - right.at(i));
  }

  return result;
}

template <class T>
auto algb::libr::Oprt::decrement(container_type<T> &scalar) -> container_type<T>
{
  if (scalar.size() != 1)
  {
    throw std::invalid_argument(SHOULD_BE_SCALAR);
  }

  --scalar.at(0);
  return scalar;
}

template <class T>
auto algb::libr::Oprt::norm(container_type<T> const &vect) -> container_type<T>
{
  return container_type<T>{sqrtf(dotProduct(vect, vect).at(0))};
}

template <class T>
auto algb::libr::Oprt::multiplyByScalar(container_type<T> const &vect, container_type<T> const &scalar) -> container_type<T>
{
  if (scalar.size() != 1)
  {
    throw std::invalid_argument(SHOULD_BE_SCALAR);
  }

  container_type<T> result;
  for (T element : vect)
  {
    result.push_back(element * scalar.at(0));
  }

  return result;
}

template <class T>
auto algb::libr::Oprt::divisionByScalar(container_type<T> const &vect, container_type<T> const &scalar) -> container_type<T>
{
  if (scalar.size() != 1)
  {
    throw std::invalid_argument(SHOULD_BE_SCALAR);
  }

  container_type<T> result;
  for (T element : vect)
  {
    result.push_back(element / scalar.at(0));
  }

  return result;
}

template <class T>
auto algb::libr::Oprt::normalizeVector(container_type<T> const &vect) -> container_type<T>
{
  return container_type<T>{divisionByScalar(vect, norm(vect))};
}

template <class T>
auto algb::libr::Oprt::getAngleBetweenVectors(container_type<T> const &left, container_type<T> const &right) -> container_type<T>
{
  if (left.size() != right.size())
  {
    throw std::invalid_argument(DIFFERENT_DIMENSIONS);
  }

  return container_type<T>{acosf(divisionByScalar(dotProduct(left, right), dotProduct(norm(left), norm(right))).at(0))};
};