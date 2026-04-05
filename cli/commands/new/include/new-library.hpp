#ifndef NEW_LIBRARY_HPP
#define NEW_LIBRARY_HPP

#include "base.hpp"
#include "new-types.hpp"
#include <filesystem>

namespace cli::commands
{

  class NewLibrary : public Base<NewLibrary, NewLibCommandOptions>
  {
  public:
    cli::core::ReturnType<void> executeImpl(const NewLibCommandOptions& options);

  private:
    cli::core::ReturnType<void> createBuildFile(const NewLibCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept;
    cli::core::ReturnType<void> createBuildFileLegacy(const NewLibCommandOptions& options, const std::filesystem::path& targetDirectory) const noexcept;
  };

} // namespace cli::commands

#include "new-library.tpp"

#endif // NEW_LIBRARY_HPP
