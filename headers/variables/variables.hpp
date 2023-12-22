#pragma once


#include <map>
#include <string>
#include <stdexcept>
#include <tuple>
#include <optional>
#include <type_traits>

#include "Writer.hpp"
#include "Reader.hpp"
#include "Parser.hpp"
#include "Operations.hpp"

namespace algb
{
  namespace vrbl
  {
    struct Variable
    {
      void *value;
      std::string type_id;
    };

    template <class... Ts>
    class Database
    {
    public:
      using line_type = libr::line_type;
      using lines_type = libr::lines_type;

      template <class T>
      using conversion_func = std::optional<T> (*)(const lines_type &);

      Database(const conversion_func<Ts>... conversionFunctions);
      ~Database();

      const line_type TYPES_ERROR = "TYPES DON'T MATCH";
      const line_type NAME_ERROR = "STORE DOESN'T CONTAIN VARIABLE WITH PASSED NAME";

      template <int T = 0>
      auto defineType(void *&ptr, line_type &type_id, lines_type const &values) -> void;

      auto setVariable(
          line_type const &name,
          lines_type const &values) -> void;

      template <class T>
      auto getVariable(
          T &object,
          line_type const &name) -> void;

    private:
      std::map<std::string, Variable> store_;
      const std::tuple<const conversion_func<Ts>...> conversionFunctions_;
    };
  }
}

template <class... Ts>
algb::vrbl::Database<Ts...>::Database(const conversion_func<Ts>... conversionFunctions) : conversionFunctions_(conversionFunctions...)
{
}

template <class... Ts>
template <int I>
auto algb::vrbl::Database<Ts...>::defineType(void *&ptr, line_type &type_id, lines_type const &values) -> void
{
  if constexpr (I < sizeof...(Ts))
  {
    auto conversion_function = std::get<I>(this->conversionFunctions_);
    if (auto tmp = conversion_function(values); tmp.has_value())
    {
      auto value = new std::remove_reference_t<decltype(tmp.value())>(tmp.value());

      ptr = value;
      type_id = typeid(*value).name();
    }
    else
    {
      defineType<I + 1>(ptr, type_id, values);
    }
  }
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

  defineType(ptr, type_id, values);

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

  if (tmp == store_.end())
  {
    throw std::invalid_argument(NAME_ERROR);
  }
  if (auto variable = tmp->second; typeid(T).name() == variable.type_id)
  {
    object = *(T *)(variable.value);
  }
  else
  {
    throw std::invalid_argument(TYPES_ERROR);
  }
};