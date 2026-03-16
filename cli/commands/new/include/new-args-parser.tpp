#ifndef NEW_ARGS_PARSER_TPP
#define NEW_ARGS_PARSER_TPP

#include "new.hpp"
#include "new-types.hpp"
#include <CLI/CLI.hpp>
#include <optional>


namespace cli::commands
{
  
  void NewArgsParser::parseArgsImpl(CLI::App& app)
  {
    auto newSubcommand = app.add_subcommand("new", "Create new target: binary or library");

    this->mIsBin = false;
    this->mIsLib = false;
    this->mIsInterface = false;
    this->mIsStatic = false;
    this->mIsShared = false;

    auto type = newSubcommand->add_option_group("Target type");
    type->add_flag("-b,--bin", this->mIsBin, "Binary target");
    type->add_flag("-l,--lib", this->mIsLib, "Library target");
    type->require_option(1);
    
    newSubcommand->add_option("name", this->mTargetName, "Target name")
                 ->required()
                 ->expected(1);

    newSubcommand->add_option("-d,--description", this->mTargetDescription, "Target description")
              ->expected(1);

    auto flagLib = type->get_option("-l");
    auto libType = newSubcommand->add_option_group("Library type");
    libType->add_flag("-i,--interface", this->mIsInterface, "Interface library")
           ->needs(flagLib);
    libType->add_flag("-s,--static", this->mIsStatic, "Static library")
           ->needs(flagLib);
    libType->add_flag("-S,--shared", this->mIsShared, "Shared library")
           ->needs(flagLib);
    libType->require_option(0,1);

    newSubcommand->callback([this]() {
      NewCommandOptions options{
        .isBin = this->mIsBin,
        .targetName = this->mTargetName,
        .targetDescription = std::nullopt,
        .libType = LibType::interface,
      };

      if (!this->mTargetDescription.empty())
      {
        options.targetDescription = this->mTargetDescription;
      }

      if (this->mIsStatic)
      {
        options.libType = LibType::staticLib;
      }
      else if (this->mIsShared)
      {
        options.libType = LibType::shared;
      }

      New newCommand;
      newCommand.execute(options);
    });
  }

} // namespace cli::commands

#endif // NEW_ARGS_PARSER_TPP

