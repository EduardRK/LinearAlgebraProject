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
        public:
            virtual ~Parser();

            virtual auto parse(line_type const &t) -> lines_type const = 0;
        };

        class LineParser : public Parser
        {
        private:
            const char_type separator;

        public:
            LineParser(char_type const &separator);
            ~LineParser();

            auto parse(line_type const &line) -> lines_type const override;
        };
    }
}