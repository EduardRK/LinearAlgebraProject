#pragma once

#include <fstream>       // std::ifstream
#include <unordered_map> // std::unordered_map
#include <unordered_set> // std::unorder_set

#include "Reader.hpp"
#include "Writer.hpp"
#include "Parser.hpp"
#include "Operations.hpp"
#include "Validator.hpp"
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
    using validator_type = libr::Validator;

    class Interpreter
    {
    public:
      Interpreter(line_type const &logPath, line_type const &resultPath, const char_type separator);
      Interpreter(line_type const &logPath, line_type const &resultPath);
      Interpreter(const char_type separator);
      Interpreter();

      ~Interpreter();

      auto interpret() -> void;

    private:
      static constexpr char_type DEFAULT_SEPARATOR = ' ';

      const std::unordered_set<line_type> BINARY_OPERATIONS{"DOT", "CROSS", "SUM", "SUB", "ANGLE", "POW", "MULT", "DIV"};
      const std::unordered_set<line_type> UNARY_OPERATIONS{"INC", "DEC", "NORM", "NORMALIZE", "COPY"};

      reader_type *reader;
      writer_type *writer;
      parser_type *parser;
      validator_type *validator;

      vrbl::Database<container_type, line_type> database_;
      std::unordered_map<line_type, void (Interpreter::*)(lines_type const &)> commands_;

      Interpreter(reader_type *reader, writer_type *writer, parser_type *parser, validator_type *validator);

      auto interpret(line_type const &command) -> void;

      auto setVariable(lines_type const &lines) -> void;
      auto readVariable(lines_type const &lines) -> void;
      auto writeVariable(lines_type const &lines) -> void;
      auto writeAllVariable(lines_type const &lines) -> void;

      auto dotProduct(lines_type const &lines) -> void;
      auto crossProduct(lines_type const &lines) -> void;
      auto pow(lines_type const &lines) -> void;
      auto sum(lines_type const &lines) -> void;
      auto increment(lines_type const &lines) -> void;
      auto sub(lines_type const &lines) -> void;
      auto decrement(lines_type const &lines) -> void;
      auto norm(lines_type const &lines) -> void;
      auto copy(lines_type const &lines) -> void;
      auto multiplyByScalar(lines_type const &lines) -> void;
      auto divisionByScalar(lines_type const &lines) -> void;
      auto normalizeVector(lines_type const &lines) -> void;
      auto getAngleBetweenVectors(lines_type const &lines) -> void;
    };
  }
}