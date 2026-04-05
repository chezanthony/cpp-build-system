#include "init-args-parser.hpp"
#include "new-args-parser.hpp"
#include <CLI/CLI.hpp>

int main(int argc, char* argv[])
{
  CLI::App app{"cpp build system"};

  bool verbose = false;
  app.add_flag("-v,--verbose", verbose, "Verbose Output");

  cli::commands::InitArgsParser initParser;
  initParser.parseArgs(app);

  cli::commands::NewArgsParser newParser;
  newParser.parseArgs(app);
  
  CLI11_PARSE(app, argc, argv);

  return 0;
}
