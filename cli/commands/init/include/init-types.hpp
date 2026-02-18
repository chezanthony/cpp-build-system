#ifndef INIT_TYPES_HPP
#define INIT_TYPES_HPP

#include <cstdint>
#include <optional>
#include <string>

namespace cli::commands
{

  enum class InitType : std::uint8_t
  {
    Empty,
    Lib,
    Bin,
  };
  
  struct InitCommandOptions
  {
    InitType initType;
    std::string projectName;
    std::optional<std::string > projectDescription;
    std::string targetName;
  };

} // namespace cli::commands

#endif // !INIT_TYPES_HPP

