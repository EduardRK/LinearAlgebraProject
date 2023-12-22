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

            virtual auto isValid(line_type const &line) -> bool_type const = 0;
        };

        class CommandValidator : public Validator
        {
        private:
            using regex_type = std::regex;

            const line_type separator;

            regex_type setRegex;
            regex_type writeRegex;
            regex_type writeAllRegex;
            regex_type readRegex;

        public:
            CommandValidator(line_type const &separator);
            CommandValidator(const char_type separator);
            ~CommandValidator();

            auto isValid(line_type const &line) -> bool_type const override;

        private:
            auto generateRegex() -> void const;
        };
    }
}