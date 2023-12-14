#pragma once

#include <regex>

#include "Libraries.hpp"

namespace algb
{
    namespace libr
    {
        class Validator
        {
        public:
            virtual ~Validator();

            virtual auto generateRegex() -> void const = 0;
            virtual auto isValid(line_type const &line) -> bool_type const = 0;
        };

        class CommandValidator : public Validator
        {
        private:
            const line_type GROUP_ALL_OPERATIONS_AND_SYSTEM_WORDS = "(WRITEALL|READ|WRITE|SET|DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE|INC|DEC|NORM|NORMALIZE|COPY)";
            const line_type GROUP_BINARY_OPERATIONS = "(DOT|CROSS|POW|SUM|SUM|SUB|MULT|DIV|ANGLE)";
            const line_type GROUP_UNARY_OPERATIONS = "(INC|DEC|NORM|NORMALIZE|COPY)";

            const char_type separator;

            regex_type setRegex;
            regex_type writeRegex;
            regex_type writeAllRegex;
            regex_type readRegex;

        public:
            CommandValidator(const char_type separator);
            ~CommandValidator();

            auto generateRegex() -> void const override;
            auto isValid(line_type const &line) -> bool_type const override;
        };
    }
}