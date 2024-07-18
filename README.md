# 🖥️ Custom Shell README 📜

## Table of Contents

- [Introduction](#introduction)
- [Basic System Calls](#basic-system-calls)
  - [Display Requirement](#display-requirement)
  - [Input Requirements](#input-requirements)
  - [warp Command](#warp-command)
  - [peek Command](#peek-command)
  - [pastevents Command](#pastevents-command)
  - [System Commands](#system-commands)
  - [proclore Command](#proclore-command)
  - [seek Command](#seek-command)
- [Processes, Files, and Misc.](#processes-files-and-misc)
  - [I/O Redirection](#io-redirection)
  - [Pipes](#pipes)
  - [Redirection along with Pipes](#redirection-along-with-pipes)
  - [activities Command](#activities-command)
  - [Signals](#signals)
  - [fg and bg Commands](#fg-and-bg-commands)
  - [neonate Command](#neonate-command)
- [Networking](#networking)
  - [iMan Command](#iman-command)

## Introduction

This document describes the implementation and usage of a custom shell with various features such as system calls, file handling, process management, and networking.

## Basic System Calls 📞

### Display Requirement

The shell prompt displays in the form `<Username@SystemName:~>`. The username and system name are dynamically retrieved, and the current directory is shown relative to the shell's home directory (~).

### Input Requirements

- The shell supports a list of commands separated by `;` or `&`.
- Commands can be executed in the background with `&`.
- Multiple commands can be given using `;`.
- Commands with errors will display an error message.

### warp Command 🚀

The warp command changes the current working directory.

- Supports `.`, `..`, `~` (home directory), and `-` (previous directory).
- Executes sequentially if multiple arguments are provided.
- Prints the full path after changing the directory.

### peek Command 👀

The peek command lists files and directories.

- Default behavior excludes hidden files.
- Flags:
  - `-l`: Displays extra information.
  - `-a`: Includes hidden files.
- Supports symbols like `.`, `..`, `~`, and `-`.

### pastevents Command 🕰️

The pastevents command is similar to the history command in Bash.

- Stores the 15 most recent commands.
- Commands identical to the previous one are not stored.
- Persistent over different shell runs.
- Subcommands:
  - `pastevents`: Displays the history.
  - `pastevents purge`: Clears the history.
  - `pastevents execute <index>`: Executes a command from the history.

### System Commands 💻

- Executes other system commands present in Bash (e.g., emacs, gedit).
- Supports both foreground and background processes.
- Prints the time taken for processes running more than 2 seconds.

### proclore Command 📊

The proclore command displays process information.

- Displays:
  - PID
  - Process status (R/R+/S/S+/Z)
  - Process group
  - Virtual memory
  - Executable path

### seek Command 🔍

The seek command searches for files or directories.

- Flags:
  - `-d`: Only look for directories.
  - `-f`: Only look for files.
  - `-e`: Prints content or changes the directory if only one match is found.
- Supports symbols like `.`, `..`, `~`, and `-`.
- Prints "No match found!" if no match is found.
- Prints "Invalid flags!" if both `-d` and `-f` are used simultaneously.

## Processes, Files, and Misc. 📁

### I/O Redirection 🔀

- Supports `>`, `>>`, and `<`.
- Creates or appends to files as necessary.
- Displays "No such input file found!" if the input file does not exist.

### Pipes ⛓️

- Supports piping between commands.
- Executes commands sequentially from left to right.
- Displays "Invalid use of pipe" if improperly used.

### Redirection along with Pipes 🔄

- Supports I/O redirection with pipes.
- Ensures proper functionality when used together.

### activities Command 📋

The activities command lists all running processes spawned by the shell.

- Displays:
  - Command name
  - PID
  - State (Running or Stopped)

### Signals 🚦

- `ping <pid> <signal_number>`: Sends a signal to a process.
- Handles special keyboard inputs:
  - Ctrl-C: Sends SIGINT to foreground process.
  - Ctrl-D: Logs out of the shell.
  - Ctrl-Z: Stops the foreground process.

### fg and bg Commands 🌟

- `fg <pid>`: Brings a background process to the foreground.
- `bg <pid>`: Changes the state of a stopped background process to running.

### neonate Command 👶

- `neonate -n [time_arg]`: Prints the PID of the most recently created process every `[time_arg]` seconds until `x` is pressed.

## Networking 🌐

### iMan Command ℹ️

- `iMan <command_name>`: Fetches and displays the man page for a given command from the internet.
