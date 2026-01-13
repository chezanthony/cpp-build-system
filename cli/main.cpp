#include <iostream>
#include "commands/build/include/test.hpp"
#include "utils/include/arg-parser.hpp"

int main(int argc, char* argv[])
{
  std::cout << "main\n";

  const int parseResult = cli::utils::ArgParser::parseArgs(argc, argv);

  Test::hello();
  return 0;
}
