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