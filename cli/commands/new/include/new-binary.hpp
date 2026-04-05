#ifndef NEW_BINARY_HPP
#define NEW_BINARY_HPP

#include "base.hpp"
#include "new-types.hpp"
#include <filesystem>

namespace cli::commands
{

  class NewBinary : public Base<NewBinary, NewBinCommandOptions>
  {
  public:
    cli::core::ReturnType<void> executeImpl(const NewBinCommandOptions& options);

  private:
    cli::core::ReturnType<void> createBuildFile(const NewBinCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept;
    cli::core::ReturnType<void> createBuildFileLegacy(const NewBinCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept;
  };

} // namespace cli::commands

#include "new-binary.tpp"

#endif // NEW_BINARY_HPP
