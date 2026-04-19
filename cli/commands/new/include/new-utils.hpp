#ifndef NEW_UTILS_HPP
#define NEW_UTILS_HPP

#include "constants.hpp"
#include "files-helper.hpp"
#include "string-normalizer.hpp"
#include "toml-validator.hpp"
#include "types.hpp"
#include <filesystem>
#include <string>
#include <string_view>

namespace cli::commands
{

  namespace constants = cli::core::constants;

  class NewUtils
  {
  public:
    NewUtils() = delete;

    static cli::core::ReturnType<bool> validateProject() noexcept;

    static std::filesystem::path makeTargetDirectory(std::string_view targetName) noexcept;

    static cli::core::ReturnType<void> createDirectory(const std::filesystem::path& directory, std::string_view label) noexcept;

    static cli::core::ReturnType<void> updateBuildFileLegacy(const std::filesystem::path& targetDirectory) noexcept;

    static cli::core::ReturnType<void> createPlaceholderFile(const std::filesystem::path& targetDirectory, const bool addMain) noexcept;

    static std::string buildSrcSegmentLegacy(std::string_view targetName) noexcept;
  };

} // namespace cli::commands

#endif // NEW_UTILS_HPP
