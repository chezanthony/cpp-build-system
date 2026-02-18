#ifndef BASE_ARGS_PARSER_TPP
#define BASE_ARGS_PARSER_TPP

#include <CLI/CLI.hpp>

namespace cli::commands
{

  template <typename Derived>
  void BaseArgsParser<Derived>::parseArgs(CLI::App& app)
  {
    static_cast<Derived*>(this)->parseArgsImpl(app);
  }

} // namespace cli::commands

#endif // !BASE_ARGS_PARSER_TPP

