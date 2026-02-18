#ifndef BASEBUILDFILEBUILDER_HPP
#define BASEBUILDFILEBUILDER_HPP

namespace cli::commands
{

  template <typename Derived, typename Options>
  class BaseBuildFileBuilder
  {
  public:
    void buildFile(const Options& options);
  };

} // namespace cli::commands

#include "base-build-file-builder.hpp"

#endif // !BASEBUILDFILEBUILDER_HPP

