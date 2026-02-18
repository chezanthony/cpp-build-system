#ifndef INIT_ARGS_PARSER_HPP
#define INIT_ARGS_PARSER_HPP

#include "base-args-parser.hpp"
#include <CLI/CLI.hpp>
#include <string>

namespace cli::commands
{

  class InitArgsParser : public BaseArgsParser<InitArgsParser>
  {
  public:
    void parseArgsImpl(CLI::App& app);
  private:
    std::string mProjectName;
    std::string mProjectDescription;
    std::string mLibName;
    std::string mBinName;
    bool mIsEmpty;
    bool mIsLib;
    bool mIsBin;
  };

} // namespace cli::commands

#include "init-args-parser.tpp"

#endif // !INIT_ARGS_PARSER_HPP

