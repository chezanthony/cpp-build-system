#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP

#include <CLI/CLI.hpp>

namespace cli::utils
{

  struct BuildOptions
  {
    int threads;
  };
  
  struct CleanOptions
  {
    bool all;
  };
  
  class ArgParser
  {
  public:
    ArgParser(void) = default;
  
    static int parseArgs(int argc, char* argv[]);
  };

} // namespace cli::utils

#endif // !ARG_PARSER_HPP

