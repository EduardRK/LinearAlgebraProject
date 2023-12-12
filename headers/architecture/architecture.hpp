#pragma once

#include <fstream> // std::ifstream
#include <map>     // std::map

#include "Reader.hpp"
#include "Writer.hpp"
#include "Parser.hpp"
#include "Operations.hpp"
#include "variables.hpp"

namespace algb
{
  namespace arch
  {
    class Interpreter
    {
    public:
      using char_type = libr::char_type;
      using line_type = libr::line_type;
      using lines_type = libr::lines_type;

      Interpreter(line_type const &logPath, char_type separator);
      Interpreter(char_type separator);
      ~Interpreter();

      auto readCommand() -> void;
      auto readFullLog() -> void;

    private:
      using value_type = float;
      using container_type = libr::container_type<value_type>;
      using reader_type = libr::Reader;
      using writer_type = libr::Writer;
      using parser_type = libr::Parser;

      const reader_type *reader;
      const writer_type *writer;
      const parser_type *parser;

      vrbl::Database<container_type, line_type> database_;

      std::map<line_type, void (Interpreter::*)(lines_type const &)> commands_;

      auto interpret(lines_type const &command) -> void;

      auto setVariable(lines_type const &lines) -> void;
      auto dotProduct(lines_type const &lines) -> void;
    };
  }
}