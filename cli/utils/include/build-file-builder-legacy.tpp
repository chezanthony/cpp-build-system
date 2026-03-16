#include <optional>
#include <string>
#include <string_view>

namespace cli::utils
{

  BuildFileBuilderLegacy& BuildFileBuilderLegacy::writeProjectBuildFile(
    const std::string& name,
    std::optional<std::string> description)
  {
    mData += "cmake_minimum_required(VERSION 3.15)\n";
    mData += "\n";
    mData += "project(" + name + "\n";
    mData += "\tVERSION 0.0.1\n";

    if (description.has_value())
    {
      mData += "\tDESCRIPTION \"" + description.value() + "\"\n";
    }
    
    mData += "\tLANGUAGES CXX\n";
    mData += ")\n";
    mData += "\n";
    mData += "set(CMAKE_CXX_STANDARD 23)\n";
    mData += "set(CMAKE_CXX_STANDARD_REQUIRED True)\n";

    return *this;
  }

  BuildFileBuilderLegacy& BuildFileBuilderLegacy::writeLibraryBuildFile(
    const std::string& name,
    std::string_view type)
  {
    mData += "add_library(" + name + " " + type + ")\n";
    mData += "\n";
    mData += "target_inlcude_directories(" + name + "\n";
    mData += (type == "INTERFACE" ? "\tINTERFACE\n" : "\tPUBLIC\n");
    mData += "\t\t${CMAKE_CURRENT_SOURCE_DIR}/include\n";
    mData += ")";

    return *this;
  }
} // namespace cli::utils

