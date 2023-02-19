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

