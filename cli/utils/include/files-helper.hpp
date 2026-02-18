#ifndef FILESHELPER_HPP
#define FILESHELPER_HPP

#include "types.hpp"
#include <filesystem>
#include <string>

namespace cli::utils
{

  using Path = std::filesystem::path;
  template <typename T>
  using ReturnType = cli::core::ReturnType<T>;
  using ErrorCodes = cli::core::ErrorCodes;
  using ErrorType = cli::core::ErrorType;
  
  class FilesHelper
  {
  public:
    static ReturnType<void> createFile(const Path& filePath) noexcept;
    static ReturnType<void> createFileAndWrite(const Path& filePath, const std::string& data) noexcept;
    static bool fileExists(const Path& filePath) noexcept;
    static ReturnType<void> createDirectory(const Path& directory) noexcept;
    static bool directoryExists(const Path& directory) noexcept;
    static Path current_path(void) noexcept;
  };

} // namespace cli::utils

#endif // !FILESHELPER_HPP

