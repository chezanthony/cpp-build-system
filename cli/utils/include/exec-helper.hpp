#ifndef EXECHELPER_HPP
#define EXECHELPER_HPP

#include "types.hpp"
#include <string>

namespace cli::utils
{

  template <typename T>
  using ReturnType = cli::core::ReturnType<T>;
  using ErrorCodes = cli::core::ErrorCodes;
  using ErrorType = cli::core::ErrorType;

  class ExecHelper
  {
  public:
    static ReturnType<void> executeCommand(const std::string& command) noexcept;
  };

} // namespace cli::utils

#endif // !EXECHELPER_HPP

