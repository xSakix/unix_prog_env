# Chapter1


## Basic keys combinations

* ctrl+h - backspace
* ctrl+d - no more input
* ctrl+i - tab
* ctrl+m - return
* ctrl+g - ring bell
* ctrl+c - delete = stop the running program!
* ctrl+u - line kill, removes all written chars in line
* ctrl+s - interrupt running prog in terminal
* ctrl+q - continue interrupted
* ctrl+d - logout


## Basic commands

* **login** - log into the system (e.g. ssh)
* **date** - print date
* **who** - print info about who is logged in (on tty?)
* **mail** - read mail (obsolate?)
* **tty** = teletype - archaic name for terminal
* **whoami** - print info about me
* **stty** - print info about your terminal (stty -a)
* **tabs** - set tabs behavior on your terminal
* **man** - man pages
* **man man** - print manual for man pages

* **ed** - editor

Example for ed:
```
a - start adding/appending text
<text text>
. - stop adding text
w <filename> - write to filename
q - quit
```

## Files

* **ls** - list files
* **ls -t** -> list files in time order
* **ls -l** -> long list 

ls will list also a 'total number', where the number is number of blocks the files occupy on disk. Usually a block is 512 or 1024 characters.

<br/>

### Explanation of long format
<br/>

```
-rwxr-xr-x. 1 user group 24984 Feb 11 12:17 tty
```

* first part is: -, d for dir, l for link
* file permission part: rwxr-xr-x
    * user permissions: rwx
    * group permissions: r-x
    * other persmissions: r-x
* last part: . - don't know what it means:)
* number of links: 1
* name of user: user
* name of group: group
* size in bytes: 24984
* date changed/created: Feb 11 12:17
* filename: tty

<br/>

* **ls -lt** -> you can group options together
* **ls -lut** -> long, sorted by date, -u date when files where used
* **ls -r** -> reverse...for example ls -lrt in reverse sorted by date
* print files - **cat** or **pr**

### File manipulation

* move/rename files = **mv**
* copy files = **cp**
* remove files = **rm**

**...experienced users find talkative commands annoying.**

### Filenames

- there is a limit to length
- don't use special at beginning like '-' etc
- '.' used also to divide files into chunks
- file sensitive junk, Junk, JUNK are 3 different files

<br/>
<br/>

* **wc** - word count, prints number of lines, words and characters in one or more files

### grep

* **grep** - search in files for lines that match a pattern
* **grep pattern file** - search for lines which contain given pattern in file
* **grep -v pattern file** - search for lines which do not contain given pattern in file

### sort

* **sort** - sort input into alphanumerical order line by line
* **sort -r** -> reverse
* **sort -n** -> sort in numerical order
* **sort -nr** -> sort in reverse numerical order
* **sort -f** -> fold upper and lower case together
* **sort +n** -> sort starting at n+1-st field

### tail 

* **tail** -> print tail of file, e.g. last 10 lines of file
* **tail -number** -> print *number* of last lines in file
* this doesn't work anymore: **tail +*number*** -> print file starting at line *number* in file

### Compare files

* **cmp** - compare 2 files and find first difference in them
  
***observation**: in 'old' times they would use character as name of 'size' insteadd of bytes. So it made sense when you do cmp file1 file2 and it writes character 10, line 55. Today you get byte 10, line 55 
and have to understand the difference.*

* **diff** - report all lines which are different  (used to find the difference)

## Directories

- files are grouped into directories
- each user has a home dir, sometimes called login dir. After you 'login' you will be in this dir.
- working/current directory can be changed
- files in two dirs are unrelated even when they have the same name

* **pwd** - print working directory

