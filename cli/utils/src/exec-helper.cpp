#include "exec-helper.hpp"
#include <cstdio>
#include <iostream>
#include <string>

namespace cli::utils
{

  ReturnType<void> ExecHelper::executeCommand(const std::string& command) noexcept
  {
    FILE* pipe = popen(command.c_str(), "r");
    char buffer[128];
    while (nullptr != fgets(buffer, sizeof(buffer), pipe))
    {
      std::cout << buffer;
    }

    const int status = pclose(pipe);
    if (0 != status)
    {
      return std::unexpected(ErrorType { core::ErrorCodes::FailedToExecuteCommand, "" });
    }
  
    return {};
  }

} // namespace cli::utils
