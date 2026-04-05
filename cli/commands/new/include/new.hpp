#ifndef NEW_HPP
#define NEW_HPP

#include "base.hpp"
#include "new-types.hpp"
#include "types.hpp"
#include <filesystem>

namespace cli::commands
{

  template <typename T>
  using ReturnType = cli::core::ReturnType<T>;
  using ErrorCodes = cli::core::ErrorCodes;
  using ErrorType = cli::core::ErrorType;

  class New : public Base<New, NewCommandOptions>
  {
  public:
    ReturnType<void> executeImpl(const NewCommandOptions& options);

  private:
    ReturnType<bool> isDirectoryValid() const noexcept;
    ReturnType<void> createDirectories(const NewCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept;
    ReturnType<void> createBuildFile(const NewCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept;
    ReturnType<void> createBuildFileLegacy(const NewCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept;
    ReturnType<void> updateBuildFileLegacy(const NewCommandOptions& options, const std::filesystem::path& cwd, const std::filesystem::path& targetDirectory) const noexcept;
    ReturnType<void> executeCommandLegacy(const NewCommandOptions& options) const noexcept;
  };

} // namespace cli::commands

#include "new.tpp"

#endif // NEW_HPP

