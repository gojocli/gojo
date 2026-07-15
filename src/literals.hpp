#ifndef GOJO_SRC_LITERALS_HPP
#define GOJO_SRC_LITERALS_HPP

#include <string_view>


namespace literals {

// {0} CLEAR
// {1} MAGENTA_BOLD
// {2} MAGENTA
// {3} YELLOW
// {4} CYAN

constexpr std::string_view HELP { 
R"(
{1}Gojo:{0} a C/C++ CLI

{1}Usage:{0} gojo {2}<command>{0} {3}<arg(s)>{0} {4}[options]{0}

{1}Commands:{0}
    {2}init{0} {3}<name>{0} {4}[-f | -i | ...]{0}     create a new gojo project in the current directory
    {2}build{0} {4}[--release | ...]{0}         build project
    {2}run{0} {4}[options]{0}                   run compiled executable
    {2}test{0} {4}[--target=<target>]{0}        run unit test(s)
    {2}clean{0} {4}[--deep | --all]{0}          clean build directory caches
    {2}fmt{0} {4}[options]{0}                   auto-format your code
    {2}check{0} {4}[--verbose]{0}               run static code analyzers
    {2}template{0}                        create a .gojo config file template in the current directory
    {2}refresh{0} {4}[--deps]{0}                reconfigure project with updated an updated .gojo config file
    {2}install{0}                         install dependencies with the selected package manager
    {2}info{0}                            print the manual page for gojo
    {2}help{0}                            print help

See 'gojo {2}<command>{0} {4}--help{0}' for more information on a specific command
)"
};


constexpr std::string_view INIT_HELP {
R"({1}Command:{0}
  gojo {2}init{0} {3}<name>{0} {4}[options]{0}

{1}Summary:{0}
  Create a new gojo project in the current directory. A name arguemnt
  is required. If no options are supplied, a default C++ project is
  created. The settings for a default C++ project can be found in the
  'gojo info' command.

{1}Arguments:{0}
  {3}name{0}            Name of the gojo project to be created.

{1}Options:{0}
  {4}--file | -f{0}       Create a new gojo project using a .gojo config
                    file located in the current directory. This option
                    syngergizes well with 'gojo template'. All other
                    arguments and options are ignored when using --file,
                    including <name>. This command will fail if no .gojo
                    config file is found in the current directory.

  {4}-i{0}                Create a new gojo project by answering several
                    interactive prompts. All other arguments and options
                    are ignored when using -i, including <name>.

  {4}--lib{0}             Set the project to be a library. By default, a new
                    gojo project is a binary executable.

  {4}--lang=<c|c++>{0}    Set the language of the project. The language options
                    are 'c' or 'c++'. By default, a new gojo project is C++.

  {4}--profile=<name>{0}  Create a new gojo project from an existing profile.
                    The profile must exist. When combining this option with
                    options, this one must come first, ie
                    gojo init --profile=default --lib
)"
};


constexpr std::string_view BUILD_HELP {
R"({1}Command:{0}
  gojo {2}build{0} {4}[options]{0}

{1}Summary:{0}
  Compile the project. By default, all targets are built in debug mode using
  the compiler flags set in the .gojo config file located at the root of the
  project.

{1}Options:{0}
  {4}--release{0}         Compile the project with all compiler optimizations
                    enabled, namely -03. If the project is currently set
                    to debug mode, it will be reconfigured before
                    compilation. If the project is already in release mode,
                    this option has no effect. No debug symbol information
                    is kept when compiled in release mode, unless
                    overidden with specific compiler flags set in the
                    .gojo config file of the project.

  {4}--debug{0}           Compile the project with debug symbols and zero
                    compiler optimizations enabled. If the project is
                    currently set to release mode, it will be reconfigured
                    before compilation. If the project is already in debug
                    mode, this option has no effect.

  {4}--tests{0}           Enable testing in the project and compile unit tests
                    along with the source code. If the project currently
                    does not have testing enabled, it will be reconfigured
                    before compilation. If the project already has testing
                    enabled, this option has no effect.

  {4}--no-tests{0}        Disable testing in the project and omit unit tests from
                    the compilation process. If the project currently has
                    testing enabled, it will be reconfigured before
                    compilation. If the project currently does not have
                    testing enabled, this option has no effect.

  {4}--clean{0}           Clean the build artifacts and caches before compilation.

  {4}--target=<target>{0} Compile only a specific target instead of the whole
                    project.
)"
};


