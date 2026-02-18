#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string_view>

namespace cli::core::constants
{
  
  constexpr std::string_view buildFileName = "cbs.toml";
  constexpr std::string_view cmakeFileName = "CMakeLists.txt";
  constexpr std::string_view projectHeader = "Project";
  constexpr std::string_view projectNameKey = "name";
  constexpr std::string_view projectDescription = "description";
  constexpr std::string_view projectVersionKey = "version";
  constexpr std::string_view initialVersionNumber = "0.0.1";
  constexpr std::string_view cppVersionKey = "cppVersion";
  constexpr std::string_view defaultCppVersion = "23";
  constexpr std::string_view subdirectoriesKey = "subdirectories";
  constexpr std::string_view libraryHeader = "Library";
  constexpr std::string_view libraryTypeKey = "libraryType";
  constexpr std::string_view binaryHeader = "Binary";

} // namespace cli::core::constants

#endif // !CONSTANTS_HPP

