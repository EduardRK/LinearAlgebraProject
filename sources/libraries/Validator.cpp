#include "Validator.hpp"

algb::libr::Validator::~Validator()
{
}

algb::libr::CommandValidator::CommandValidator(const char_type separator) : separator{separator}
{
}

algb::libr::CommandValidator::~CommandValidator()
{
}

auto algb::libr::CommandValidator::generateRegex() -> void const
{
    line_type tempSetRegex = "^((SET)" + separator;
    tempSetRegex += "((?:(?!(DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*))" + separator;
    tempSetRegex += "*)(DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE)(" + separator;
    tempSetRegex += "((?:(?!(DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*)*)){2}$|^((SET)" + separator;
    tempSetRegex += "((?:(?!(DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*)*))" + separator;
    tempSetRegex += "(INC|DEC|NORM|NORMALIZE|COPY)(" + separator;
    tempSetRegex += "((?:(?!(DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*)*))$|^((SET)" + separator;
    tempSetRegex += "((?:(?!(DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*)*))(" + separator;
    tempSetRegex += "((?:(?!(DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY))))[^" + separator;
    tempSetRegex += "]+)+$";
    this->setRegex = regex_type(tempSetRegex);

    this->writeAllRegex = regex_type("^(WRITEALL)$");

    line_type tempReadRegex = "^(READ)" + separator;
    tempReadRegex += "((?:(?!(DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[^" + separator;
    tempReadRegex += "])+$";
    this->readRegex = regex_type(tempReadRegex);

    line_type tempWriteRegex = "^(WRITE)(" + separator;
    tempWriteRegex += "(?:(?!(DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))([a-zA-Z]\\w*))+$|^(WRITE)" + separator;
    tempWriteRegex += "((DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE)(" + separator;
    tempWriteRegex += "(?:(?!(DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*)){2})$|^(WRITE)" + separator;
    tempWriteRegex += "((INC|DEC|NORM|NORMALIZE|COPY)(" + separator;
    tempWriteRegex += "(?:(?!(DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)))[a-zA-Z](\\w*)))$";
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