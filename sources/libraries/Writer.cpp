#include <iostream>
#include <stdexcept>

#include "Writer.hpp"

algb::libr::Writer::~Writer()
{
}

algb::libr::FileWriter::FileWriter(path_type const &path) : path{path}
{
    this->out.open(path, std::ios::out);

    if (!out.is_open())
    {
        throw std::invalid_argument("Wrong path");
    }
}

algb::libr::FileWriter::~FileWriter()
{
    this->out.close();
}

auto algb::libr::FileWriter::write(line_type const &line) -> void const
{
    out << line << std::endl;
}

auto algb::libr::FileWriter::write(lines_type const &lines) -> void const
{
    for (line_type line : lines)
    {
        write(line);
    }
}

algb::libr::TerminalWriter::TerminalWriter()
{
}

algb::libr::TerminalWriter::~TerminalWriter()
{
}

auto algb::libr::TerminalWriter::write(line_type const &line) -> void const
{
    std::cout << line << std::endl;
}

auto algb::libr::TerminalWriter::write(lines_type const &lines) -> void const
{
    for (line_type line : lines)
    {
        write(line);
    }
}