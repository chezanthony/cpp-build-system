#include "constants.hpp"
#include "files-helper.hpp"
#include "types.hpp"
#include <expected>
#include <filesystem>
#include <fstream>

namespace cli::utils
{

  ReturnType<void> FilesHelper::createFile(const Path& filePath) noexcept
  {
    if (FilesHelper::fileExists(filePath))
    {
      return std::unexpected(ErrorType{ ErrorCodes::FileExists, "" });
    }
    
    std::ofstream file(filePath);

    if (!file)
    {
      return std::unexpected(ErrorType{ ErrorCodes::FailedToCreateFile, "" });
    }

    file.close();
    return {};
  }

  ReturnType<void> FilesHelper::createFileAndWrite(const Path& filePath, const std::string& data) noexcept
  {
    if (FilesHelper::fileExists(filePath))
    {
      return std::unexpected(ErrorType{ ErrorCodes::FileExists, "" });
    }
    
    std::ofstream file(filePath);

    if (!file)
    {
      return std::unexpected(ErrorType{ ErrorCodes::FailedToCreateFile, "" });
    }

    file << data;

    if (!file.good())
    {
      return std::unexpected(ErrorType{ ErrorCodes::FailedToWriteFile, "" });
    }

    return {};
  }

  bool FilesHelper::fileExists(const Path& filePath) noexcept
  {
    return (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath));
  }

  ReturnType<void> FilesHelper::createDirectory(const Path& directory) noexcept
  {
    if (FilesHelper::directoryExists(directory))
    {
      return std::unexpected(ErrorType{ ErrorCodes::DirectoryExists, "" });
    }

    if (!std::filesystem::create_directory(directory))
    {
      return std::unexpected(ErrorType{ ErrorCodes::FailedToCreateDirectory, "" });
    }

    return {};
  }

  bool FilesHelper::directoryExists(const Path& directory) noexcept
  {
    return std::filesystem::exists(directory);
  }

  Path FilesHelper::current_path(void) noexcept
  {
    return std::filesystem::current_path();
  }
} // namespace cli::utils