*In old unix the home would be somewhere /usr/*username*. Fedora/linux have /home/*username*s. In new linux 'usr' might mean unix share? A special dir shared with all users? Based on simple google search it contains user space executables/files.*


* **'/'** = root directoryls
* **cd** - change directory
* **mkdir** - make directory (cool use is **mkdir -p path** which create all non existing dirs in path)
* **rmdir** - remove directory

## Shell

- wildcards \*, for example ls chapter*, will print all files which start with chapter, etc.
- {start...end} - for ex. ls chapter{1...3}
- [] - matches anything within brackets, for example ls chapter[123], ls chapter[1-8], ls ch[a-z]*
- ? - match any single char, for ex ls ch?pter
- you cannot create new files from patterns, for ex mv ch.* chapter.* if chapter.* doesn't exists
- patterns match only existing files!
- **echo \***  - prints all filenames in dir
- **'*'** - be carefull when you use it. You might regretting selecting something which you didn't want to. Especially when uninstalling packages, removing files, etc...

### Input-output redirection

- '>' - redirect output of command to a file, for ex ls > file1, cat file1 file2 file3 > file
- '>' = put the output in the following file, rather than on the terminal
- '>>' - adds to the end of file, for ex cat file1 file2 file3 >> file4 (copies file1, file2 and file3 to the end of file4)
- '<' - take the input for a program from the following file, 

**<u>some examples:</u>**

print a list of sorted logged users:
```
who > tmp 
sort < tmp
```

print number of logged users:
```
who > tmp
wc -l < tmp
```

number of files:
```
ls > tmp
wc -l < tmp
```

print list of file into 3 columns:
```
ls > tmp
pr -3 < tmp
```

check if a user is logged in:
```
who > tmp
grep marry <tmp
```

***Essential property of most commands**: if no filenames are specified, the standard input is processed.*

## Pipes

A pipe is a way to connect the output of one program to the input of another program without any temporary file. A pipeline is a connection of two or mor eprograms through pipes.

**<u>Example rewritten:</u>**
```
who | sort
who | wc -l
ls | wc -l
ls | pr -3
who | grep marry 
```

* any program that reads from the terminal can read from a pipe
* any program that writes on the termnial can write to a pipe

```
ls | pr -3 | lpr
who | grep marry | wc -l
```

### How the programs in a pipeline are run

* Programs in a pipeline run at the same time, **not one after another**.
* Programs in a pipeline can be interactive.
* **Kernel** looks after whatever **scheduling** and **synchronization** is needed to make it all work.

### How are commands in shell invoked

* Normal command invocation looks like this: *command optional-arguments optional-filenames*
* If no filename, command **reads from standard input**
* Standard input is by **default the terminal**
* Standard input can be **redirected** to come form a **file** or a **pipe**.
* Most commands write their outputs on **standard output**.
* Standard output is by **default send to the terminal**.
* Standard output can be redirected to a **file** or a **pipe**.
* Each command has a **standard error** output as well.
* **Standard error is normally directed to the terminal**.

## Processes

* You can run two programs by separating them with ';'. Ex.: 
  ```
  $ date;who
  ```
* Commands are run in sequence
* '&' at the end of a command line says to the shell "start this command running, then take further commands from the terminal immediately", e.g. don't wait for it to complete. If we redirect into file, it will not interfere with whatever we do.
  
  ```
  $ c Readme.md > wc.out &
  [1] 6252
  [1]+  Done                    wc Readme.md > wc.out
  ```

* **An instance of a running program is called a <u>process</u>**
* Each process has a **process id**. We can use it refer to a specific running program.
* **wc** is a program. Each time we run **wc** we create a new **process**.
* '&' applies to the <u>whole</u> pipeline. All programs are started at the same time in pipeline. Printed process id will belong to the last program/process in the sequence.

```
$ cat Readme.md | wc &
[1] 7634
    256    1431    7790
[1]+  Done                    cat Readme.md | wc
```

* **wait** - wait's for all processes initiated with '&' to finish. It will block until that happens.

```
$ cat Readme.md | wc ; sleep 10 &
    263    1489    8134
[1] 7764
$ wait
[1]+  Done                    sleep 10
````

* **kill <process id>** - stop process. **kill 0** - kills all processes except for login shell.

```
$ cat Readme.md | wc ; sleep 10 &
    271    1514    8262
[1] 7847
$ kill 7847
[1]+  Terminated              sleep 10
```

* **ps -ag** - print all currently running processes. Output is different on each system.

```
PID TTY      STAT   TIME COMMAND
   1789 tty2     Ssl+   0:00 /usr/libexec/gdm-wayland-session /usr/bin/gnome-session
   1798 tty2     Sl+    0:00 /usr/libexec/gnome-session-binary
   2826 pts/0    Ss     0:00 bash
   8104 pts/0    R+     0:00 ps -ag
```

* **PID** - process id
* **TTY** - terminal asociated with the process
* **TIME** - processor time used in minutes and seconds
* **COMMAND** - command being run
* **STAT** - is not mentioned, but quick man lookup returns - state of the process (D uninterruptible sleep, I idle kernel thread, R running or runnable, S interruptible sleep, T stopped by job control signal, t stopped by debugged, W paging, X dead, Z defunct zombie process). For BSD style < high priority, N low priority, L has pages locked into mem, s is session leader, l is multi-threaded, + is in the foregroung process gr
  
* Processes are ordered into a hierarchy like filesystem. **Each process has a parent**. Each process can have **children**. 
* My shell was created by a process connected to system. Each command I run will be a direct child of my shell.
* If we run a command from within our commands, the command will be a child of that one, and a grandchild of the shell.

* **nohup** - no hang up. The command will continue to run if you log out. Output is saved into a file 'nohup.out'. There is no way to nohup a command retroactively.

```
nohup command &
```

* **nice _expensive command_ &** - run your command with lower priority. Use for commands which run long time and can affect other users on the system. **nohup runs automatically nice also!**
* **at _time_</i>_** - start command at given time. **atq** - print scheduled jobs. **atrm _job num_** - removes scheduled job with given job num. **batch** - run a command when resources permit it (.e.g. the load drops bellow 0.8)

```
$ at 12:57
warning: commands will be executed using /bin/sh
at Sat Apr  1 12:57:00 2023
at> ls -la
at> <EOT>
job 1 at Sat Apr  1 12:57:00 2023
```

## Tailoring the environment

* **.profile** - the shell will execute commands when you log in, before printing the first prompt. It is used to setup your environment.
* **stty erase <backspace>** - one of the first command in _.profile_. For backspace you can enter '^x' for ctrl+x, or '^h' for backspace. **^** - is an obsolate symbol for pipe operator '|' and therefore it must be protected by quotes.
* **stty erase '^h' -tabs** - add sensible tab stops to terminal
* **who | wc -l** - see how busy the system is
* **.bashr** - is the main profile file for bash which runs on each new terminal bash shell

### Some shell variables

* **PS1** - sets the prompt string. For example if it is:

```
PS1='%'
```
Your shell prompt will literally start with '\%'.

* when setting shell variables **spaces are not permitted** around '='

```
#this is ok:
PS1='%'

#this is not:
PS1 = '%'
```

* **HOME** - name of our home directory
* **MAIL** - standard files where our mail is kept
* **PATH** - contains a sequence of directories which represent a _search path_, where the shell looks for commands. We set PATH usually like this:

```
PATH=$PATH:/my/dir/with/commands
```

This will add to existing PATH (defined here as $PATH) a new directory where our commands are.

* you can use **echo** to print shell variables:

```
$ echo $PS1
[\u@\h \W]\$
$ echo $PATH
/home/martin/.local/bin:/home/martin/bin:/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin
$ echo $HOME
/home/martin
```

* **TERM** - defines the kind of terminal we want.This info may make it possible for programs to manage your screen more effectively.

```
$ echo $TERM
xterm-256color
```

* you can use variables for abbreviation. For example define a shorcut for a long directory path

```
d=/horribly/long/directory/name

#and use in shell like this:

$cd $d
```

* personal variables should be spelled **in lower case**
* **export** is used to mark variables to be used in other commands

```
export MAIL PATH TERM
```

