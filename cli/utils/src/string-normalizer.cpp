#include "string-normalizer.hpp"
#include <algorithm>
#include <cctype>

namespace cli::utils
{

  std::string StringNormalizer::normalizeDirectory(std::string directory)
  {
    std::transform(directory.begin(), directory.end(), directory.begin(), ::tolower);
    std::replace(directory.begin(), directory.end(), ' ', '-');
    return directory;
  }

} // namespace cli::utils

