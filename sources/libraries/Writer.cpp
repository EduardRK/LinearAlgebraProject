#include <iostream>

#include "Writer.hpp"

algb::libr::FileWriter::FileWriter(path_type const &path) : path{path}
{
    this->out.open(path, std::ios::out);
}

algb::libr::FileWriter::~FileWriter()
{
    this->out.close();
}

auto algb::libr::FileWriter::write(line_type const &line) -> bool_type const
{
    if (out.fail())
    {
        return false;
    }

    out << line << std::endl;
    return true;
}

auto algb::libr::FileWriter::write(lines_type const &lines) -> bool_type const
{
    if (out.fail())
    {
        return false;
    }

    for (line_type line : lines)
    {
        out << line << std::endl;
    }
    return true;
}

algb::libr::TerminalWriter::TerminalWriter()
{
}

algb::libr::TerminalWriter::~TerminalWriter()
{
}

auto algb::libr::TerminalWriter::write(line_type const &line) -> bool_type const
{
    if (line.empty())
    {
        return false;
    }

    std::cout << line << std::endl;
    return true;
}

auto algb::libr::TerminalWriter::write(lines_type const &lines) -> bool_type const
{
    if (lines.empty())
    {
        return false;
    }

    for (line_type line : lines)
    {
        std::cout << line << std::endl;
    }
    return true;
}