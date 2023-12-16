#include <stdexcept> // std::runtime_error
#include <string>    // std::getline

#include "architecture.hpp"
#include "Writer.hpp"
#include "Reader.hpp"
#include "Parser.hpp"
#include "Operations.hpp"

algb::arch::Interpreter::Interpreter(path_type const &logPath, path_type const &resultPath)
{
  Interpreter(logPath, resultPath, DEFAULT_SEPARATOR);
}

algb::arch::Interpreter::Interpreter(path_type const &logPath, path_type const &resultPath, const char_type separator)
{
  Interpreter(new libr::FileReader(logPath), new libr::FileWriter(resultPath), new libr::CommandParser(separator), new libr::CommandValidator(separator));
}

algb::arch::Interpreter::Interpreter()
{
  Interpreter{DEFAULT_SEPARATOR};
}

algb::arch::Interpreter::Interpreter(const char_type separator)
{
  Interpreter(new libr::TerminalReader(), new libr::TerminalWriter(), new libr::CommandParser(separator), new libr::CommandValidator(separator));
}

algb::arch::Interpreter::Interpreter(reader_type *reader, writer_type *writer, parser_type *parser, validator_type *validator) : reader{reader}, writer{writer}, parser{parser}, validator{validator}, commands_{
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
      throw std::invalid_argument("Wrong command: " + command);
    }

    interpret(command);
  }
}

auto algb::arch::Interpreter::interpret(line_type const &command) -> void
{
  lines_type parseCommand = parser->parse(command);
  line_type systemCommand = parseCommand.front();

  lines_type commandBody = lines_type(++parseCommand.begin(), parseCommand.end());

  if (systemCommand == "SET")
  {
    setVariable(commandBody);
  }
  else if (systemCommand == "READ")
  {
    readVariable(commandBody);
  }
  else if (systemCommand == "WRITE")
  {
    writeVariable(commandBody);
  }
  else if (systemCommand == "WRITEALL")
  {
    writeAllVariables(commandBody);
  }
  else
  {
    throw std::invalid_argument("Wrong system command: " + systemCommand);
  }
}

auto algb::arch::Interpreter::setVariable(lines_type const &lines) -> void
{
  line_type name = lines.front();
  line_type command = lines[1];

  if (isOperation(command))
  {
    container_type result = (this->*this->commands_.at(command))(lines_type(lines.begin() + 2, lines.end()));
    lines_type linesResult = containerToLines(result);
    database_.setVariable(name, linesResult);
  }
  else
  {
    database_.setVariable(name, lines_type(++lines.begin(), lines.end()));
  }
}

auto algb::arch::Interpreter::readVariable(lines_type const &lines) -> void
{
}

auto algb::arch::Interpreter::writeVariable(lines_type const &lines) -> void
{
}

auto algb::arch::Interpreter::writeAllVariables(lines_type const &lines) -> void
{
}

auto algb::arch::Interpreter::dotProduct(lines_type const &lines) -> container_type
{
  container_type v1, v2;

  initialize(v1, v2, lines);

  return algb::libr::Oprt::dotProduct(v1, v2);
}

auto algb::arch::Interpreter::initialize(container_type &v1, container_type &v2, lines_type const &lines) -> void
{
  line_type left = lines.front();
  line_type right = lines.back();

  database_.getVariable(v1, left);
  database_.getVariable(v2, right);
}

auto algb::arch::Interpreter::initialize(container_type &v, lines_type const &lines) -> void
{
  line_type name = lines.front();

  database_.getVariable(v, name);
}

auto algb::arch::Interpreter::containerToLines(container_type const &container) -> lines_type
{
  lines_type lines;

  for (value_type value : container)
  {
    lines.push_back(std::to_string(value));
  }

  return lines;
}

auto algb::arch::Interpreter::isOperation(line_type const &operationName) -> bool_type
{
  return OPERATIONS.find(operationName) != OPERATIONS.end();
}
