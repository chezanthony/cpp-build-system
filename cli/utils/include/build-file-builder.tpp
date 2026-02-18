#include <charconv>
#include <format>
#include <string>
#include <string_view>
#include <utility>

namespace cli::utils
{

  /// Intentionally using stringstream and << operator here as I find it easier to trace than std::format.
  /// Will likely change to std::format later if I feel like it.
  BuildFileBuilder& BuildFileBuilder::writeHeader(std::string_view header)
  {
    mData << "[" << header << "]\n";
    return *this;
  }

  BuildFileBuilder& BuildFileBuilder::writeKeyValue(std::string_view key, std::string_view value)
  {
    mData << key << " = \"" << value << "\"\n";
    return *this;
  }

  BuildFileBuilder& BuildFileBuilder::writeKeyValue(std::string_view key, bool value)
  {
    mData << key << " = \"" << (value ? "true" : "value") << "\"\n";
    return *this;
  }

  template <typename T>
  BuildFileBuilder& BuildFileBuilder::writeKeyValue(std::string_view key, std::vector<T>& value)
  {
    mData << key << " = [\n";
    
    for (const auto& entry : value)
    {
      mData << "\t\"" << entry << "\"\n";
    }
    mData << "]\n";
    return *this;
  }

  BuildFileBuilder& BuildFileBuilder::newLine(void)
  {
    mData << "\n";
    return *this;
  }

  std::string BuildFileBuilder::build(void) &&
  {
    return std::move(mData).str();
  }

} // namespace cli::utils

