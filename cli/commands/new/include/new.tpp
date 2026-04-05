#ifndef NEW_TPP
#define NEW_TPP

#include "build-file-builder.hpp"
#include "constants.hpp"
#include "exec-helper.hpp"
#include "files-helper.hpp"
#include "new-types.hpp"
#include "toml-validator.hpp"
#include "string-normalizer.hpp"
#include "types.hpp"
#include <cstdio>
#include <filesystem>
#include <sstream>
#include <string>
#include <utility>
#include <unordered_map>

namespace cli::commands
{

  namespace constants = cli::core::constants;
  
  ReturnType<void> New::executeImpl(const NewCommandOptions& options)
  {
    const auto validDir = isDirectoryValid();
    if (!validDir.value_or(false))
    {
      return std::unexpected(ErrorType{ ErrorCodes::InvalidDirectory, "Directory is not a project." });
    }

    const std::filesystem::path cwd = std::filesystem::current_path();
    const std::filesystem::path targetDirectory = cwd / cli::utils::StringNormalizer::normalizeDirectory(options.targetName);

    auto result = createDirectories(options, targetDirectory);
    if(!result)
    {
      return result;
    }

    /// @todo: extract binary and library into their own class.
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

    result = updateBuildFileLegacy(options, cwd, targetDirectory);
    if (!result)
    {
      result.error().message = "Error updating cmake file.";
      return result;
    }

    return {};
  }

  /// This is intentionally written in an imperative way as I find it easier to trace.
  /// This could be moved either to the << operator of the option type or a formatter specialization
  /// depending on whether I decidde to change build-file-builder to use std::formatter or not.
  ReturnType<void> New::createBuildFile(const NewCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept
  {
    const std::filesystem::path buildFilePath = targetDirectory / constants::buildFileName;
    const std::unordered_map<LibType, std::string_view> libTypeToString{
      {LibType::interface, constants::interfaceLibraryType},
      {LibType::staticLib, constants::staticLibraryType},
      {LibType::shared,    constants::sharedLibraryType},
    };

    cli::utils::BuildFileBuilder fileBuilder;

    fileBuilder
      .writeHeader(options.isBin ? constants::binaryHeader : constants::libraryHeader)
      .writeKeyValue(constants::targetNameKey, options.targetName)
      .writeKeyValueOptional(constants::targetDescriptionKey, options.targetDescription)
      .writeKeyValuePredicate(constants::libraryTypeKey, libTypeToString.at(options.libType), !options.isBin);

    fileBuilder.newLine();

    const std::string buildFileString { std::move(fileBuilder).build() };
    return cli::utils::FilesHelper::createFileAndWrite(buildFilePath, buildFileString);
  }

  /// Not worried about how messy this is. This will be removed in phase 2.
  /// @todo: Remove in phase 2.
  ReturnType<void> New::createBuildFileLegacy(const NewCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept
  {
    const std::filesystem::path cmakeFilePath = targetDirectory / constants::cmakeFileName;

    const std::unordered_map<LibType, std::string> libTypeToString{{
      {LibType::interface, "INTERFACE"},
      {LibType::staticLib, "STATIC"},
      {LibType::shared, "SHARED"},
    }};
    const std::string libTypeString{ libTypeToString.at(options.libType) };
    std::string scopeString{ "PUBLIC" };
    if (!options.isBin && LibType::interface == options.libType)
    {
      scopeString = "INTERFACE";
    }

    std::string data;
    if (options.isBin)
    {
      data += "add_executable(" + options.targetName + ")\n";
    }
    else
    {
      data += "add_library(" + options.targetName +  " " + libTypeString + ")\n";
    }

    data += "\n";
    data += "target_include_directories(" + options.targetName + "\n";
    data += "\t" + scopeString + "\n";
    data += "\t\t${CMAKE_CURRENT_SOURCE_DIR}/include\n";
    data += ")";

    return cli::utils::FilesHelper::createFileAndWrite(cmakeFilePath, data);
  }

  /// @todo: Remove in phase 2.
  ReturnType<void> New::updateBuildFileLegacy(const NewCommandOptions& options, const std::filesystem::path& cwd, const std::filesystem::path& targetDirectory) const noexcept
  {
    const std::filesystem::path cmakeFilePath = cwd / constants::cmakeFileName;
    const std::string data{ "add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/" + targetDirectory.filename().string() + ")\n\n" };

    return cli::utils::FilesHelper::appendToFile(cmakeFilePath, data);
  }

  ReturnType<bool> New::isDirectoryValid() const noexcept
  {
    const std::filesystem::path cwd{ cli::utils::FilesHelper::current_path() };
    const std::filesystem::path tomlFilePath{ cwd / constants::buildFileName };

    return cli::utils::TomlValidator::isProject(tomlFilePath);
  }

  ReturnType<void> New::createDirectories(const NewCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept
  {
    auto result = cli::utils::FilesHelper::createDirectory(targetDirectory.string());
    if(!result)
    {
      result.error().message = "Error creating directory for target: " + targetDirectory.string();
      return result;
    }

    const std::filesystem::path targetIncludeDirectory{ targetDirectory / constants::includeDirectory };
    result = cli::utils::FilesHelper::createDirectory(targetIncludeDirectory.string());
    if(!result)
    {
      result.error().message = "Error creating include directory for target: " + targetIncludeDirectory.string();
      return result;
    }
  
    if(!options.isBin && LibType::interface == options.libType)
    {
      return result;
    }

    const std::filesystem::path targetSrcDirectory{ targetDirectory / constants::srcDirectory };
    result = cli::utils::FilesHelper::createDirectory(targetSrcDirectory.string());
    if(!result)
    {
      result.error().message = "Error creating src directory for target: " + targetSrcDirectory.string();
    }
    
    return result;
  }
} // namespace cli::commands

#endif // NEW_TPP

