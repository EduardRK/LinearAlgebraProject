#include "libraries.hpp"

algb::libr::TerminalReader::TerminalReader()
{
}

algb::libr::TerminalReader::~TerminalReader()
{
}

auto algb::libr::TerminalReader::readAllLines() -> lines_type
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

algb::libr::TerminalWriter::TerminalWriter()
{
}

algb::libr::TerminalWriter::~TerminalWriter()
{
}

auto algb::libr::TerminalWriter::write(line_type line) -> bool
{
    std::cout << line << std::endl;
    return true;
}