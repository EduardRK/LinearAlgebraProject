#pragma once

#include <map>
#include <string>
#include <stdexcept>

#include "libraries.hpp"

namespace algb
{
  namespace vrbl
  {
    struct Variable
    {
      void *value;
      std::string type_id;
    };

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

      const line_type TYPES_ERROR = "TYPES DON'T MATCH";
      const line_type NAME_ERROR = "STORE DOESN'T CONTAIN VARIABLE WITH PASSED NAME";

      // template <class T>
      // T getValue(line_type const &name);

      auto setVariable(
          line_type const &name,
          lines_type const &values) -> void;

      template <class T>
      auto getVariable(
          T &object,
          line_type const &name) -> void;

    private:
      std::map<std::string, Variable> store_;
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
  std::string type_id;
  void *ptr;

  auto vals = new std::vector<float>{1, 100, 5, 6};
  ptr = vals;
  type_id = typeid(vals).name();

  algb::vrbl::Variable box{
      ptr,
      type_id,
  };

  this->store_.insert(std::pair(name, box));
};

template <class... Ts>
template <class T>
auto algb::vrbl::Database<Ts...>::getVariable(
    T &object,
    line_type const &name) -> void
{
  auto tmp = store_.find(name);

  if (tmp->first != name)
  {
    throw std::invalid_argument();
  }
  if (auto variable = tmp->second; typeid(T *).name() == variable.type_id)
  {
    object = *(T *)(variable.value);
  }
  else
  {
    throw std::invalid_argument(TYPES_ERROR);
  }
};