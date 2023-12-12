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
    using char_type = libr::char_type;
    using line_type = libr::line_type;
    using lines_type = libr::lines_type;
    using value_type = float;
    using container_type = libr::container_type<value_type>;
    using reader_type = libr::Reader;
    using writer_type = libr::Writer;
    using parser_type = libr::Parser;

    class Interpreter
    {
    public:
      Interpreter(line_type const &logPath, char_type separator);
      Interpreter(char_type separator);
      ~Interpreter();

      auto readLog() -> lines_type;
      auto interpret(lines_type const &commands) -> void;

    private:
      reader_type *reader;
      writer_type *writer;
      parser_type *parser;

      vrbl::Database<container_type, line_type> database_;

      std::map<line_type, void (Interpreter::*)(lines_type const &)> commands_;

      auto setVariable(lines_type const &lines) -> void;
      auto dotProduct(lines_type const &lines) -> void;
    };
  }
}