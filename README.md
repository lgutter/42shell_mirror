# 42shell

42shell is a project in the [Codam](https://www.codam.nl/) curriculum requiring you to build a shell with all basic functionality, plus a choice of six extra features.

The six extra features we are building are:
- Complete management of quoting &#10003;
- Tab completion for built-ins, command, and files in current directory
- Arithmetic expansion using `$(())`
-
-
-


# Compiling
You can download a pre-compiled binary for Arch, Debian or Ubuntu if you trust our CI build jobs: [DIRECT DOWNLOAD LINKS]
- [Arch Linux](https://gitlab.com/Devanando/42shell/-/jobs/artifacts/master/download?job=arch-build)
- [Debian](https://gitlab.com/Devanando/42shell/-/jobs/artifacts/master/download?job=debian-build)
- [Ubuntu](https://gitlab.com/Devanando/42shell/-/jobs/artifacts/master/download?job=ubuntu-build)

### Compilation has been tested on MacOS Mojave, Debian, Ubuntu, and Arch linux, and requires the following dependencies:
- gcc
- libncurses5-dev
- pkg-config
- [meson](https://mesonbuild.com/) (0.52 recommended)
- [ninja](https://ninja-build.org/) (1.10 recommended)

To compile the shell, run the following commands:
```
$> meson build
$> cd build
$> ninja
```
The compiled executable will be called `./cetushell`.

Optionally, you can install [Criterion](https://github.com/Snaipe/Criterion) and run `ninja test` to compile and run a limited set of tests.

# Usage
To start the shell, run `./cetushell`.
42shell will initialize a minimal environment if it receives an empty environment.

This shell currently has the following features:
- Command execution based on PATH
- Internal shell + environment variables, including expansion and support for read-only
- Pipes
- Redirections (>, <, >>, <<, >&, <&)
- Command history using `arrow up` and `arrow down` (using HISTFILE & HISTSIZE, supports newlines)
- Quotes (`"`, `'` & `\`), including in heredocs and the heredoc end word (i.e. `EOF`)
- Heredocs
- Command line control:
	- `arrow keys` to move left and right, `ctrl + arrow keys` to move per word or line
	- shift + arrow keys left and right to select
	- `ctrl+b` to copy, `ctrl+x` to cut, `ctrl+v` to paste.
- The following built-in commands:
	- `cd` (including `cd -` )
	- `echo` (supports `-n` to ommit trailing newline)
	- `env` (without any arguments or options)
	- `setenv` (see `--help` for options and syntax)
	- `unsetenv` (see `--help` for options and syntax)
	- `setshell` (see `--help` for options and syntax)
	- `unsetshell` (see `--help` for options and syntax)
	- `exit`

