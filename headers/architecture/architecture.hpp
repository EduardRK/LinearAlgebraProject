#pragma once

#include <fstream>       // std::ifstream
#include <unordered_map> // std::unordered_map

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
      Interpreter(line_type const &logPath, const char_type separator);
      Interpreter(line_type const &logPath);
      Interpreter(const char_type separator);
      Interpreter();

      ~Interpreter();

      auto readLog() -> lines_type;
      auto interpret(lines_type const &commands) -> void;

    private:
      static constexpr char_type DEFAULT_SEPARATOR = ' ';

      reader_type *reader;
      writer_type *writer;
      parser_type *parser;

      vrbl::Database<container_type, line_type> database_;
      
      std::unordered_map<line_type, void (Interpreter::*)(lines_type const &)> commands_;

      Interpreter(reader_type *reader, writer_type *writer, parser_type *parser);

      auto setVariable(lines_type const &lines) -> void;
      auto dotProduct(lines_type const &lines) -> void;
    };
  }
}