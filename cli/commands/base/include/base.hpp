#ifndef BASE_HPP
#define BASE_HPP

namespace cli::commands
{

  template <typename Derived, typename Options>
  class Base
  {
  public:
    void execute(const Options& options);
  };

} // namespace cli::commands

#include "base.tpp"

#endif // BASE_HPP

