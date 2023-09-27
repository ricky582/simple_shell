# Simple Shell

A simple linux shell, written in C - based on the Linux kernel.

Group university project from 2nd year.

## Installation
First, check you have all the required software:
  - [Git](https://git-scm.com/downloads)
  - A C compiler or Ubuntu shell: For a good Ubuntu shell on Windows I recommend [this](https://ubuntu.com/tutorials/install-ubuntu-on-wsl2-on-windows-10#1-overview) and [Cygwin](https://www.cygwin.com/install.html) if you'd rather use a compiler

Next, do the following (I used Ubuntu Shell linked above):
  - Clone repository - `git clone https://github.com/ricky582/simple_shell`
  - Compile the code - `gcc -o SimpleShell Main.c`
  - Run the shell - `./SimpleShell`

## Useage
Most of the common linux commands are available (`cd`, `ls`, `pwd`, `mkdir` etc.), try them out!

Some limitations for simplicity:
  - To close the shell use the `exit` command (alternatively use Ctrl+D)
  - `history` command is limited to 20 items, same behaviour otherwise
  - similarly, `alias` is limited to 10 items
  - navigating previous commands with up/down arrow keys is not possible
