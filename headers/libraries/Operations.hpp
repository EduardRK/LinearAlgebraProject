#pragma once

#include <string> // std::string
#include <vector> // std::vector
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <iostream>

#include "Libraries.hpp"

namespace algb
{
  namespace libr
  {
    class Oprt final
    {
    private:
      static constexpr value_type DIMENSION_CROSS_PRODUCT = 3;
      static constexpr message_type SHOULD_BE_SCALAR = "Should be scalar";
      static constexpr message_type DIFFERENT_DIMENSIONS = "Different dimensions";
      static constexpr message_type WRONG_DIMENSIONS = "Wrong dimensions";

      Oprt() {}
      ~Oprt() {}

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
      static auto increment(container_type<T> const &scalar) -> container_type<T>;

      template <class T>
      static auto sub(container_type<T> const &left, container_type<T> const &right) -> container_type<T>;

      template <class T>
      static auto decrement(container_type<T> const &scalar) -> container_type<T>;

      template <class T>
      static auto norm(container_type<T> const &vect) -> container_type<T>;

      template <class T>
      static auto copy(container_type<T> const &vect) -> container_type<T>;

      template <class T>
      static auto multiplyByScalar(container_type<T> const &vect, container_type<T> const &scalar) -> container_type<T>;

      template <class T>
      static auto divisionByScalar(container_type<T> const &vect, container_type<T> const &scalar) -> container_type<T>;

      template <class T>
      static auto normalizeVector(container_type<T> const &vect) -> container_type<T>;

      template <class T>
      static auto getAngleBetweenVectors(container_type<T> const &left, container_type<T> const &right) -> container_type<T>;
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

  return container_type<T>{powf(base.front(), exponent.front())};
}

template <class T>
auto algb::libr::Oprt::sum(container_type<T> const &left, container_type<T> const &right) -> container_type<T>
{
  if (left.size() != right.size())
  {
    throw std::invalid_argument(DIFFERENT_DIMENSIONS);
  }

  container_type<T> result(left.size());

  for (size_t i = 0; i < left.size(); ++i)
  {
    result.push_back(left.at(i) + right.at(i));
  }

  return result;
}

template <class T>
auto algb::libr::Oprt::increment(container_type<T> const &scalar) -> container_type<T>
{
  if (scalar.size() != 1)
  {
    throw std::invalid_argument(SHOULD_BE_SCALAR);
  }

  return container_type<T>{scalar.front() + 1};
}

template <class T>
auto algb::libr::Oprt::sub(container_type<T> const &left, container_type<T> const &right) -> container_type<T>
{
  if (left.size() != right.size())
  {
    throw std::invalid_argument(DIFFERENT_DIMENSIONS);
  }

  container_type<T> result(left.size());

  for (size_t i = 0; i < left.size(); ++i)
  {
    result.push_back(left.at(i) - right.at(i));
  }

  return result;
}

template <class T>
auto algb::libr::Oprt::decrement(container_type<T> const &scalar) -> container_type<T>
{
  if (scalar.size() != 1)
  {
    throw std::invalid_argument(SHOULD_BE_SCALAR);
  }

  return container_type<T>{scalar.front() - 1};
}

template <class T>
auto algb::libr::Oprt::norm(container_type<T> const &vect) -> container_type<T>
{
  return container_type<T>{sqrtf(dotProduct(vect, vect).front())};
}

template <class T>
auto algb::libr::Oprt::copy(container_type<T> const &vect) -> container_type<T>
{
  return container_type<T>{vect};
}

template <class T>
auto algb::libr::Oprt::multiplyByScalar(container_type<T> const &vect, container_type<T> const &scalar) -> container_type<T>
{
  if (scalar.size() != 1)
  {
    throw std::invalid_argument(SHOULD_BE_SCALAR);
  }

  container_type<T> result(vect.size());

  for (T const &element : vect)
  {
    result.push_back(element * scalar.front());
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

  container_type<T> result(vect.size());

  for (T const &element : vect)
  {
    result.push_back(element / scalar.front());
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

  return container_type<T>{acosf(divisionByScalar(dotProduct(left, right), dotProduct(norm(left), norm(right))).front())};
};