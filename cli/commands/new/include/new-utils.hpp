#ifndef NEW_UTILS_HPP
#define NEW_UTILS_HPP

#include "constants.hpp"
#include "files-helper.hpp"
#include "string-normalizer.hpp"
#include "toml-validator.hpp"
#include "types.hpp"
#include <filesystem>
#include <string_view>

namespace cli::commands
{

  namespace constants = cli::core::constants;

  class NewUtils
  {
  public:
    static inline cli::core::ReturnType<bool> validateProject() noexcept
    {
      const std::filesystem::path cwd{ cli::utils::FilesHelper::current_path() };
      const std::filesystem::path tomlFilePath{ cwd / constants::buildFileName };
      return cli::utils::TomlValidator::isProject(tomlFilePath);
    }

    static inline std::filesystem::path makeTargetDirectory(std::string_view targetName) noexcept
    {
      const std::filesystem::path cwd{ cli::utils::FilesHelper::current_path() };
      return cwd / cli::utils::StringNormalizer::normalizeDirectory(targetName);
    }

    static inline cli::core::ReturnType<void> createDirectory(const std::filesystem::path& directory, std::string_view label) noexcept
    {
      auto result = cli::utils::FilesHelper::createDirectory(directory);
      if (!result)
      {
        result.error().message = "Error creating " + std::string{ label } + " directory for target: " + directory.string();
      }
      return result;
    }

    static inline cli::core::ReturnType<void> updateBuildFileLegacy(const std::filesystem::path& targetDirectory) noexcept
    {
      const std::filesystem::path cwd{ cli::utils::FilesHelper::current_path() };
      const std::filesystem::path cmakeFilePath = cwd / constants::cmakeFileName;
      const std::string data{ "add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/" + targetDirectory.filename().string() + ")\n\n" };
      return cli::utils::FilesHelper::appendToFile(cmakeFilePath, data);
    }
  };

} // namespace cli::commands

#endif // NEW_UTILS_HPP
