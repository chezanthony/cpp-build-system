#ifndef NEW_ARGS_PARSER_TPP
#define NEW_ARGS_PARSER_TPP

#include "new-binary.hpp"
#include "new-library.hpp"
#include "new-types.hpp"
#include <CLI/CLI.hpp>
#include <optional>

namespace cli::commands
{

  NewArgsParser::NewArgsParser() : 
    mIsInterface{ false }, 
    mIsStatic{ false },
    mIsShared{ false }
  {
  }

  void NewArgsParser::parseArgsImpl(CLI::App& app)
  {
    auto newSubcommand = app.add_subcommand("new", "Create new target: binary or library");
    newSubcommand->require_subcommand(1);

    auto binSubcommand = newSubcommand->add_subcommand("bin", "Create binary target");
    auto libSubcommand = newSubcommand->add_subcommand("lib", "Create library target");

    binSubcommand->add_option("name", this->mTargetName, "Target name")
                 ->required()
                 ->expected(1);
    binSubcommand->add_option("-d,--description", this->mTargetDescription, "Target description")
                 ->expected(1);

    libSubcommand->add_option("name", this->mTargetName, "Target name")
                 ->required()
                 ->expected(1);
    libSubcommand->add_option("-d,--description", this->mTargetDescription, "Target description")
                 ->expected(1);

    auto libTypeGroup = libSubcommand->add_option_group("Library type");
    libTypeGroup->add_flag("-i,--interface", this->mIsInterface, "Interface library");
    libTypeGroup->add_flag("-s,--static", this->mIsStatic, "Static library");
    libTypeGroup->add_flag("-S,--shared", this->mIsShared, "Shared library");
    libTypeGroup->require_option(0, 1);

    binSubcommand->callback([this]() {
      NewBinCommandOptions options{
        .targetName = this->mTargetName,
        .targetDescription = this->mTargetDescription.empty() ? std::nullopt : std::optional{ this->mTargetDescription },
      };
      NewBinary{}.execute(options);
    });

    libSubcommand->callback([this]() {
      LibType libType = LibType::interface;
      if (this->mIsStatic)
      {
        libType = LibType::staticLib;
      }
      else if (this->mIsShared)
      {
        libType = LibType::shared;
      }

      NewLibCommandOptions options{
        .targetName = this->mTargetName,
        .targetDescription = this->mTargetDescription.empty() ? std::nullopt : std::optional{ this->mTargetDescription },
        .libType = libType,
      };
      NewLibrary{}.execute(options);
    });
  }

} // namespace cli::commands

#endif // NEW_ARGS_PARSER_TPP
