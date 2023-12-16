#pragma once

#include <string>
#include <vector>
#include <regex>

namespace algb
{
    namespace libr
    {
        using char_type = char;
        using value_type = float;
        using bool_type = bool;
        using message_type = char[];
        using path_type = std::string;
        using line_type = std::string;
        using lines_type = std::vector<std::string>;

        template <class T>
        using container_type = std::vector<T>;
    }
}