constexpr std::string_view RUN_HELP {
R"({1}Command:{0}
  gojo {2}run{0} {4}[options]{0}

{1}Summary:{0}
  Run the compiled executable produced by the project. A call to 'gojo build'
  must be successfully completed before running this command. This command
  has no effect if the project is a library. This command uses the 'executable
  name' field in the .gojo config file of the project in order to find the
  correct executable to run, and will fail if it cannot find an executable with
  that name.

{1}Options:{0}
  Any options passed to this command will be forwarded to the executable.             
)"
};


constexpr std::string_view TEST_HELP {
R"({1}Command:{0}
  gojo {2}test{0} {4}[options]{0}

{1}Summary:{0}
  Run unit tests in the project. Tests must be enabled in the .gojo config
  file and a call to 'gojo build' must be successfully completed before
  running this command.

{1}Options:{0}
  {4}--target=<target>{0} Test only a specific target intead of all unit tests.
)"
};


constexpr std::string_view CLEAN_HELP {
R"({1}Command:{0}
  gojo {2}clean{0} {4}[options]{0}

{1}Summary:{0}
  Remove build artifacts and/or caches.

{1}Options:{0}
  {4}--deep{0}          Remove all build artifacts and caches from the,
                  project, while keeping dependencies intact.

  {4}--all{0}           Remove everything from the build directory, including
                  dependencies. Use this option with caution as it
                  requires dependencies to be reinstalled and rebuilt,
                  and the project has to be re-configured.
)"
};


constexpr std::string_view FMT_HELP {
R"({1}Command:{0}
  gojo {2}fmt{0} {4}[options]{0}

{1}Summary:{0}
  Format the project using clang-format. By default, this command uses the
  .clang-format file found in the root of the project created by 'gojo init'.
  If no file is found and no options are supplied, this command has no effect.
  Any options supplied to this command are forwarded directly to clang-format
  and override any settings in the .clang-format file. By default, code is
  auto formatted and changed in-place according the rules laid out in the
  .clang-format file. More information on clang-format can be found here:
  https://clang.llvm.org/docs/ClangFormat.html

{1}Options:{0}
  Any options supplied to this command are forwarded to clang-format and
  override any rules set in the .clang-format file, if it exists.
)"
};


constexpr std::string_view CHECK_HELP {
R"({1}Command:{0}
  gojo {2}check{0} {4}[options]{0}

{1}Summary:{0}
  Run static analysis checks on the code without building the project. There
  are two programs used to run static analysis checks, clang-tidy and
  cppcheck. Both can be enabled or disabled in the .gojo config file located
  at the root of the project. If neither program is enabled, this command has
  no effect. clang-tidy can be configured with the .clang-tidy file located
  at the root of the project, created by 'gojo init' if enabled. Additionally,
  command line arguments can be supplied in the .gojo config file at the root
  of the project using the 'clang-tidy arguments' field, which will take
  precedence over the .clang-tidy file. More information on clang-tidy can be
  found here: https://clang.llvm.org/extra/clang-tidy/
  cppcheck can be configured in the .gojo config file located in the root of
  the project using the 'cppcheck checks enabled' and 'cppcheck arguments'
  fields. The former decides which checks will be run and the latter is used
  to pass any command line options to cppcheck. More information on cppcheck
  can be found here: https://cppcheck.sourceforge.io/manual.html

{1}Options:{0}
  {4}--verbose | -v{0}  Print all output from the static analyzers enabled
                  in the project. By default, only errors are printed.
)"
};


constexpr std::string_view TEMPLATE_HELP {
R"({1}Command:{0}
  gojo {2}template{0}

{1}Summary:{0}
  Create an empty template for a .gojo config file in the current directory.
  This command synergizes well with 'gojo init --file' to create a new project
  using the settings laid out in a .gojo config file. See 'gojo info' for more
  information on the .gojo config file.
)"
};


constexpr std::string_view REFRESH_HELP {
R"({1}Command:{0}
  gojo {2}refresh{0} {4}[options]{0}

{1}Summary:{0}
  Read the .gojo config file located at the root of the project and reconfigure
  the project. This command is necessary when changing the following fields in
  the .gojo config file:

    - 'language standard'
    - 'gnu extensions'
    - 'compiler'
    - 'compiler flags'
    - 'generator'
    - 'build type'
    - 'testing enabled'

{1}Options:{0}
  {4}--profile=<name>{0}   Configure the project with an existing gojo profile.
                     The profile must exist.
)"
};


