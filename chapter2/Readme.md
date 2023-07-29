# The file system

* **<u>Everything in the UNIX file system is a file.</u>**
* it's a good example of KISS
  
## The basics of files

* a file is a sequence of bytes
* byte is small chunk of information, typically 8 bit long. Byte is eq to a character.
* no structure is imposed on the file by the system
* no meaning is attached to it's content
* **the meaning of the bytes depends solely on the program that interpret the file**
* this is true for peripheral devices as well
* magnetic tapes, main messages, characters typed on the keyboard, line printer output, data flowing in pipes - each of these **<u>FILES</u>** <u>is just a sequence of bytes as far as the system and programs in it are concerned</u>.

```
$ cat junk
now is the time
for all good people
$ od -c junk
0000000   n   o   w       i   s       t   h   e       t   i   m   e  \n
0000020   f   o   r       a   l   l       g   o   o   d       p   e   o
0000040   p   l   e  \n
0000044

$ od -cb junk
0000000   n   o   w       i   s       t   h   e       t   i   m   e  \n
        156 157 167 040 151 163 040 164 150 145 040 164 151 155 145 012
0000020   f   o   r       a   l   l       g   o   o   d       p   e   o
        146 157 162 040 141 154 154 040 147 157 157 144 040 160 145 157
0000040   p   l   e  \n
        160 154 145 012
0000044
```

* **od** - octal dump of file. '-c' means interpret bytes as characters. '-b' option will show the bytes as octal(base 8) numbers. On most unix-es the base encoding of characters is ASCII.
* the 7-digits on the left side are positions in the file, e.g. the ordinal number of the next character shown in octal.
* emphasis on octal numbers is a holdover from PDP-11
* to print hexadecimal use option '-x'

```
$ od -x junk
0000000 6f6e 2077 7369 7420 6568 7420 6d69 0a65
0000020 6f66 2072 6c61 206c 6f67 646f 7020 6f65
0000040 6c70 0a65
0000044
```

* each line is ended with the ASCII character **newline** with octal value **012** (or **0a65** hex)
* by convention from C, the character for newline is '\n'
* newline is a *special character*
* other well known *special characters* are backspace(010, '\b'), tab(011, '\t'), carriage return(015, '\r')
* it is important to distinguish how the character is **stored** in a file and how it is **interpreted** in various situations.
* for example the KERNEL echoes RETURN as a carriage return and a newline. But it stores it only the newline in the input. On output the newline is expanded into carriage return and newline.
* *linefeed* is a synonym for newline and the sequence is often called **CRLF**
* system signifies the end of file  by simply saying there is no more data in the file. The kernel keeps track of file length, so a program encounters end-of-file when it has processed all the bytes in a file.
* programs retrieve the data in a file by **system call**(a subroutine in the kernel) called **read**. **read** returns the number of bytes read. If zero is returned, the end-of-file is assumed. Returning zero is and interpretation-independent way to represent the end of a file without introducing a new special char.
* when you type in terminal, input line is given to the program by the **kernel** only when you type its newline.
* **cat** usually buffers its output to write in large chunks. With param '-u' we can unbuffer the output and print immediately as it reads. **comment**: this no longer is true. '-u' was deprecated, and **cat** default behavior is as if you would use '-u' by default.
* **ctrl-d** - stops the program not because it's a signal for exit. It is because it signals the program that there is 0 more bytes available and it reached the 'end of file'. Thus the programs does what it is supposed to do and exits (in most cases). 


## What's in a file

The format of a file is determined by the programs that use it. Kernel doesn't know the file type.

```
$ file test notes.txt
test:      empty
notes.txt: ASCII text
```

**file** reads the first dew hundred bytes of a file and looks for clues to the file type.

Instead of creating distinctions, the UNIX system tries to efface them. All text consists of lines terminated by newline characters, and most programs understand this simple format. This uniformity is unusual, as most systems have several file formats, even for text, and require negotiation by the program or a user to create a file of particular type. In UNIX systems there is just one kind of file, and all that is required to access a file is its name.

Every file format that is not text must have its own family of support programs to do things that the standard tools could perform if the format were text. 

Text files may be a little lest efficient in machine cycles, but this must be balanced against the cost of extra software to maintain more specific formats.

(Also make your programs more robust)

## Directories and filenames

Each running programm, that is each process, has a **current directory**, and all filenames are implicitly assumed to start with the name of that directory, and all filenames are implicitly assumed to start with the name of that directory, unless they begin directly with a slash.

* **pwd** - identifies current working directory

The current directory is an attribute of a process, not a person or a program - people have login directories, processes have current directories.

If a process creates a child process, the child inherits the current directory of its parent. If the child changes to a new directory, the parent is unaffected...it's current directory remains the same no matter for the child process does.


Related files belong together to the same directory.

