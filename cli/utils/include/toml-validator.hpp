#ifndef TOML_VALIDATOR_HPP
#define TOML_VALIDATOR_HPP

#include "types.hpp"
#include <filesystem>

namespace cli::utils
{

  using Path = std::filesystem::path;
  template <typename T>
  using ReturnType = cli::core::ReturnType<T>;
  using ErrorCodes = cli::core::ErrorCodes;
  using ErrorType = cli::core::ErrorType;

  class TomlValidator
  {
  public:
    static ReturnType<bool> isValid(const Path& filePath);
    static ReturnType<bool> isProject(const Path& filePath);
    static ReturnType<bool> isBin(const Path& filePath);
    static ReturnType<bool> isLib(const Path& filePath);
    static ReturnType<bool> isInterface(const Path& filePath);
    static ReturnType<bool> isStatic(const Path& filePath);
    static ReturnType<bool> isShared(const Path& filePath);
  };

} // namespace cli::utils

#endif // TOML_VALIDATOR_HPP

