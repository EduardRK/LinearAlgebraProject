#include <stdexcept> // std::runtime_error
#include <string>    // std::getline

#include "architecture.hpp"
#include "Writer.hpp"
#include "Reader.hpp"
#include "Parser.hpp"
#include "Operations.hpp"

algb::arch::Interpreter::Interpreter(line_type const &logPath, line_type const &resultPath)
{
  Interpreter(logPath, resultPath, DEFAULT_SEPARATOR);
}

algb::arch::Interpreter::Interpreter(line_type const &logPath, line_type const &resultPath, const char_type separator)
{
  Interpreter(new libr::FileReader(logPath), new libr::FileWriter(resultPath), new libr::Parser(separator), new libr::CommandValidator(separator));
}

algb::arch::Interpreter::Interpreter()
{
  Interpreter{DEFAULT_SEPARATOR};
}

algb::arch::Interpreter::Interpreter(const char_type separator)
{
  Interpreter(new libr::TerminalReader(), new libr::TerminalWriter(), new libr::Parser(separator), new libr::CommandValidator(separator));
}

algb::arch::Interpreter::Interpreter(reader_type *reader, writer_type *writer, parser_type *parser, validator_type *validator) : reader{reader}, writer{writer}, parser{parser}, validator{validator}, commands_{
                                                                                                                                                                                                           {"SET", &algb::arch::Interpreter::setVariable},
                                                                                                                                                                                                           {"DOT", &algb::arch::Interpreter::dotProduct}}
{
}

algb::arch::Interpreter::~Interpreter()
{
  delete this->reader;
  delete this->writer;
  delete this->parser;
}

auto algb::arch::Interpreter::readLog() -> lines_type
{
  return reader->read();
}

auto algb::arch::Interpreter::interpret(lines_type const &commands) -> void
{
  for (line_type command : commands)
  {
    /*
      this
      parse command
      setVariable
      call functions
      writer.write()
    */
  }
}

// auto algb::arch::Interpreter::interpret(lines_type const &cmd) -> void
// {
//   auto key = cmd.front();
//   auto oth = lines_type(++cmd.begin(), cmd.end());
//   (this->*this->commands_.at(key))(oth); // throw
// }

auto algb::arch::Interpreter::setVariable(lines_type const &lines) -> void
{
  auto name = lines.front();
  auto value = lines_type(++lines.begin(), lines.end());
  this->database_.setVariable(name, value);
}

auto algb::arch::Interpreter::dotProduct(lines_type const &lines) -> void
{
  libr::container_type<value_type> v1, v2;
  // value_type val;

  auto leftName = *lines.begin();
  auto rightName = *++lines.begin();
  auto newName = *++lines.begin();

  this->database_.getVariable(v1, leftName);
  this->database_.getVariable(v2, rightName);

  // val = libr::dotProduct(v1, v2);
  // this->database_.setVariable(newName, );
}