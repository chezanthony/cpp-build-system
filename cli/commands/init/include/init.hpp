#ifndef INIT_HPP
#define INIT_HPP

#include "base.hpp"
#include "init-types.hpp"
#include "types.hpp"

namespace cli::commands
{

  template <typename T>
  using ReturnType = cli::core::ReturnType<T>;
  using ErrorCodes = cli::core::ErrorCodes;
  using ErrorType = cli::core::ErrorType;

  class Init : public Base<Init, InitCommandOptions>
  {
  public:
    ReturnType<void> executeImpl(const InitCommandOptions& options);

  private:
    void handleBuildFileExists(void) const noexcept;
    ReturnType<void> createBuildFile(const InitCommandOptions& options) const noexcept;
    ReturnType<void> createBuildFileLegacy(const InitCommandOptions& options) const noexcept;
    ReturnType<void> executeCommandLegacy(const InitCommandOptions& options) const noexcept;
  };

} // namespace cli::commands

#include "init.tpp"

#endif // !INIT_HPP