constexpr std::string_view INSTALL_HELP {
R"({1}Command:{0}
  gojo {2}install{0}

{1}Summary:{0}
  Install and build dependencies in both debug and release mode. They are
  built in both modes to allow seamless switching between build types in
  the project without having to rebuild upon a switch. This command is
  necessary if dependencies have been added or removed from the dependency
  list in either the conanfile.py or vcpkg files. This command has no effect
  if the package manager is set to 'none' in the project.
)"
};


constexpr std::string_view PROFILE_HELP {
R"({1}Command:{0}
  gojo {2}profile{0} {4}[options]{0}

{1}Summary:{0}
  Manage global gojo profiles. Some options require arguemnts to work. Profiles
  are stored in ~/.gojocli/profiles as .gojo config files.

{1}Options{0}
  {4}create{0} {3}<name>{0}    Create a new gojo profile with the specified
                   name. The name arguemnt is required.

  {4}list{0}             List all of the current gojo profiles found in
                   the system.

  {4}show{0} {3}<name>{0}      Show the gojo profile with the specified name.

  {4}delete{0} {3}<name>{0}    Delete a gojo profile with the specified name.
                   specify 'all' to delete all gojo profiles.
)"
};


constexpr std::string_view INFO {
R"(
)"
};


constexpr std::string_view WIN { R"({2}
⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⣾⡳⣼⣆⠀⠀⢹⡄⠹⣷⣄⢠⠇⠻⣷⣶⢀⣸⣿⡾⡏⠀⠰⣿⣰⠏⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⣀⣀⣀⡹⣟⡪⢟⣷⠦⠬⣿⣦⣌⡙⠿⡆⠻⡌⠿⣦⣿⣿⣿⣿⣦⣿⡿⠟⠚⠉⠀⠉⠳⣄⡀⠀⠀⠁⠀
⠀⠀⠀⠀⠀⠀⠀⡀⢀⣼⣟⠛⠛⠙⠛⠉⠻⢶⣮⢿⣯⡙⢶⡌⠲⢤⡑⠀⠈⠛⠟⢿⣿⠛⣿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣆⠀⠀⠀
⠀⠀⠀⠀⠀⡸⠯⣙⠛⢉⣉⣙⣿⣿⡳⢶⣦⣝⢿⣆⠉⠻⣄⠈⢆⢵⡈⠀⠀⢰⡆⠀⣼⠓⠀⠀⠀ Nah,    ⠀⠈⣷⠀⠀
⠀⠀⠀⠖⠉⠻⣟⡿⣿⣭⢽⣽⣶⣈⢛⣾⣿⣧⠀⠙⠓⠀⠑⢦⡀⠹⣧⢂⠀⣿⡇⢀⣿⠺⠇⠀  I'd        ⣿⠀⠀
⠀⠀⠀⠀⠐⠈⠉⢛⣿⣿⣶⣤⣈⠉⣰⣗⡈⢛⣇⠀⣵⡀⠀⠘⣿⡄⢻⣤⠀⢻⡇⣼⣧⣿⡄⠀⠀ Win      ⠀⠀⡿⠀⠀
⠀⠀⠀⠀⠀⣠⣾⣿⢍⡉⠛⠻⣷⡆⠨⣿⣭⣤⣍⠀⢹⣷⡀⠀⠹⣿⡄⠈⠀⢿⠁⣿⣿⠏⠀⠀⠀            ⣇⠀⠀
⠀⣿⣇⣠⣾⣿⣛⣲⣿⠛⠀⠀⢀⣸⣿⣿⣟⣮⡻⣷⣤⡙⢟⡀⠀⠙⢧⠀⠀⠎⠀⠉⠁⠰⣿⠀⠀          ⢀⡿⠀⠀
⠀⠈⢻⣿⣿⣽⣿⣿⣿⣴⡏⠚⢛⣈⣍⠛⠛⠿⢦⣌⢙⠻⡆⠁⠀⠀⠀⣴⣦⠀⠀⠀⠐⢳⢻⣦⣀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠮⠀⠀⠀
⠀⠀⠈⠙⣿⣧⣶⣿⠿⣧⣴⣿⢻⡉⠀⢀⣠⣴⣾⡟⠿⠃⠁⣠⣤⡶⣾⡟⠅⠀⣀⡄⠀⣾⢸⣿⣏⢻⢶⣦⣤⣤⣄⢶⣾⣿⣡⣤⡄⠀
⠀⠀⣠⣞⣋⣿⣿⣾⣿⡿⡛⣹⡟⣤⢰⡿⠟⠉⣀⣀⣤⣤⡠⠙⢁⣾⡿⠂⠀⣿⠟⣁⠀⣹⠀⣹⣿⡟⣼⣿⣿⣌⣿⣞⣿⣿⠁⠀⠀⠀
⠀⢠⡿⢛⢟⣿⣿⣿⣿⣿⣿⡟⣼⣿⣟⢓⠛⣿⣏⣿⣵⣗⣵⣴⣿⢟⡵⣣⣼⣿⢟⣵⣶⢻⣶⣿⠀⠀⣈⢻⣿⣿⣿⢿⣾⢿⣧⠀⠀⠀
⠀⠘⠃⢸⣿⡾⣿⣿⣿⣿⣯⣿⣿⣿⣶⣿⣿⣟⣾⡿⣫⣿⣿⣿⣽⣿⣿⣿⣿⢫⣾⣿⣿⣿⣿⣿⣴⡆⣻⣿⡏⣿⢻⣧⣿⡿⣿⡆⠀⠀
⠀⠀⠀⠜⣿⣾⢿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣭⣿⣖⣿⢿⣿⡿⣿⣿⣿⡿⢡⢯⣿⣿⣿⣿⣿⣿⣿⣧⡿⣾⣷⣿⣿⢿⣿⡇⠉⠁⠀⠀
⠀⠀⠀⠀⣿⣥⣾⣿⣿⣿⣿⣿⣿⣿⡇⣭⣿⣿⣿⣿⠃⠞⠟⣸⣿⠏⣸⣧⣀⠿⢿⣿⣿⣟⣿⣿⣿⣿⣽⣿⢿⣿⣿⣿⣿⠁⠀⠀⠀⠀
⠀⠀⠀⠈⠛⣹⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⣟⣿⣿⡿⢶⣦⣄⣿⠏⠀⣿⣟⣿⣶⠾⣿⣟⣋⣛⣿⣿⣿⣿⡇⣻⣿⣿⣿⡏⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠟⠛⠫⣿⣿⣿⣿⣿⡿⣧⠛⣿⠛⣿⣿⣿⣷⡌⠹⡟⠀⠀⠉⡟⠋⢠⣾⣿⣿⣿⡟⣿⣿⣿⣿⢀⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠘⠋⣾⣷⣿⣿⣧⠙⠀⠙⢣⠝⠛⠋⣽⣷⢦⠇⠀⠀⠘⠁⣤⣾⣿⠝⠛⠉⠘⢻⣿⣿⢿⣼⣷⡟⢻⣷⠉⠀⡀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠐⠟⢻⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠈⠛⠀⠀⠀⠀⠀⣾⠟⠀⢸⣷⣿⡇⠀⠛⠀⠀⠁⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠁⠀⢹⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⡧⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠆⠀⠀⠀⠀⠀⠀⠈⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⢻⡿⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣇⠀⠀⠀⠀⠀⠀⠀⠀⠲⣄⠀⡄⠆⠀⠀⠀⠀⠀⠀⠀⠀⣼⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⣀⠀⠀⣠⣾⣿⠁⠀⠀⠀⠀⠀⣀⡄⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⢻⣆⠀⠛⠁⠶⣶⣶⣶⣶⣶⣶⡶⠆⠘⠋⣠⡾⢫⣾⡟⠀⠀⠀⠀⠀⠐⠉⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠛⠀⠙⣷⡀⠀⠀⠙⠛⠛⠛⠛⠋⠁⠀⢀⣴⠋⠀⣾⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣿⣰⣦⡀⠸⣿⣦⡀⠀⠀⠀⠀⠀⠀⢀⣴⡟⠁⠀⠐⢻⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣾⣿⣿⣿⡄⢺⣿⡄⠹⣿⠻⢦⣤⣤⣤⣤⣶⣿⡟⢀⣀⠀⠀⢸⣿⣦⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢀⣠⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣮⣿⣿⡀⠹⡷⣦⣀⡀⡀⢸⣿⠏⢠⣾⣿⠀⠀⣾⣿⣿⣿⣿⣶⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀
⣀⣤⣴⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠘⣷⣻⡟⠀⡼⠁⣴⣿⣿⣯⣥⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⣀⠀⠀⠀⠀
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣯⣿⣤⣤⣤⣬⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⣄
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿{0}

{1}"Throughout Heaven and Earth, I alone am the honored one."{0}
)"
};


constexpr std::string_view GITIGNORE = R"(CMakeLists.txt.user
CMakeCache.txt
CMakeFiles
CMakeScripts
Testing
Makefile
cmake_install.cmake
install_manifest.txt
compile_commands.json
CTestTestfile.cmake
_deps
CMakeUserPresets.json
build)";

}  // namespace literals

#endif
