#ifndef STRINGNORMALIZER_HPP
#define STRINGNORMALIZER_HPP

#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>

namespace cli::utils
{

  class StringNormalizer
  {
  public:
    static inline std::string normalizeDirectory(std::string_view directory)
    {
      std::string result{ directory };
      std::transform(result.begin(), result.end(), result.begin(), ::tolower);
      std::replace(result.begin(), result.end(), ' ', '-');
      return result;
    }
  };

} // namespace cli::utils

#endif // STRINGNORMALIZER_HPP
