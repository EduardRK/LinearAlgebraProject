#pragma once

#include <vector>
#include <string>

#include "Libraries.hpp"

namespace algb
{
    namespace libr
    {
        class Parser
        {
        private:
            const char_type separator;

        public:
            Parser(char_type const &separator);
            ~Parser();

            auto parse(line_type const &line) -> lines_type;
        };
    }
}