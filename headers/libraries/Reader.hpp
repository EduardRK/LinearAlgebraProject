#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "Libraries.hpp"

namespace algb
{
    namespace libr
    {
        class Reader
        {
        public:
            virtual auto read() -> lines_type const = 0;
        };

        class FileReader : public Reader
        {
        private:
            const path_type path;
            std::ifstream input;

        public:
            FileReader(path_type const &path);
            ~FileReader();

            auto read() -> lines_type const override;
        };

        class TerminalReader : public Reader
        {
        private:
            static constexpr message_type END_MESSAGE = "end";

        public:
            TerminalReader();
            ~TerminalReader();

            auto read() -> lines_type const override;
        };
    }
}