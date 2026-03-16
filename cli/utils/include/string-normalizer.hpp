#ifndef STRINGNORMALIZER_HPP
#define STRINGNORMALIZER_HPP

#include <string>

namespace cli::utils
{

  class StringNormalizer
  {
  public:
    static std::string normalizeDirectory(std::string directory);
  };

} // namespace cli::utils

#endif // STRINGNORMALIZER_HPP

