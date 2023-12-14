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
    tempSetRegex += "((?:(?!" + GROUP_ALL_OPERATIONS_AND_SYSTEM_WORDS + "))[a-zA-Z](\\w*))" + separator;
    tempSetRegex += "*)" + GROUP_BINARY_OPERATIONS + "(" + separator;
    tempSetRegex += "((?:(?!" + GROUP_ALL_OPERATIONS_AND_SYSTEM_WORDS + "))[a-zA-Z](\\w*)*)){2}$|^((SET)" + separator;
    tempSetRegex += "((?:(?!" + GROUP_ALL_OPERATIONS_AND_SYSTEM_WORDS + "))[a-zA-Z](\\w*)*))" + separator;
    tempSetRegex += "" + GROUP_UNARY_OPERATIONS + "(" + separator;
    tempSetRegex += "((?:(?!" + GROUP_ALL_OPERATIONS_AND_SYSTEM_WORDS + "))[a-zA-Z](\\w*)*))$|^((SET)" + separator;
    tempSetRegex += "((?:(?!" + GROUP_ALL_OPERATIONS_AND_SYSTEM_WORDS + "))[a-zA-Z](\\w*)*))(" + separator;
    tempSetRegex += "((?:(?!" + GROUP_ALL_OPERATIONS_AND_SYSTEM_WORDS + ")))[^" + separator;
    tempSetRegex += "]+)+$";
    this->setRegex = regex_type(tempSetRegex);

    this->writeAllRegex = regex_type("^(WRITEALL)$");

    line_type tempReadRegex = "^(READ)" + separator;
    tempReadRegex += "((?:(?!" + GROUP_ALL_OPERATIONS_AND_SYSTEM_WORDS + "))[^" + separator;
    tempReadRegex += "])+$";
    this->readRegex = regex_type(tempReadRegex);

    line_type tempWriteRegex = "^(WRITE)(" + separator;
    tempWriteRegex += "(?:(?!" + GROUP_ALL_OPERATIONS_AND_SYSTEM_WORDS + "))([a-zA-Z]\\w*))+$|^(WRITE)" + separator;
    tempWriteRegex += "(" + GROUP_BINARY_OPERATIONS + "(" + separator;
    tempWriteRegex += "(?:(?!" + GROUP_ALL_OPERATIONS_AND_SYSTEM_WORDS + "))[a-zA-Z](\\w*)){2})$|^(WRITE)" + separator;
    tempWriteRegex += "(" + GROUP_UNARY_OPERATIONS + "(" + separator;
    tempWriteRegex += "(?:(?!" + GROUP_ALL_OPERATIONS_AND_SYSTEM_WORDS + "))[a-zA-Z](\\w*)))$";
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