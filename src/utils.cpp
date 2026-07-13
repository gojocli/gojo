#include "src/utils.hpp"

#include <array>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <format>
#include <print>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/wait.h>
#include <unistd.h>
#include <utility>
#include <vector>

#if defined(__APPLE__)
  #include <sys/_types/_pid_t.h>
  #include <sys/_types/_ssize_t.h>
#endif

#if defined(__linux__)
  #include <sys/types.h>
#endif


namespace {

std::vector<std::string> split_args(const std::string& args_str) {
  std::vector<std::string> args_vec {};
  std::string arg {};
  std::stringstream ss { args_str };

  while (std::getline(ss, arg, ' ')) {
    args_vec.emplace_back(arg);
  }

  return args_vec;
}

std::vector<char*> args_c_str(std::vector<std::string>& args) {
  std::vector<char*> args_c_str {};
  args_c_str.reserve(args.size());

  for (auto& arg : args) {
    args_c_str.emplace_back(arg.data());
  }
  args_c_str.emplace_back(nullptr);

  return args_c_str;
}

}  // namespace

namespace utils {

CommandResult execute_command(const std::string& cmd, bool capture_output) {
  // Open pipe to pass data between parent and child process.
  std::array<int, 2> pipefd {};
  if (pipe(pipefd.data()) == -1) {
    return CommandResult { 
      .output="failed to open inter-process pipe",
      .success=false
    };
  }

  std::fflush(nullptr);
  // Fork a new child process to run the command.
  const pid_t pid { fork() };
  if (pid == -1) {
    return CommandResult {
      .output="failed to fork process",
      .success=false
    };
  }

  if (pid == 0) {
    // Child process
    // Connect stdout of the child process to the write end of the pipe.
    dup2(pipefd.at(1), STDOUT_FILENO);

    // Connect stderr of the child process to the write end of the pipe.
    dup2(pipefd.at(1), STDERR_FILENO);

    // Close both ends of the pipe to avoid leaking them when over-writing
    // the child process.
    close(pipefd.at(0));
    close(pipefd.at(1));

    // Write over this process' memory and execute the command in this
    // process.
    // The reason the cmd is first parsed into string is because the char*
    // need a reference to point to. If the vector of strings is destroyed,
    // the char* will point to junk data and exec() will not work. And of
    // course because it's a piece of shit C API it ONLY takes char* and
    // an array of char*. It took me FOREVER to find this bug since
    // originally I was creating a function local string and creating a char*
    // from that string to place in the array. This results in an extra copy
    // of the strings and an allocation of a new vector of pointers. I can't
    // think of a way around it because several commands are not known until
    // runtime, meaning they have to be allocated in strings. Maybe I can
    // tweak this function to take in a vector of strings and just create
    // a vector of char* to those strings, but for now I just want to be DONE.
    auto args_str { split_args(cmd) };
    const auto args { args_c_str(args_str) };
    execvp(args.at(0), args.data());
    std::perror("execvp");

    // If this code runs, it means execvp failed and this child process
    // should be killed.
    std::exit(EXIT_FAILURE);
  }
  else {
    // Parent process
    // Close write end of the pipe since this process only reads from the
    // child.
    close(pipefd.at(1));

    constexpr int BUFFER_SIZE { 4096 };
    std::array<char, BUFFER_SIZE> buffer {};
    std::string output {};
    ssize_t bytes_read {};

    if (capture_output) {
      while ((bytes_read = read(pipefd.at(0), buffer.data(), BUFFER_SIZE - 1)) > 0) {
        buffer.at(BUFFER_SIZE - 1) = '\0';
        output.append(buffer.data());
      }
    }
    else {
      while ((bytes_read = read(pipefd.at(0), buffer.data(), BUFFER_SIZE - 1)) > 0) {
        buffer.at(BUFFER_SIZE - 1) = '\0';
        std::print("{}", buffer.data());
      }
    }

    // Close read end of the pipe after (possibly) reading from the child process.
    close(pipefd.at(0));

    // Wait for child process to terminate.
    int status {};
    if (waitpid(pid, &status, 0) == -1) {
      return CommandResult { .output=output, .success=false };
    }

    if (WIFEXITED(status)) {
      if (WEXITSTATUS(status) == EXIT_FAILURE) {
        // process exited in failure state
        return CommandResult { .output=output, .success=false };
      }
      if (WEXITSTATUS(status) == EXIT_SUCCESS) {
        return CommandResult { .output=output, .success=true };
      }
    }
    else {
      // Process was killed or stopped
      return CommandResult { .output=output, .success=false };
    }
  }

  std::unreachable();
}


std::string to_upper(std::string_view str) {
  std::string upper {};
  for (const char c : str) {
    upper.push_back(
      // Sometimes C++ is dumb as fuck...why does toupper
      // take in an int?
      static_cast<char>(std::toupper(static_cast<int>(c)))
    );
  }
  return upper;
}


std::string to_lower(std::string_view str) {
  std::string lower {};
  for (const char c : str) {
    lower.push_back(
      static_cast<char>(std::tolower(static_cast<int>(c)))
    );
  }
  return lower;
}


const std::string_view get_home_dir() {
  const std::string_view HOME = std::getenv("HOME");
  return HOME;
}


const std::string get_profiles_dir() {
  const std::string profiles_dir {
    std::format("{}/.gojocli/profiles", get_home_dir())
  };
  return profiles_dir;
}

}  // namespace utils
