# Minishell
 Create a simple shell. Yes, a little bash or zsh.
## Features
- Show a prompt when waiting for a new command
- Search and launch the right executable (based on the PATH variable or by using relative or absolute path) like in bash
- It must implement the builtins like in bash:
  - ```echo``` with option ’-n’
  - ```cd``` with only a relative or absolute path
  - ```pwd``` without any options
  - ```export``` without any options
  - ```unset``` without any options
  - ```env``` without any options and any arguments
  - ```exit``` without any options
- Semicolons ```;``` in the command to separate commands
- ```’``` and ```"``` work like in bash except for multiline commands
- Redirections ```< > “>>”```
- Pipes ```|```
- Environment variables (```$``` followed by characters)
- Return value of a process ```$?```
- signals ```ctrl-C```, ```ctrl-D``` and ```ctrl-\```
## Usage
```c
/* Compile */
 make
 
/* Launch the shell */
./minishell
```
## Sources
* https://www.geeksforgeeks.org/doubly-linked-list/
* https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
* http://web.eecs.utk.edu/~huangj/cs360/360/notes/Exec/lecture.html
* https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/
* https://pubs.opengroup.org/onlinepubs/009695399/functions/getcwd.html
* https://sites.cs.ucsb.edu/~manish/discussion/week2.pdf
* https://www-users.cs.umn.edu/~kauffman/4061/05-io-files-pipes.pdf
* https://stackoverflow.com/questions/11515399/implementing-shell-in-c-and-need-help-handling-input-output-redirection
* https://linux.die.net/man/2/waitpid
* https://www.geeksforgeeks.org/fork-execute-processes-bottom-using-wait/?ref=rp
* https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/?ref=rp
* https://linuxhint.com/c_fork_system_call/
* https://www.php.net/manual/en/function.chdir.php
* https://stackoverflow.com/questions/56031104/the-cd-command-in-c-and-use-of-chdir
* https://www.geeksforgeeks.org/error-handling-c-programs/
* https://stackoverflow.com/questions/50610781/implementing-pipe-and-redirection-together-in-c
* https://www.howtogeek.com/439199/15-special-characters-you-need-to-know-for-bash/
* https://www.guru99.com/linux-redirection.html
* https://unix.stackexchange.com/questions/159513/what-are-the-shells-control-and-redirection-operators
* https://pubs.opengroup.org/onlinepubs/9699919799.2016edition/basedefs/V1_chap03.html#tag_03_318
* https://unix.stackexchange.com/questions/362559/list-of-terminal-generated-signals-eg-ctrl-c-sigint
* https://stackoverflow.com/questions/46746333/stat-st-mode-is-always-equal-to-16877
* https://www.geeksforgeeks.org/wait-system-call-c/
* https://man7.org/linux/man-pages/man2/fork.2.html
## Authors
- ***[elahyani](https://github.com/L-ELHASSANE)***
- ***[ichejra](https://github.com/iTree-m)***
