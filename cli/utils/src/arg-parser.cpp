#include "arg-parser.hpp"
#include <iostream>

namespace cli
{

namespace utils
{

int ArgParser::parseArgs(int argc, char* argv[])
{
  CLI::App app{"cpp build system"};
  bool verbose = false;
  app.add_flag("-v,--verbose", verbose, "Verbose Output");

  int threads = 1;
  auto build = app.add_subcommand("build", "Build the project");
  build->add_option("-t,--threads", threads, "Number of threads")
       ->check(CLI::Range(1,64))
       ->default_val(1);

  build->callback([&]() {
    std::cout << "build subcommand executed" << std::endl;
  });

  app.require_subcommand(1);
  CLI11_PARSE(app, argc, argv);
  return 0;
}

} // namespace utils

} // namespace cli
