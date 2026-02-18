#ifndef BUILDFILEBUILDER_HPP
#define BUILDFILEBUILDER_HPP

#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace cli::utils
{

  class BuildFileBuilder
  {
  public:
    BuildFileBuilder& writeHeader(std::string_view header);
    BuildFileBuilder& writeKeyValue(std::string_view key, std::string_view value);
    BuildFileBuilder& writeKeyValue(std::string_view key, bool value);

    template <typename T>
    BuildFileBuilder& writeKeyValue(std::string_view key, std::vector<T>& value);

    BuildFileBuilder& newLine(void);
    std::string build(void) &&;

  private:
    std::stringstream mData;
  };

} // namespace cli::utils

#include "build-file-builder.tpp"

#endif // !BUILDFILEBUILDER_HPP

