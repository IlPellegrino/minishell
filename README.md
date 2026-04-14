# minishell

> A UNIX shell implementation from scratch — as beautiful as a shell.

`minishell` is a 42 Common Core team project that involves building a functional command-line interpreter in C, inspired by `bash`. It covers process management, I/O redirection, piping, signal handling, and environment variable management — all from the ground up.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Supported Syntax](#supported-syntax)

---

## Overview

`minishell` reads and parses user input, resolves executables via `$PATH`, manages child processes using `fork` and `execve`, and handles all standard shell constructs: pipes, redirections, environment variables, and signals. It aims for close parity with `bash` behaviour for the mandatory features.

---

## Features

- Interactive prompt with command history (via `readline`)
- Executable resolution through `$PATH`
- Input/output redirections (`<`, `>`, `>>`, `<<`)
- Pipe chaining between commands (`|`)
- Environment variable expansion (`$VAR`, `$?`)
- Signal handling: `Ctrl+C` (new prompt), `Ctrl+D` (exit), `Ctrl+\` (ignored)
- Fully implemented built-in commands
- Proper handling of single and double quotes
- Memory leak free — all allocations are tracked and freed

---

## Project Structure

```
minishell/
├── main.c              # Entry point — REPL loop and signal setup
├── minishell.h         # Main header — structs, enums, prototypes
├── lexer/              # Tokenisation — splits input into tokens
├── parser/             # AST / command list construction
├── expander/           # Variable expansion and quote handling
├── executor/           # Command execution, pipes, redirections
├── builtins/           # Built-in command implementations
├── signals/            # Signal handler setup
├── env/                # Environment variable management
├── utils/              # String utilities and error handling
├── libft/              # Custom C library
└── Makefile
```

---

## Requirements

- GCC or Clang
- GNU Make
- `readline` library

**Install readline on Linux:**

```bash
sudo apt-get install libreadline-dev
```

**Install readline on macOS (via Homebrew):**

```bash
brew install readline
```

---

## Installation

Clone the repository:

```bash
git clone https://github.com/NicoloRomito/minishell.git
cd minishell
make
```

Clean up:

```bash
make clean    # removes object files
make fclean   # removes binary and object files
make re       # full rebuild
```

---

## Usage

Launch the shell:

```bash
./minishell
```

You will be presented with a prompt. Type commands as you would in a standard terminal:

```bash
minishell$ echo "Hello, world!"
Hello, world!

minishell$ ls -la | grep ".c" | wc -l

minishell$ export MY_VAR=42
minishell$ echo $MY_VAR
42

minishell$ cat << EOF
> line one
> line two
> EOF
line one
line two

minishell$ exit
```

---

## Built-in Commands

| Command | Description |
|---|---|
| `echo [-n]` | Print text to stdout; `-n` suppresses trailing newline |
| `cd [path]` | Change current directory |
| `pwd` | Print the current working directory |
| `export [var=value]` | Set or export an environment variable |
| `unset [var]` | Remove an environment variable |
| `env` | Print all environment variables |
| `exit [code]` | Exit the shell with an optional exit code |

---

## Supported Syntax

| Feature | Description |
|---|---|
| `cmd arg1 arg2` | Execute a command with arguments |
| `cmd1 \| cmd2` | Pipe stdout of cmd1 to stdin of cmd2 |
| `cmd < file` | Redirect file to stdin |
| `cmd > file` | Redirect stdout to file (overwrite) |
| `cmd >> file` | Redirect stdout to file (append) |
| `cmd << LIMITER` | Here-document: read until LIMITER |
| `$VAR` | Expand environment variable |
| `$?` | Expand last exit code |
| `'...'` | Single quotes — no expansion |
| `"..."` | Double quotes — variable expansion only |

---

*Project developed at 42 Firenze as part of the Common Core curriculum.*
