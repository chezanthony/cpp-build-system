#ifndef BASE_TPP
#define BASE_TPP

#include "types.hpp"
#include <iostream>

namespace cli::commands
{

  template<typename Derived, typename Options>
  void Base<Derived, Options>::execute(const Options& options)
  {
    cli::core::ReturnType<void> result = static_cast<Derived*>(this)->executeImpl(options);

    using ErrorType = cli::core::ErrorType;
    using ErrorCodes = cli::core::ErrorCodes;

    if (!result.has_value())
    {
      std::cout << "Error: ";

      switch (result.error().errorCode)
      {
      case ErrorCodes::FileExists:
        std::cout << "File exists: ";
        break;
      case ErrorCodes::FileNotFound:
        std::cout << "File not found: ";
        break;
      case ErrorCodes::FailedToCreateFile:
        std::cout << "Failed to create file: ";
        break;
      case ErrorCodes::DirectoryExists:
        std::cout << "Directory exists: ";
        break;
      case ErrorCodes::InvalidDirectory:
        std::cout << "Invalid directory: ";
        break;
      default:
        std::cout << "Unknown: ";
      }

      std::cout << result.error().message << "\n";
    }
  }
  
} // namespace cli::commands

#endif // !BASE_TPP

