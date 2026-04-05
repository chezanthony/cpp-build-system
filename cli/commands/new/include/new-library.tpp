#ifndef NEW_LIBRARY_TPP
#define NEW_LIBRARY_TPP

#include "build-file-builder.hpp"
#include "constants.hpp"
#include "files-helper.hpp"
#include "new-library.hpp"
#include "new-utils.hpp"
#include "types.hpp"
#include <filesystem>
#include <string>
#include <unordered_map>

namespace cli::commands
{

  cli::core::ReturnType<void> NewLibrary::executeImpl(const NewLibCommandOptions& options)
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

    if (options.libType != LibType::interface)
    {
      result = NewUtils::createDirectory(targetDirectory / constants::srcDirectory, "src");
      if (!result)
      {
        return result;
      }
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

  cli::core::ReturnType<void> NewLibrary::createBuildFile(const NewLibCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept
  {
    const std::filesystem::path buildFilePath = targetDirectory / constants::buildFileName;
    const std::unordered_map<LibType, std::string_view> libTypeToString{
      { LibType::interface, constants::interfaceLibraryType },
      { LibType::staticLib, constants::staticLibraryType },
      { LibType::shared,    constants::sharedLibraryType },
    };

    cli::utils::BuildFileBuilder fileBuilder;
    fileBuilder
      .writeHeader(constants::libraryHeader)
      .writeKeyValue(constants::targetNameKey, options.targetName)
      .writeKeyValueOptional(constants::targetDescriptionKey, options.targetDescription)
      .writeKeyValue(constants::libraryTypeKey, libTypeToString.at(options.libType));

    fileBuilder.newLine();

    const std::string buildFileString{ std::move(fileBuilder).build() };
    return cli::utils::FilesHelper::createFileAndWrite(buildFilePath, buildFileString);
  }

  cli::core::ReturnType<void> NewLibrary::createBuildFileLegacy(const NewLibCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept
  {
    const std::filesystem::path cmakeFilePath = targetDirectory / constants::cmakeFileName;
    const std::unordered_map<LibType, std::string> libTypeToString{
      { LibType::interface, "INTERFACE" },
      { LibType::staticLib, "STATIC" },
      { LibType::shared,    "SHARED" },
    };
    const std::string scopeString{ options.libType == LibType::interface ? "INTERFACE" : "PUBLIC" };

    std::string data;
    data += "add_library(" + options.targetName + " " + libTypeToString.at(options.libType) + ")\n";
    data += "\n";
    data += "target_include_directories(" + options.targetName + "\n";
    data += "\t" + scopeString + "\n";
    data += "\t\t${CMAKE_CURRENT_SOURCE_DIR}/include\n";
    data += ")\n";

    return cli::utils::FilesHelper::createFileAndWrite(cmakeFilePath, data);
  }

} // namespace cli::commands

#endif // NEW_LIBRARY_TPP
