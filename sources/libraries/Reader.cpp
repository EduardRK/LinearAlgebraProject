#include <iostream>
#include <stdexcept>

#include "Reader.hpp"

algb::libr::Reader::~Reader()
{
}

algb::libr::FileReader::FileReader(path_type const &path) : path{path}
{
    this->input.open(path, std::ios::in);

    if (!input.is_open())
    {
        throw std::invalid_argument(WRONG_PATH);
    }
}

algb::libr::FileReader::~FileReader()
{
    this->input.close();
}

auto algb::libr::FileReader::read() -> lines_type const
{
    lines_type result;
    line_type temp;

    while (std::getline(input, temp))
    {
        result.push_back(temp);
    }

    return result;
}

algb::libr::TerminalReader::TerminalReader()
{
}

algb::libr::TerminalReader::~TerminalReader()
{
}

auto algb::libr::TerminalReader::read() -> lines_type const
{
    lines_type result;
    line_type temp;

    while (std::getline(std::cin, temp))
    {
        if (temp == END_MESSAGE)
        {
            break;
        }

        result.push_back(temp);
    }
    
    return result;
}