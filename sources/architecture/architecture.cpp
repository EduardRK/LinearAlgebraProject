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
  Interpreter(new libr::FileReader(logPath), new libr::FileWriter(resultPath), new libr::LineParser(separator), new libr::CommandValidator(separator));
}

algb::arch::Interpreter::Interpreter()
{
  Interpreter{DEFAULT_SEPARATOR};
}

algb::arch::Interpreter::Interpreter(const char_type separator)
{
  Interpreter(new libr::TerminalReader(), new libr::TerminalWriter(), new libr::LineParser(separator), new libr::CommandValidator(separator));
}

algb::arch::Interpreter::Interpreter(reader_type *reader, writer_type *writer, parser_type *parser, validator_type *validator) : reader{reader}, writer{writer}, parser{parser}, validator{validator}, commands_{
                                                                                                                                                                                                           {"SET", &setVariable},
                                                                                                                                                                                                           {"READ", &readVariable},
                                                                                                                                                                                                           {"WRITE", &writeVariable},
                                                                                                                                                                                                           {"WRITEALL", &writeAllVariable},
                                                                                                                                                                                                           {"DOT", &dotProduct},
                                                                                                                                                                                                           {"CROSS", &crossProduct},
                                                                                                                                                                                                           {"SUM", &sum},
                                                                                                                                                                                                           {"SUB", &sub},
                                                                                                                                                                                                           {"INC", &increment},
                                                                                                                                                                                                           {"DEC", &decrement},
                                                                                                                                                                                                           {"POW", &pow},
                                                                                                                                                                                                           {"MULT", &multiplyByScalar},
                                                                                                                                                                                                           {"DIV", &divisionByScalar},
                                                                                                                                                                                                           {"ANGLE", &getAngleBetweenVectors},
                                                                                                                                                                                                           {"NORM", &norm},
                                                                                                                                                                                                           {"NORMALIZE", &normalizeVector},
                                                                                                                                                                                                           {"COPY", &copy}}
{
  this->validator->generateRegex();
}

algb::arch::Interpreter::~Interpreter()
{
  delete this->reader;
  delete this->writer;
  delete this->parser;
  delete this->validator;
}

auto algb::arch::Interpreter::interpret() -> void
{
  lines_type commands = reader->read();
  interpret(commands);
}

auto algb::arch::Interpreter::interpret(lines_type const &commands) -> void
{
  for (line_type command : commands)
  {
    if (!validator->isValid(command))
    {
      continue;
      // exeption ?
    }

    interpret(command);
  }
}

auto algb::arch::Interpreter::interpret(line_type const &command) -> void
{
  /*
       this
       parse command
       setVariable
       call functions
       writer.write()
  */
}

// auto algb::arch::Interpreter::interpret(lines_type const &cmd) -> void
// {
//   auto key = cmd.front();
//   auto oth = lines_type(++cmd.begin(), cmd.end());
//   (this->*this->commands_.at(key))(oth); // throw
// }

auto algb::arch::Interpreter::setVariable(lines_type const &lines) -> void
{
  line_type name = lines.front();
  lines_type value = lines_type(++lines.begin(), lines.end());
  this->database_.setVariable(name, value);
}

auto algb::arch::Interpreter::dotProduct(lines_type const &lines) -> void
{
  container_type v1, v2;
  // value_type val;

  line_type leftName = *lines.begin();
  line_type rightName = *++lines.begin();
  line_type newName = *++lines.begin();

  this->database_.getVariable(v1, leftName);
  this->database_.getVariable(v2, rightName);

  // val = libr::dotProduct(v1, v2);
  // this->database_.setVariable(newName, );
}