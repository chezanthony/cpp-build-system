#ifndef INIT_ARGS_PARSER_TPP
#define INIT_ARGS_PARSER_TPP

#include "init.hpp"
#include "init-types.hpp"
#include <CLI/CLI.hpp>
#include <iostream>
#include <optional>

namespace cli::commands
{

  void InitArgsParser::parseArgsImpl(CLI::App& app)
  {
    auto init = app.add_subcommand("init", "Initialize directory into a project");
  
    this->mIsEmpty = false;
    this->mIsLib = false;
    this->mIsBin = false;
  
    auto mode = init->add_option_group("Project type");
    mode->add_flag("-e,--empty", this->mIsEmpty, "Empty project");
    mode->add_flag("-l,--lib", this->mIsLib, "Lib project");
    mode->add_flag("-b,--bin", this->mIsBin, "Bin project");
    mode->require_option(0, 1);
  
    init->add_option("name", this->mProjectName, "Project Name")
        ->required()
        ->expected(1);

    init->add_option("-d,--description", this->mProjectDescription, "Project Description")
        ->expected(1);
  
    auto libNameOpt = 
      init->add_option("--lib-name", this->mLibName, "Library Name (defaults to project name)")
          ->expected(1);
    auto binNameOpt = 
      init->add_option("--bin-name", this->mBinName, "Binary Name (defaults to project name)")
          ->expected(1);
  
    libNameOpt->needs("-l");
    binNameOpt->needs("-b");
  
    init->callback([this]() {
      InitCommandOptions options{
        .initType = InitType::Empty,
        .projectName = this->mProjectName,
        .projectDescription = std::nullopt,
        .targetName = this->mProjectName,
      };

      if (!this->mProjectDescription.empty())
      {
        options.projectDescription = this->mProjectDescription;
      }
  
      if (this->mIsLib)
      {
        options.initType = InitType::Lib;
        options.targetName = this->mLibName.empty() ? this->mProjectName : this->mLibName;
      }
  
      if (this->mIsBin)
      {
        options.initType = InitType::Bin;
        options.targetName = this->mBinName.empty() ? this->mProjectName : this->mBinName;
      }
  
      Init initCommand{};
      initCommand.execute(options);
    });
  }

} // namespace cli::commands

#endif // !INIT_ARGS_PARSER_TPP

