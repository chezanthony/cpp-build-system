#ifndef BASE_HPP
#define BASE_HPP

namespace cli
{

namespace commands
{

template <typename Derived>
class Base
{
public:
  Base() = default;

  void execute(void)
  {
    static_cast<Derived*>(this)->executeImpl();
  }

  void printHelp(void)
  {
    static_cast<Derived*>(this)->printHelp();
  }
}; // class Base

} // namespace commands

} // namespace cli

#endif // BASE_HPP

