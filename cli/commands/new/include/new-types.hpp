#ifndef NEW_TYPES_HPP
#define NEW_TYPES_HPP

#include <cstdint>
#include <optional>
#include <string>

namespace cli::commands
{

  enum class LibType : std::uint8_t
  {
    interface,
    staticLib,
    shared,
  };

  struct NewCommandOptions
  {
    bool isBin; 
    std::string targetName;
    std::optional<std::string> targetDescription;
    LibType libType;
  };

} // namespace cli::commands

#endif // NEW_TYPES_HPP

