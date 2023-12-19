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
    class Interpreter
    {
    private:
      using char_type = libr::char_type;
      using line_type = libr::line_type;
      using path_type = libr::path_type;
      using lines_type = libr::lines_type;
      using value_type = libr::value_type;
      using container_type = libr::container_type<value_type>;
      using bool_type = libr::bool_type;
      using reader_type = libr::Reader;
      using writer_type = libr::Writer;
      using parser_type = libr::Parser;
      using validator_type = libr::Validator;

      static constexpr char_type DEFAULT_SEPARATOR = ' ';

      const std::unordered_set<line_type> OPERATIONS{"DOT", "CROSS", "SUM", "SUB", "ANGLE", "POW", "MULT", "DIV", "INC", "DEC", "NORM", "NORMALIZE", "COPY"};

      reader_type *reader;
      writer_type *writer;
      parser_type *parser;
      validator_type *validator;

      vrbl::Database<container_type, lines_type> database_;
      std::unordered_map<line_type, container_type (Interpreter::*)(lines_type const &)> commands_;

      Interpreter(reader_type *reader, writer_type *writer, parser_type *parser, validator_type *validator);

    public:
      Interpreter(path_type const &logPath, path_type const &resultPath, const char_type separator);
      Interpreter(path_type const &logPath, path_type const &resultPath);
      Interpreter(const char_type separator);
      Interpreter();

      ~Interpreter();

      auto interpret() -> void;

    private:
      auto interpret(lines_type const &commands) -> void;
      auto interpret(line_type const &command) -> void;

      auto setVariable(lines_type const &lines) -> void;
      auto readVariable(lines_type const &lines) -> void;
      auto writeVariable(lines_type const &lines) -> void;
      auto writeAllVariables(lines_type const &lines) -> void;

      auto dotProduct(lines_type const &lines) -> container_type;
      auto crossProduct(lines_type const &lines) -> container_type;
      auto pow(lines_type const &lines) -> container_type;
      auto sum(lines_type const &lines) -> container_type;
      auto increment(lines_type const &lines) -> container_type;
      auto sub(lines_type const &lines) -> container_type;
      auto decrement(lines_type const &lines) -> container_type;
      auto norm(lines_type const &lines) -> container_type;
      auto copy(lines_type const &lines) -> container_type;
      auto multiplyByScalar(lines_type const &lines) -> container_type;
      auto divisionByScalar(lines_type const &lines) -> container_type;
      auto normalizeVector(lines_type const &lines) -> container_type;
      auto getAngleBetweenVectors(lines_type const &lines) -> container_type;

      auto initialize(container_type &v1, container_type &v2, lines_type const &lines) -> void;
      auto initialize(container_type &v, lines_type const &lines) -> void;

      auto containerToLines(container_type const &container) -> lines_type;

      auto isOperation(line_type const &operationName) -> bool_type;
    };
  }
}