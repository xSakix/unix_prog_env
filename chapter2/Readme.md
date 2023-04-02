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
[martin@fedora chapter2]$ cat junk
now is the time
for all good people
[martin@fedora chapter2]$ od -c junk
0000000   n   o   w       i   s       t   h   e       t   i   m   e  \n
0000020   f   o   r       a   l   l       g   o   o   d       p   e   o
0000040   p   l   e  \n
0000044
[martin@fedora chapter2]$ oc -cb junk
bash: oc: command not found...
Install package 'origin-clients' to provide command 'oc'? [N/y] n


[martin@fedora chapter2]$ od -cb junk
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
[martin@fedora chapter2]$ od -x junk
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
* 