* **/usr** - directory of the user file system (user is abbreviated in the sense of cmp, ls, etc...)
* **/usr/you** - is your login directory
* **/usr/src** - contains src for system programs 
* **/usr/src/cmd** - contains src for UNIX commands
* **/usr/src/cmd/sh** - contains src for the shelll

Put your files together into hierarchies. The filesystem is a powerfull organisational tool. 

* **du**  - disk usage,e.g. how much disc space is consumed by the files in a dir, including all subdirs

```$ du Projects/AI/models/
113692992	Projects/AI/models/

$ du Projects/AI/models/*
13281544	Projects/AI/models/30b-Lazarus.ggmlv3.q2_K.bin
17563880	Projects/AI/models/falcon-40b-instruct.ggccv1.q3_k.bin
13506868	Projects/AI/models/llama-2-13b-chat.ggmlv3.q8_0.bin
13506868	Projects/AI/models/llama-2-13b-guanaco-qlora.ggmlv3.q8_0.bin
27916900	Projects/AI/models/llama-2-70b-chat.ggmlv3.q2_K.bin
27916900	Projects/AI/models/stablebeluga2-70b.ggmlv3.q2_K.bin
```
The numbers are the numbers of disc blocks - typically 512-1024 bytes each. The value for a directory indicates how many blocks are consumed by all the files in that directory and its subdirectories, including the directory itself.

To print the usage in human friendly way:

```
$ du -h Projects/AI/models/*
13G	Projects/AI/models/30b-Lazarus.ggmlv3.q2_K.bin
17G	Projects/AI/models/falcon-40b-instruct.ggccv1.q3_k.bin
13G	Projects/AI/models/llama-2-13b-chat.ggmlv3.q8_0.bin
13G	Projects/AI/models/llama-2-13b-guanaco-qlora.ggmlv3.q8_0.bin
27G	Projects/AI/models/llama-2-70b-chat.ggmlv3.q2_K.bin
27G	Projects/AI/models/stablebeluga2-70b.ggmlv3.q2_K.bin
32K	Projects/AI/models/wget-log
```


**du** looks in a directory for files. If you don't tell it which directory, it assumess '.', the directory you are in now. 

```
$ du -ah
13G	./30b-Lazarus.ggmlv3.q2_K.bin
17G	./falcon-40b-instruct.ggccv1.q3_k.bin
13G	./llama-2-13b-chat.ggmlv3.q8_0.bin
27G	./llama-2-70b-chat.ggmlv3.q2_K.bin
32K	./wget-log
13G	./llama-2-13b-guanaco-qlora.ggmlv3.q8_0.bin
27G	./stablebeluga2-70b.ggmlv3.q2_K.bin
109G	.
```

That means 'Projects/AI/models/30b-Lazarus.ggmlv3.q2_K.bin' and './30b-Lazarus.ggmlv3.q2_K.bin' are the same files.

Despite their fundamental properties inside the kernel, directories sit in the file system as ordinary files. They can be read as ordinary files -- to preserve it's sanity and the user's files, kernel reserves to itself all control over the contents of directories.

The directory format is a combination of binary and textual data. A directory consits of 16-byte chunks, the last 14 bytes of which hold the filename, padded with ASCII NUL's (which have value 0) and the first two of which tell the system where the administrative information for the file resides. 

Every directory begins with two entries '.' and '..'.

```
$ cd 
$ mkdir recipes
$ cd recipes/
$ pwd
/home/martin/recipes
$ cd ..
$ pwd
/home/martin
$ cd ..
$ pwd
/home
$ cd ..
$ pwd
/
```
Directory '/' is called the **root** of the file system. Every file in the system is in the root directory or one of it's subdirectories, and the root is its own parent directory.

## Permissions

Every file has a set of permissions associated with it, which determine who can do what with the file.

There is a special user on **every** UNIX system, called the **super-user**, who can modify any file on the system. The special login name **root** carries super-user privileges, it is used by system administrators when they do system maintenance. There is also a command called **su** that grants super-user status if you know the root password. 

If you need more privacy you can change the data in the file so that even the super-user cannot read(or rather understand it's contents) it, by using the **crypt** command. (Even the crypt command isn't perfectly secure. A super-user can change the crypt command itself, and there are cryptographic attacks on the crypt algo itself...however the crypt command is fairly secure)

