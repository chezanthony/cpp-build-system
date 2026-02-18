#ifndef BASE_ARGS_PARSER_HPP
#define BASE_ARGS_PARSER_HPP

#include <CLI/CLI.hpp>

namespace cli::commands
{

  template <typename Derived>
  class BaseArgsParser
  {
  public:
    void parseArgs(CLI::App& app);
  };

} // namespace cli::commands

#include "base-args-parser.tpp"

#endif // !BASE_ARGS_PARSER_HPP

