#include <iostream>
#include "utils/include/arg-parser.hpp"

int main(int argc, char* argv[])
{
  std::cout << "main passing to arg parser\n";

  const int parseResult = cli::utils::ArgParser::parseArgs(argc, argv);

  return 0;
}
