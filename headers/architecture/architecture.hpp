#pragma once

#include <fstream> // std::ifstream
#include <map>     // std::map

#include "libraries.hpp"
#include "variables.hpp"

namespace algb
{
  namespace arch
  {
    class Interpreter
    {
    public:
      using char_type = libr::char_type;
      using line_type = libr::line_type;
      using lines_type = libr::lines_type;

      // set, v1, 1, 2, 3
      // set, v2, 4, 5, 6
      // dot, v1, v2, v3
      Interpreter(line_type const &logPath, char_type sep);
      ~Interpreter();

      auto readCommand() -> void;
      auto readFullLog() -> void;

    private:
      using file_strm_type = std::ifstream;
      using value_type = float;

      line_type const logPath_;
      char_type const separator_;
      file_strm_type ifs_;

      vrbl::Database<int, float, std::vector<int>> database_;

      std::map<line_type, void (Interpreter::*)(lines_type const &)> commands_;

      auto interpret(lines_type const &command) -> void;

      auto setVariable(lines_type const &lines) -> void;
      auto dotProduct(lines_type const &lines) -> void;
    };
  }
}