#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP

#include <CLI/CLI.hpp>

namespace cli
{

namespace utils
{

struct BuildOptions
{
  int threads;
}; // struct BuildOptions

struct CleanOptions
{
  bool all;
}; // struct CleanOptions

class ArgParser
{
public:
  ArgParser(void) = default;

  static int parseArgs(int argc, char* argv[]);
}; // class ArgParser

} // namespace utils

} // namespace cli

#endif // !ARG_PARSER_HPP
