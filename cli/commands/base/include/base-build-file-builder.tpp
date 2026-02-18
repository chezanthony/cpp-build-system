#ifndef BASEBUILDFILEBUILDER_TPP
#define BASEBUILDFILEBUILDER_TPP

namespace cli::commands
{

  template<typename Derived, typename Options>
  void BaseBuildFileBuilder<Derived, Options>::buildFile(const Options& options)
  {
    static_cast<Derived*>(this)->buildFileImpl(options);
  }

} // namespace cli::commands

#endif // 1BASEBUILDFILEBUILDER_TPP

