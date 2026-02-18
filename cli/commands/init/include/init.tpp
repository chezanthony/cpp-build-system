#ifndef INIT_TPP
#define INIT_TPP

#include "build-file-builder.hpp"
#include "constants.hpp"
#include "exec-helper.hpp"
#include "files-helper.hpp"
#include "init-types.hpp"
#include "types.hpp"
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

namespace cli::commands
{

  namespace constants = cli::core::constants;

  ReturnType<void> Init::executeImpl(const InitCommandOptions& options)
  {
    const std::filesystem::path cwd = std::filesystem::current_path();

    auto result = createBuildFile(options);
    if (!result.has_value())
    {
      result.error().message = "Error creating toml file.";
      return result;
    }

    result = createBuildFileLegacy(options);
    if (!result.has_value())
    {
      result.error().message = "Error creating cmake file.";
      return result;
    }

    result = executeCommandLegacy(options);
    if (!result.has_value())
    {
      result.error().message = "Error initializing cmake project.";
      return result;
    }

    return {};
  }

  /// This is intentionally written in an imperative way as I find it easier to trace.
  /// This could be moved either to the << operator of the option type or a formatter specialization
  /// depending on whether I decidde to change build-file-builder to use std::formatter or not.
  ReturnType<void> Init::createBuildFile(const InitCommandOptions& options) const noexcept 
  {
    const std::filesystem::path cwd = std::filesystem::current_path();
    const std::filesystem::path buildFilePath = cwd / constants::buildFileName;

    cli::utils::BuildFileBuilder fileBuilder;
    fileBuilder
      .writeHeader(constants::projectHeader)
      .writeKeyValue(constants::projectNameKey, options.projectName);

    if (options.projectDescription.has_value())
    {
      fileBuilder
        .writeKeyValue(constants::projectDescription, options.projectDescription.value());
    }

    fileBuilder
      .writeKeyValue(constants::projectVersionKey, constants::initialVersionNumber)
      .writeKeyValue(constants::cppVersionKey, constants::defaultCppVersion)
      .newLine();
    
    const std::string buildFileString { std::move(fileBuilder).build() };

    return cli::utils::FilesHelper::createFileAndWrite(buildFilePath, buildFileString);
  }

  /// Not woried about how messy this is. This will be removed in phase 2.
  /// @todo: Remove in phase 2.
  ReturnType<void> Init::createBuildFileLegacy(const InitCommandOptions& options) const noexcept
  {
    const std::filesystem::path cwd = std::filesystem::current_path();
    const std::filesystem::path cmakeFilePath = cwd / constants::cmakeFileName;

    std::stringstream theStream;
    theStream
      << "cmake_minimum_required(VERSION 3.15)\n"
      << "\n"
      << "project(" << options.projectName << "\n"
      << "\tVERSION " << constants::initialVersionNumber << "\n";
    
    if (options.projectDescription.has_value())
    {
      theStream
        << "\tDESCRIPTION " << "\"" << options.projectDescription.value() << "\"\n";
    }

    theStream
      << "\tLANGUAGES CXX\n"
      << ")\n"
      << "\n";

    return cli::utils::FilesHelper::createFileAndWrite(cmakeFilePath, theStream.str());
  }

  /// @todo: Remove in phase 2.
  ReturnType<void> Init::executeCommandLegacy(const InitCommandOptions& options) const noexcept
  {
    return cli::utils::ExecHelper::executeCommand("cmake -B build");
  }

} // namespace cli::commands

#endif // !INIT_TPP

