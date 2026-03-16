#include "constants.hpp"
#include "toml-validator.hpp"
#include <toml++/toml.hpp>

namespace cli::utils
{

  namespace constants = cli::core::constants;

  namespace
  {

    ReturnType<toml::table> parseToml(const Path& filePath)
    {
      try
      {
        return toml::parse_file(filePath.string());
      }
      catch (const toml::parse_error& e)
      {
        return std::unexpected(ErrorType{ ErrorCodes::FileNotFound, e.what() });
      }
    }

    bool isProjectInternal(const toml::table& table)
    {
      return table[constants::projectHeader].is_table();
    }

    bool isBinInternal(const toml::table& table)
    {
      return table[constants::binaryHeader].is_table();
    }

    bool isLibInternal(const toml::table& table)
    {
      return table[constants::libraryHeader].is_table();
    }

    bool isInterfaceInternal(const toml::table& table)
    {
      const auto type = table[constants::libraryHeader][constants::libraryTypeKey].value<std::string_view>();
      return constants::interfaceLibraryType == type;
    }

    bool isStaticInternal(const toml::table& table)
    {
      const auto type = table[constants::libraryHeader][constants::libraryTypeKey].value<std::string_view>();
      return constants::staticLibraryType == type;
    }

    bool isSharedInternal(const toml::table& table)
    {
      const auto type = table[constants::libraryHeader][constants::libraryTypeKey].value<std::string_view>();
      return constants::sharedLibraryType == type;
    }

  } // namespace

  ReturnType<bool> TomlValidator::isValid(const Path& filePath)
  {
    const auto table = parseToml(filePath);
    if (!table) return std::unexpected(table.error());
    return ( isProjectInternal(*table) || isBinInternal(*table) || isLibInternal(*table) );
  }

  ReturnType<bool> TomlValidator::isProject(const Path& filePath)
  {
    const auto table = parseToml(filePath);
    if (!table) return std::unexpected(table.error());
    return isProjectInternal(*table);
  }

  ReturnType<bool> TomlValidator::isBin(const Path& filePath)
  {
    const auto table = parseToml(filePath);
    if (!table) return std::unexpected(table.error());
    return isBinInternal(*table);
  }

  ReturnType<bool> TomlValidator::isLib(const Path& filePath)
  {
    const auto table = parseToml(filePath);
    if (!table) return std::unexpected(table.error());
    return isLibInternal(*table);
  }

  ReturnType<bool> TomlValidator::isInterface(const Path& filePath)
  {
    const auto table = parseToml(filePath);
    if (!table) return std::unexpected(table.error());
    return isInterfaceInternal(*table);
  }

  ReturnType<bool> TomlValidator::isStatic(const Path& filePath)
  {
    const auto table = parseToml(filePath);
    if (!table) return std::unexpected(table.error());
    return isStaticInternal(*table);
  }

  ReturnType<bool> TomlValidator::isShared(const Path& filePath)
  {
    const auto table = parseToml(filePath);
    if (!table) return std::unexpected(table.error());
    return isSharedInternal(*table);
  }

} // namespace cli::utils
