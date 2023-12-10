#include "libraries.hpp"

algb::libr::FileReader::FileReader(path_type const &path) : path{path}
{
    this->input.open(path, std::ios::in);
}

algb::libr::FileReader::~FileReader()
{
    this->input.close();
}

auto algb::libr::FileReader::read() -> lines_type
{
    lines_type result;
    line_type string;
    while (std::getline(input, string))
    {
        result.push_back(string);
    }

    return result;
}

algb::libr::FileWriter::FileWriter(path_type const &path) : path{path}
{
    this->out.open(path, std::ios::app);
}

algb::libr::FileWriter::~FileWriter()
{
    this->out.close();
}

auto algb::libr::FileWriter::write(line_type const &line) -> bool_type
{
    if (out.fail())
    {
        return false;
    }

    out << line << std::endl;
    return true;
}

algb::libr::TerminalReader::TerminalReader()
{
}

algb::libr::TerminalReader::~TerminalReader()
{
}

auto algb::libr::TerminalReader::read() -> lines_type
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

auto algb::libr::TerminalWriter::write(line_type const &line) -> bool_type
{
    if (line.empty())
    {
        return false;
    }

    std::cout << line << std::endl;
    return true;
}

algb::libr::Parser::Parser(char_type const &separator) : separator{separator}
{
}

algb::libr::Parser::~Parser()
{
}

auto algb::libr::Parser::parse(line_type const &line) -> lines_type
{
    line_type temp = "";
    lines_type result;

    const char_type *lineChars = line.c_str();
    for (std::size_t i = 0; i < line.size(); ++i)
    {
        if (lineChars[i] != separator)
        {
            temp += lineChars[i];
        }
        else
        {
            result.push_back(temp);
            temp = "";
        }
    }

    return result;
}