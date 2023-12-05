#pragma once

#include "libraries.hpp"

namespace algb
{
  namespace vrbl
  {

    // vector<float>
    // string
    // vector<string> -> vector<float> or string
    // struct variable{void* val, type id}
    // map<string, vrbl>
    template <class... Ts>
    class Database
    {
    public:
      using line_type = libr::line_type;
      using lines_type = libr::lines_type;

      Database();
      ~Database();

      // template <class T>
      // T getValue(line_type const &name);

      auto setVariable(
          line_type const &name,
          lines_type const &values) -> void;

      template <class T>
      auto getVariable(
          T &object,
          line_type const &name) -> void;
    };
  }
}

template <class... Ts>
algb::vrbl::Database<Ts...>::Database()
{
}

template <class... Ts>
algb::vrbl::Database<Ts...>::~Database()
{
}

template <class... Ts>
auto algb::vrbl::Database<Ts...>::setVariable(
    line_type const &name,
    lines_type const &values) -> void
{
}

template <class... Ts>
template <class T>
auto algb::vrbl::Database<Ts...>::getVariable(
    T &object,
    line_type const &name) -> void
{
}