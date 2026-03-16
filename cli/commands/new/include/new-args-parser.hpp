#ifndef NEW_ARGS_PARSER_HPP
#define NEW_ARGS_PARSER_HPP

#include "base-args-parser.hpp"
#include <CLI/CLI.hpp>
#include <string>

namespace cli::commands
{

  class NewArgsParser : public BaseArgsParser<NewArgsParser>
  {
  public:
    void parseArgsImpl(CLI::App& app);

  private:
    bool mIsBin;
    bool mIsLib;
    std::string mTargetName;
    std::string mTargetDescription;
    bool mIsInterface;
    bool mIsStatic;
    bool mIsShared;
  };

} // namespace cli::commands

#include "new-args-parser.tpp"

#endif // NEW_ARGS_PARSER_HPP

