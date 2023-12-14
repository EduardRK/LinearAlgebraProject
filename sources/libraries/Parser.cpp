#include "Parser.hpp"

algb::libr::Parser::~Parser()
{
}

algb::libr::LineParser::LineParser(char_type const &separator) : separator{separator}
{
}

algb::libr::LineParser::~LineParser()
{
}

auto algb::libr::LineParser::parse(line_type const &line) -> lines_type const
{
    line_type temp = "";
    lines_type result;

    for (char c : line)
    {
        if (c != separator)
        {
            temp += c;
        }
        else
        {
            result.push_back(temp);
            temp = "";
        }
    }

    if (!temp.empty())
    {
        result.push_back(temp);
    }

    return result;
}