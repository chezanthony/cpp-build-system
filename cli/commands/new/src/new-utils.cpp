#include "constants.hpp"
#include "files-helper.hpp"
#include "new-utils.hpp"
#include "string-normalizer.hpp"
#include "toml-validator.hpp"
#include "types.hpp"
#include <filesystem>
#include <string>

namespace cli::commands
{

  cli::core::ReturnType<bool> NewUtils::validateProject() noexcept
  {
    const std::filesystem::path cwd{ cli::utils::FilesHelper::current_path() };
    const std::filesystem::path tomlFilePath{ cwd / constants::buildFileName };
    return cli::utils::TomlValidator::isProject(tomlFilePath);
  }

  std::filesystem::path NewUtils::makeTargetDirectory(std::string_view targetName) noexcept
  {
    const std::filesystem::path cwd{ cli::utils::FilesHelper::current_path() };
    return cwd / cli::utils::StringNormalizer::normalizeDirectory(targetName);
  }

  cli::core::ReturnType<void> NewUtils::createDirectory(const std::filesystem::path& directory, std::string_view label) noexcept
  {
    auto result = cli::utils::FilesHelper::createDirectory(directory);
    if (!result)
    {
      result.error().message = "Error creating " + std::string{ label } + " directory for target: " + directory.string();
    }
    return result;
  }

  cli::core::ReturnType<void> NewUtils::updateBuildFileLegacy(const std::filesystem::path& targetDirectory) noexcept
  {
    const std::filesystem::path cwd{ cli::utils::FilesHelper::current_path() };
    const std::filesystem::path cmakeFilePath = cwd / constants::cmakeFileName;
    const std::string data{ "add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/" + targetDirectory.filename().string() + ")\n\n" };
    return cli::utils::FilesHelper::appendToFile(cmakeFilePath, data);
  }

  cli::core::ReturnType<void> NewUtils::createPlaceholderFile(const std::filesystem::path& targetDirectory, const bool addMain) noexcept
  {
    const std::filesystem::path placeHolderFile{ targetDirectory / constants::srcDirectory / constants::placeHolderSrcFileName };
    if (addMain)
    {
      return cli::utils::FilesHelper::createFileAndWrite(placeHolderFile, "int main() { return 0; }\n");  
    }
  
    return cli::utils::FilesHelper::createFile(placeHolderFile);
  }

  std::string NewUtils::buildSrcSegmentLegacy(std::string_view targetName) noexcept
  {
    std::string data;
    data += "target_sources(" + std::string{ targetName } + "\n";
    data += "\tPRIVATE\n";
    data += "\t\t${CMAKE_CURRENT_SOURCE_DIR}/src/" + std::string{ constants::placeHolderSrcFileName } + "\n";
    data += ")\n\n";

    return data;
  }
} // namespace cli::commands

