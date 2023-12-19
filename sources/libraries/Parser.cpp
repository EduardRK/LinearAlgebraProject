#include "Parser.hpp"

algb::libr::Parser::~Parser()
{
}

algb::libr::CommandParser::CommandParser(char_type const &separator) : separator{separator}
{
}

algb::libr::CommandParser::~CommandParser()
{
}

auto algb::libr::CommandParser::parse(line_type const &line) -> lines_type const
{
    lines_type result;

    auto startIterator = line.begin();
    auto currentIterator = startIterator;

    for (; currentIterator < line.end(); ++currentIterator)
    {
        if (*currentIterator != separator)
        {
            continue;
        }

        result.push_back(line_type(startIterator, currentIterator));
        startIterator = currentIterator + 1;
    }

    result.push_back(line_type(startIterator, currentIterator));

    return result;
}