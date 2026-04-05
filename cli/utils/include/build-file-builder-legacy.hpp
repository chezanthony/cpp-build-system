#ifndef BUILDFILEBUILDER_HPP
#define BUILDFILEBUILDER_HPP

#include <optional>
#include <string>
#include <string_view>

namespace cli::utils
{

  class BuildFileBuilderLegacy
  {
  public:
    BuildFileBuilderLegacy& writeProjectBuildFile(const std::string& name, std::optional<std::string> description);
    BuildFileBuilderLegacy& writeLibraryBuildFile(const std::string& name, std::string_view type);

private:
    std::string mData;
  };

} // namespace cli::utils

#include "build-file-builder.tpp"

#endif // BUILDFILEBUILDER_HPP

