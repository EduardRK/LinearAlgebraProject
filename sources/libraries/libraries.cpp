#include "libraries.hpp"

algb::libr::FileReader::FileReader(path_type path) : path{path}
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

algb::libr::FileWriter::FileWriter(path_type path) : path{path}
{
    this->out.open(path, std::ios::app);
}

algb::libr::FileWriter::~FileWriter()
{
    this->out.close();
}

auto algb::libr::FileWriter::write(line_type line) -> bool
{
    if (out.fail())
    {
        return false;
    }

    out << line << std::endl;
    return true;
}