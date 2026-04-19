#ifndef NEW_BINARY_TPP
#define NEW_BINARY_TPP

#include "build-file-builder.hpp"
#include "constants.hpp"
#include "files-helper.hpp"
#include "new-binary.hpp"
#include "new-utils.hpp"
#include "types.hpp"
#include <filesystem>
#include <string>

namespace cli::commands
{

  cli::core::ReturnType<void> NewBinary::executeImpl(const NewBinCommandOptions& options)
  {
    const auto validDir = NewUtils::validateProject();
    if (!validDir.value_or(false))
    {
      return std::unexpected(cli::core::ErrorType{ cli::core::ErrorCodes::InvalidDirectory, "Directory is not a project." });
    }

    const std::filesystem::path targetDirectory = NewUtils::makeTargetDirectory(options.targetName);

    auto result = NewUtils::createDirectory(targetDirectory, "target");
    if (!result)
    {
      return result;
    }

    result = NewUtils::createDirectory(targetDirectory / constants::includeDirectory, "include");
    if (!result)
    {
      return result;
    }

    result = NewUtils::createDirectory(targetDirectory / constants::srcDirectory, "src");
    if (!result)
    {
      return result;
    }

    result = NewUtils::createPlaceholderFile(targetDirectory, true);
    if (!result)
    {
      result.error().message = "Error creating place holder file.";
      return result;
    }

    result = createBuildFile(options, targetDirectory);
    if (!result)
    {
      result.error().message = "Error creating toml file.";
      return result;
    }

    result = createBuildFileLegacy(options, targetDirectory);
    if (!result)
    {
      result.error().message = "Error creating cmake file.";
      return result;
    }

    result = NewUtils::updateBuildFileLegacy(targetDirectory);
    if (!result)
    {
      result.error().message = "Error updating cmake file.";
      return result;
    }

    return {};
  }

  cli::core::ReturnType<void> NewBinary::createBuildFile(const NewBinCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept
  {
    const std::filesystem::path buildFilePath = targetDirectory / constants::buildFileName;

    cli::utils::BuildFileBuilder fileBuilder;
    fileBuilder
      .writeHeader(constants::binaryHeader)
      .writeKeyValue(constants::targetNameKey, options.targetName)
      .writeKeyValueOptional(constants::targetDescriptionKey, options.targetDescription);

    fileBuilder.newLine();

    const std::string buildFileString{ std::move(fileBuilder).build() };
    return cli::utils::FilesHelper::createFileAndWrite(buildFilePath, buildFileString);
  }

  cli::core::ReturnType<void> NewBinary::createBuildFileLegacy(const NewBinCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept
  {
    const std::filesystem::path cmakeFilePath = targetDirectory / constants::cmakeFileName;

    std::string data;
    data += "add_executable(" + options.targetName + ")\n";
    data += "\n";
    data += "target_include_directories(" + options.targetName + "\n";
    data += "\tPUBLIC\n";
    data += "\t\t${CMAKE_CURRENT_SOURCE_DIR}/include\n";
    data += ")\n\n";

    data += NewUtils::buildSrcSegmentLegacy(options.targetName);

    return cli::utils::FilesHelper::createFileAndWrite(cmakeFilePath, data);
  }

} // namespace cli::commands

#endif // NEW_BINARY_TPP
