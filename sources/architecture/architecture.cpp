#include <stdexcept> // std::runtime_error
#include <string>    // std::getline

#include "architecture.hpp"
#include "Writer.hpp"
#include "Reader.hpp"
#include "Parser.hpp"
#include "Operations.hpp"

algb::arch::Interpreter::Interpreter(line_type const &logPath, char_type separator) : commands_{
                                                                                          {"SET", &algb::arch::Interpreter::setVariable},
                                                                                          {"DOT", &algb::arch::Interpreter::dotProduct}}
{
  this->reader = new libr::FileReader(logPath);
  this->writer = new libr::FileWriter(logPath);
  this->parser = new libr::Parser(separator);
}

algb::arch::Interpreter::Interpreter(char_type separator)
{
  this->reader = new libr::TerminalReader();
  this->writer = new libr::TerminalWriter();
  this->parser = new libr::Parser(separator);
}
algb::arch::Interpreter::~Interpreter()
{
  delete this->reader;
  delete this->writer;
  delete this->parser;
}

auto algb::arch::Interpreter::readCommand() -> void
{
  line_type line;   // "set x 42"
  lines_type lines; // {"set", "x", "42"}

  // std::getline(this->ifs_, line);
  // lines = libr::parse(line, this->separator_);
}

auto algb::arch::Interpreter::interpret(lines_type const &cmd) -> void
{
  auto key = cmd.front();
  auto oth = lines_type(++cmd.begin(), cmd.end());
  (this->*this->commands_.at(key))(oth); // throw
}

auto algb::arch::Interpreter::setVariable(lines_type const &lines) -> void
{
  auto name = lines.front();
  auto value = lines_type(++lines.begin(), lines.end());
  this->database_.setVariable(name, value);
}

auto algb::arch::Interpreter::dotProduct(
    lines_type const &lines) -> void
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