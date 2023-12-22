#include <stdexcept> // std::runtime_error
#include <string>    // std::getline

#include "architecture.hpp"
#include "Writer.hpp"
#include "Reader.hpp"
#include "Parser.hpp"
#include "Operations.hpp"

algb::arch::Interpreter::Interpreter(path_type const &logPath, path_type const &resultPath) : Interpreter(logPath, resultPath, DEFAULT_SEPARATOR)
{
}

algb::arch::Interpreter::Interpreter(path_type const &logPath, path_type const &resultPath, const char_type separator) : Interpreter(new libr::FileReader(logPath), new libr::FileWriter(resultPath), new libr::CommandParser(separator), new libr::CommandValidator(separator))
{
}

algb::arch::Interpreter::Interpreter() : Interpreter{DEFAULT_SEPARATOR}
{
}

algb::arch::Interpreter::Interpreter(const char_type separator) : Interpreter(new libr::TerminalReader(), new libr::TerminalWriter(), new libr::CommandParser(separator), new libr::CommandValidator(separator))
{
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
  // line_type nameOrPath = lines.front();
  // lines_type newCommands;
  // reader_type *newReader;
  // //* Need method isVariable
  // if (database_->isVariable(nameOrPath))
  // {
  //   lines_type path;

  //   database_.getVariable(path, nameOrPath);
  //   newReader = new algb::libr::FileReader(path.front());
  // }
  // else
  // {
  //   newReader = new algb::libr::FileReader(nameOrPath);
  // }

  // newCommands = newReader->read();

  // interpret(newCommands);
}

auto algb::arch::Interpreter::writeVariable(lines_type const &lines) -> void
{
  line_type command = lines.front();

  if (isOperation(command))
  {
    container_type result = (this->*this->commands_.at(command))(lines_type(++lines.begin(), lines.end()));
    lines_type linesResult = containerToLines(result);
    line_type finalString = "TEMP:";

    for (line_type line : linesResult)
    {
      finalString += " " + line;
    }

    writer->write(finalString);
  }
  else
  {
    line_type finalString = "";
    lines_type values;

    for (line_type line : lines)
    {
      database_.getVariable(values, line);
      finalString += line + ":";

      for (line_type value : values)
      {
        finalString += " " + value;
      }

      writer->write(finalString);
      finalString = "";
    }
  }
}

auto algb::arch::Interpreter::writeAllVariables(lines_type const &lines) -> void
{
  //* Need all variables from database
}

auto algb::arch::Interpreter::dotProduct(lines_type const &lines) -> container_type
{
  container_type v1, v2;

  initialize(v1, v2, lines);

  return algb::libr::Oprt::dotProduct(v1, v2);
}

auto algb::arch::Interpreter::crossProduct(lines_type const &lines) -> container_type
{
  container_type v1, v2;

  initialize(v1, v2, lines);

  return algb::libr::Oprt::crossProduct(v1, v2);
}

auto algb::arch::Interpreter::pow(lines_type const &lines) -> container_type
{
  container_type v1, v2;

  initialize(v1, v2, lines);

  return algb::libr::Oprt::pow(v1, v2);
}

auto algb::arch::Interpreter::sum(lines_type const &lines) -> container_type
{
  container_type v1, v2;

  initialize(v1, v2, lines);

  return algb::libr::Oprt::sum(v1, v2);
}

auto algb::arch::Interpreter::increment(lines_type const &lines) -> container_type
{
  container_type v;

  initialize(v, lines);

  return algb::libr::Oprt::increment(v);
}

auto algb::arch::Interpreter::sub(lines_type const &lines) -> container_type
{
  container_type v1, v2;

  initialize(v1, v2, lines);

  return algb::libr::Oprt::sub(v1, v2);
}

auto algb::arch::Interpreter::decrement(lines_type const &lines) -> container_type
{
  container_type v;

  initialize(v, lines);

  return algb::libr::Oprt::decrement(v);
}

auto algb::arch::Interpreter::norm(lines_type const &lines) -> container_type
{
  container_type v;

  initialize(v, lines);

  return algb::libr::Oprt::norm(v);
}

auto algb::arch::Interpreter::copy(lines_type const &lines) -> container_type
{
  container_type v;

  initialize(v, lines);

  return algb::libr::Oprt::copy(v);
}

auto algb::arch::Interpreter::multiplyByScalar(lines_type const &lines) -> container_type
{
  container_type v1, v2;

  initialize(v1, v2, lines);

  return algb::libr::Oprt::multiplyByScalar(v1, v2);
}

auto algb::arch::Interpreter::divisionByScalar(lines_type const &lines) -> container_type
{
  container_type v1, v2;

  initialize(v1, v2, lines);

  return algb::libr::Oprt::divisionByScalar(v1, v2);
}

auto algb::arch::Interpreter::normalizeVector(lines_type const &lines) -> container_type
{
  container_type v;

  initialize(v, lines);

  return algb::libr::Oprt::normalizeVector(v);
}

auto algb::arch::Interpreter::getAngleBetweenVectors(lines_type const &lines) -> container_type
{

  container_type v1, v2;

  initialize(v1, v2, lines);

  return algb::libr::Oprt::getAngleBetweenVectors(v1, v2);
}

auto algb::arch::Interpreter::initialize(container_type &v1, container_type &v2, lines_type const &lines) -> void
{
  initialize(v1, lines.front());
  initialize(v2, lines.back());
}

auto algb::arch::Interpreter::initialize(container_type &v, lines_type const &lines) -> void
{
  initialize(v, lines.front());
}

auto algb::arch::Interpreter::initialize(container_type &v, line_type const &line) -> void
{
  database_.getVariable(v, line);
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
