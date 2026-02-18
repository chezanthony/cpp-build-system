#include "init-args-parser.hpp"
#include "arg-parser.hpp"
#include <iostream>

namespace cli::utils
{

  int ArgParser::parseArgs(int argc, char* argv[])
  {
    CLI::App app{"cpp build system"};
    bool verbose = false;
    app.add_flag("-v,--verbose", verbose, "Verbose Output");

    cli::commands::InitArgsParser initParser;
    initParser.parseArgs(app);
  
    CLI11_PARSE(app, argc, argv);
    return 0;
  }

} // namespace cli::utils
