# 42shell

42shell is a project in the [Codam](https://www.codam.nl/) curriculum requiring you to build a shell with all basic functionality, plus a choice of six extra features.

The seven extra features we have built are:
- Complete management of quoting ✓
- Tab completion for built-ins, command, and files in current directory ✓
- hash table for executables ✓
- test builtin ✓
- Arithmetic expansion using `$(())` ✓
- command substitution using `$()` ✓
- process substitution using `<()` and `>()` ✓

anything labeled with `(BONUS)` is not required by the project subject.



# Compiling
You can download a pre-compiled binary for Arch, Debian or Ubuntu if you trust our CI build jobs:\
`[DIRECT DOWNLOAD LINKS]`
- [Arch Linux](https://gitlab.com/Devanando/42shell/-/jobs/artifacts/master/download?job=arch-build)
- [Debian](https://gitlab.com/Devanando/42shell/-/jobs/artifacts/master/download?job=debian-build)
- [Ubuntu](https://gitlab.com/Devanando/42shell/-/jobs/artifacts/master/download?job=ubuntu-build)

### Compilation has been tested on MacOS Mojave, Debian, Ubuntu, and Arch linux, and requires the following dependencies:
- gcc or clang
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
- Command execution based on `PATH`
- hashing of executable names in hashtable, with corresponding `hash` builtin
- non-interactive mode through redirection of input OR a file as argument (BONUS)
- support for comments using `#`. Aything after a `#` until the next newline is ignored. (BONUS)
- Internal shell + environment variables, including assignment through assignment words, expansion (using `$KEY` or `${KEY}`) and support for read-only
- Changing the shell prompt by modifying the shell variable `PS1`
- Pipes (including completion of pipes(BONUS))
- Redirections (>, <, >>, <<, >&, <&)
- Command history using `arrow up` and `arrow down` (using `$HISTFILE` & `$HISTSIZE`, supports newlines(BONUS))
- Contextual `tab` completion with support for files, directories, executables, and shell/environment variables.
- Arithmetic expansion using `$((expr))`, with support for variables and nesting with `$((40 + $((2))))` and decimal, hex, and octal numbers.
- Command substitution using `$(command)`, with full support for anything supported in non-interactive mode.
- Process substitution using `>(command)` to redirect to the process or `<(command)` to redirect from the command.
- Quotes (`"`, `'` and `\`), including in heredocs and the heredoc end word (i.e. `EOF`)
- the operators `&&` and `||` to chain multiple complete commands
- job control including the required builtins (see below) and `job_spec` which supports these formats:
	- `%-`: matches previous job
	- `%+`: matches current job
	- `%n` matches job with job id `n`
	- `%string`: matches any job that begins with `string`
	- `%?string`: matchs any job that contains `string`
- Command line control:
	- `arrow keys` to move left and right, `ctrl + arrow keys` to move per word or line
	- shift + arrow keys left and right to select
	- `ctrl+b` to copy, `ctrl+x` to cut, `ctrl+v` to paste.
# Built-in commands:
- `cd [-P|-L|'-'] [PATH]`: change directory to `PATH`, or home if `PATH` is not iven.
	- `-P` will update `$PWD` to absolute path if `PATH` contained symlinks
	- `-L` will update `$PWD` to relative path if `PATH` contained symlinks default)
	- `-` changes to previous directory (stored in `$OLDPWD`)
- `echo`: supports `-n`(BONUS) to ommit trailing newline
- `hash [-r|-i|COMMAND[=PATH]]`: manage the command hash table
- `jobs [-p|-l] [job_spec ...]`: print status of jobs.
	- `-p` only prints the pgid of the job.
	- `-l` always print long output with details per process
- `fg [job_spec]`: but job in foreground. if `job_spec` is ommited, `%+` is assumed.
- `bg [job_spec ...]`: but all given jobs in foreground. if `job_spec` is ommited, %+` is assumed.
- `set`: print all variables (shell and environment)
- `unset [KEY ...]`: unset all instances of every `KEY` in shell and environment ariables
- `export [-p|KEY[=VALUE] ...]`: export every `KEY` from the shell to the nvironment, or add it th the environment with `VALUE` if specified.
	- `-p` will print all environment variables in a valid format to export all of hem.
- `setenv`: see `--help` for options and syntax (BONUS)
- `unsetenv`: see `--help` for options and syntax (BONUS)
- `setshell`: see `--help` for options and syntax (BONUS)
- `unsetshell`: see `--help` for options and syntax (BONUS)
- `exit [exit_code]`: exit the shell. exit code will be `exit_code` if given, or ost recent status code. (`$?`)
- `type [COMMAND ...]`: prints type/location of every `COMMAND`.
- `test` with support for `[ expr ]`(BONUS) and `!`, and the following operators:
	- `-a` : True if file exists. (BONUS)
	- `-b` : True if file exists and is a block special file.
	- `-c` : True if file exists and is a character special file.
	- `-d` : True if file exists and is a directory.
	- `-e` : True if file exists.
	- `-f` : True if file exists and is a regular file.
	- `-g` : True if file exists and its set-group-id bit is set.
	- `-h` : True if file exists and is a symbolic link. (BONUS)
	- `-L` : True if file exists and is a symbolic link.
	- `-p` : True if file exists and is a named pipe (FIFO).
	- `-r` : True if file exists and is readable.
	- `-S` : True if file exists and is a socket.
	- `-s` : True if file exists and has a size greater than zero.
	- `-u` : True if file exists and its set-user-id bit is set.
	- `-w` : True if file exists and is writable.
	- `-x` : True if file exists and is executable.
	- `-z` : True if the length of string is zero.
	- `-n` : True if the length of string is non-zero. (BONUS)
	str1 OP str2: Arg1 and arg2 are strings, where OP can be:
	- `=` : True if the strings are equal.
	- `==` : True if the strings are equal. (BONUS)
	- `!=` : True if the strings are not equal.
	int1 OP int2: Arg1 and arg2 may be positive or negative integers, where OP can e:
	- `-eq` : True if arg1 is equal to arg2.
	- `-ne` : True if arg1 is not equal to arg2.
	- `-gt` : True if arg1 is greater than arg2. (BONUS)
	- `-ge` : True if arg1 is greater than or equal to arg2.
	- `-lt` : True if arg1 is less than arg2.
	- `-le` : True if arg1 is less than or equal to arg2.
