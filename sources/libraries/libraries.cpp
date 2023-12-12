#include "libraries.hpp"

// const& для передачи по ссылке. Чтобы не копировать значение. Const чтобы не измениь значение
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
    lines_type result;                // ветор, в котором собираются все строки из файла
    line_type temp;                   // временная строка
    while (std::getline(input, temp)) // считывает строки, пока они есть из инпута в temp string
    {
        result.push_back(temp);
    }

    return result;
}

algb::libr::FileWriter::FileWriter(path_type const &path) : path{path}
{
    this->out.open(path, std::ios::out); // открывает поток на запись
}

algb::libr::FileWriter::~FileWriter()
{
    this->out.close(); // закрывает поток на запись
}

auto algb::libr::FileWriter::write(line_type const &line) -> bool_type
{
    if (out.fail()) // если ошибка соединения с файлом, то не запишет и вернет false
    {
        return false;
    }

    out << line << std::endl; // записывает в файла и возвращает тру
    return true;
}

auto algb::libr::FileWriter::write(lines_type const &lines) -> bool_type
{
    if (out.fail())
    {
        return false;
    }

    for (line_type line : lines) // записывает каждую строчку из вектора строк
    {
        out << line << std::endl; // записывает line в файл
    }
    return true;
}

template <class T>
auto algb::libr::FileWriter::write(container_type<T> const &vect) -> bool_type
{
    if (out.fail())
    {
        return false;
    }

    for (T element : vect)
    {
        out << element << " ";
    }
    out << std::endl;
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
    if (line.empty()) // если строка пуста
    {
        return false;
    }

    std::cout << line << std::endl;
    return true;
}

auto algb::libr::TerminalWriter::write(lines_type const &lines) -> bool_type
{
    if (lines.empty()) // если массив пустой
    {
        return false;
    }

    for (line_type line : lines)
    {
        std::cout << line << std::endl;
    }
    return true;
}

template <class T>
auto algb::libr::TerminalWriter::write(container_type<T> const &vect) -> bool_type
{
    if (vect.empty()) // если массив пусто
    {
        return false;
    }

    for (T element : vect)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
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

    if (!temp.empty())
    {
        result.push_back(temp);
    }

    return result;
}