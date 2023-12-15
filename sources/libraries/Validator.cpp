#include "Validator.hpp"

#include <iostream>

algb::libr::Validator::~Validator()
{
}

algb::libr::CommandValidator::CommandValidator(line_type const &separator) : separator{separator}
{
}

algb::libr::CommandValidator::CommandValidator(const char_type separator) : separator{line_type{separator}}
{
}

algb::libr::CommandValidator::~CommandValidator()
{
}

auto algb::libr::CommandValidator::generateRegex() -> void const
{
    line_type tempSetRegex = "^((SET)" + separator + "((?:(?!(WRITEALL|READ|WRITE|SET|DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*))" + separator + ")(DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE)(" + separator + "((?:(?!(WRITEALL|READ|WRITE|SET|DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*)*)){2}$|^((SET)" + separator + "((?:(?!(WRITEALL|READ|WRITE|SET|DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*)*))" + separator + "(INC|DEC|NORM|NORMALIZE|COPY)(" + separator + "((?:(?!(WRITEALL|READ|WRITE|SET|DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*)*))$|^((SET)" + separator + "((?:(?!(WRITEALL|READ|WRITE|SET|DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*)*))(" + separator + "((?:(?!(WRITEALL|READ|WRITE|SET|DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY))))[^" + separator + "]+)+$";
    this->setRegex = regex_type(tempSetRegex);

    this->writeAllRegex = regex_type("^(WRITEALL)$");

    line_type tempReadRegex = "^(READ)" + separator + "((?:(?!(WRITEALL|READ|WRITE|SET|DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[^" + separator + "])+$";
    this->readRegex = regex_type(tempReadRegex);

    line_type tempWriteRegex = "^(WRITE)(" + separator + "(?:(?!(WRITEALL|READ|WRITE|SET|DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))([a-zA-Z]\\w*))+$|^(WRITE)" + separator + "((DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE)(" + separator + "(?:(?!(WRITEALL|READ|WRITE|SET|DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*)){2})$|^(WRITE)" + separator + "((INC|DEC|NORM|NORMALIZE|COPY)(" + separator + "(?:(?!(WRITEALL|READ|WRITE|SET|DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*)))$";
    this->writeRegex = regex_type(tempWriteRegex);
}

auto algb::libr::CommandValidator::isValid(line_type const &line) -> bool_type const
{
    if (std::regex_match(line.data(), setRegex))
    {
        return true;
    }
    else if (std::regex_match(line.data(), writeRegex))
    {
        return true;
    }
    else if (std::regex_match(line.data(), writeAllRegex))
    {
        return true;
    }
    else if (std::regex_match(line.data(), readRegex))
    {
        return true;
    }
    return false;
}