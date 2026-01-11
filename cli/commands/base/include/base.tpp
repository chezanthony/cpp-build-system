#include "base.hpp"

namespace cli
{

namespace commands
{

Base::execute(void)
{
  static_cast<Derived*>(this)->executeImpl();
}

Base::printHelp(void)
{
  static_cast<Derived*>(this)->helpImpl();
}

} // namespace commands

} // namespace cli

