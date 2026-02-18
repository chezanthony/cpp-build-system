#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>
#include <expected>
#include <string>

namespace cli::core
{

  enum class ErrorCodes : uint8_t
  {
    // Filesystem
    FileNotFound,
    FileExists,
    FailedToCreateFile,
    FailedToWriteFile,
    DirectoryNotFound,
    DirectoryExists,
    FailedToCreateDirectory,
    FailedToExecuteCommand,
  };

  struct ErrorType
  {
    ErrorCodes errorCode;
    std::string message;
  };

  template <typename T>
  using ReturnType = std::expected<T, ErrorType>;

} // namespace cli::core

#endif // !TYPES_HPP

