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

            virtual auto parse(line_type const &line) -> lines_type const = 0;
        };

        class CommandParser : public Parser
        {
        private:
            const char_type separator;

        public:
            CommandParser(char_type const &separator);
            ~CommandParser();

            auto parse(line_type const &line) -> lines_type const override;
        };
    }
}