When yoy login, you enter a name and password. The name is called **login-id**. But the system recognizes you by a <u>number</u>, called your user-id, or **uid**. (multiple login-id can have the same uid, but it's not practical)
Beside uid you are assigned a **group identification**, or **group id**, which places you into a class of users. On many systems, all ordinary users are placed in a single group called *other*. 

**The UNIX system in general determines what you can do by the persmissions granted to your uid and group-id.**

**etc/passwd** is the password file. It contains all the login information about each user. It contains uid and group-id. (password was moved to a different file for security reasons in modern systems)

```
$ grep you /etc/passwd
you:x:1003:1004::/home/you:/bin/bash
```

File format:
```
login-id:encrypted-password:uid:group-id:miscellany:login-directory:shell
```

If the shell field is empty, you will use the default shell.
The miscellany field can contain anything and often it has your name.

When you give your password to *login*, it encrypts it and compares the result against the encrypted password in /etc/passwd. 

There are three kinds of permissions for each file:
* read
* write
* execute

Different permissions can apply to different people. As a file owner, you have one set of read, write and execute permissions. 
Your group has a separate set. 
Everyone else has a third set.

To print permission info you can use *ls*:
```
$ ls -l /etc/passwd
-rw-r--r--. 1 root root 3144 Jul 29 14:09 /etc/passwd

$ ls -lg /etc/passwd
-rw-r--r--. 1 root 3144 Jul 29 14:09 /etc/passwd

```

So the permissions on /etc/passwd can be interpreted as:

* it is owned by login-id root
* group is root
* it is 3144 bytes long
* it has one link
* it was last modified Jul 29 14:09
  
The string '-rw-r--r--' represents the persmissions of the file (as *ls* is representing them):
* the first '-' indicates that it is an ordinary file (directory would have a 'd' there)
* next three characters 'rw-' represent file owner's permissions for read, write and execute. So root has the permission to read and write.
* the next three characters 'r--' represent the group's permissions. So the group root can ony read the file.
* the last three characters 'r--' define the permissions for everyone else - the rest of the users on the system (e.g. which are not root or are not in group root).

So only user 'root' can change the info in /etc/passwd, but everybody else can read it.

The file **/etc/group** encodes group names and group-id's, and defines which users are in which groups. 

To change your password you need to user **passwd** command, as only root has the rights to change the /etc/passwd file. 

```
$ ls -l /bin/passwd
-rwsr-xr-x. 1 root root 32760 Jan 19  2023 /bin/passwd
```
So anyone can execute passwd. The **s** in the execute field(instead of 'x') for owner permissions states that, when the command is run, it is to be given the permissions corresponding to the file owner, in this case *root*. Because /bin/passwd is **set-uid** to *root*, any user can run the passwd command to edit the password file. 

The *set-uid* bit is a simple but elegant idea that solves a number of security problems. It is potentially dangerous, as the /bin/passwd has to be correct. If it weren't, it could destroy system information under root's auspices. 

If it had permissions '-rwsrwxrwx', it could be overwritten by **any** user, who could therefore replace the file with a program that does anything. This is particulary serious for a *set-uid* program, because *root* has access permissions to every file on the system. (Some UNIX systems turn the *set-uid* bit off whenever a file is modified, to reduce the danger of a security hole)

```
$ ls -l /bin/who
-rwxr-xr-x. 1 root root 49752 May  4 02:00 /bin/who
```
**who** is executable by everybody, and writable by *root* and the owner's group. Executable means that the shell will look into a set of directories, one of which is */bin*, for a file named who. If it finds such a file and if the file has execute permissions, the shell calls the kernel to run it. The kernel checks the permissions and if they are valid, runs the program. A program is *just a file* with executive permisions.

Directories permissions operate differently, but the basic idea is the same. An **r** field means that you can read the directory, so you can find out what files are in it with *ls*. A **w** means that you can create and delete files in this directory, because that requires modifying and therefore writing the directory file. 

You cannot **simply** write in a directory, even root is forbidden to do so. There are system calls that create and remove files, and through them it is possible to change the contents of a directory.The 'w' permissions tells who can call these kernel routines to modify the directory. 

**Permission to remove a file is independent of the file itself.** If you have write permission on a directory, you can remove a file even when you don't have write permissions on given file. The **rm** double-checks if you want to remove a protected file (with -f flag it will remove without asking).

The **x** flag on directory doesn't mean execution, but **search**. It determines whether the directory might be searched for a file. It is possible to create a directory with '--x' which implies the users may access any file that they know about in that directory, but may not run *ls* on it or read it's contents.
With permission 'r--' users can see (use *ls*) but not use the contents of the directory. 

**chmod** command is used to change permissions on files:

```
chmod permissions file
```

You can use octal numbers to define permissions:

 * 4 for read
 * 2 for write
 * 1 for execution

You specify them by adding am together. For example:

```
chmod 666 junk
```

means 'rw-rw-rw' permissions. 'rw--' equals 4+2 = 6...the octal numbers are for owner, group and others. So  6 for owner, 6 for group, 6 for other.

You can also use symbolic additions or removal of permissions:

```
chmod +x junk
chmod +r junk
chmod +w junk

chmod -x junk
chmod -r junk
chmod -w junk
```

This way it will be applicable for everyone (owner, group, other).

Only the owner and super-user can change permissions on a file/directory.

Even when someone allows you to write a file, the system will not allow you to change permissions.

If you want to protect your files in your directory, remove 'w' permission for groups and others.

Changing the permissions on a directory/file will not change its modification date. **The modification date reflects changes to the file's contents and not it's modes.**

The permissions and dates are not stored in the file itself, but in a system structure called **i-node (index node)**.


## Inodes

