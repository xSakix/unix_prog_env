/**
the original can be found here: 
https://github.com/coreutils/coreutils/blob/master/src/whoami.c
https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-getuid-get-real-user-id

getuid - get user identity
https://man7.org/linux/man-pages/man2/getuid.2.html

getpwuid- The getpwuid() function returns a pointer to a structure containing the broken-out fields of the record in the password database that matches the user ID uid.
https://linux.die.net/man/3/getpwuid


The passwd structure is defined in <pwd.h> as follows:

struct passwd {
    char   *pw_name;       username 
    char   *pw_passwd;     user password 
    uid_t   pw_uid;        user ID 
    gid_t   pw_gid;        group ID
    char   *pw_gecos;      user information[GECOS stands for "General Electric Comprehensive Operating System"]
    char   *pw_dir;        home directory
    char   *pw_shell;      hell program
};

The /etc/passwd file is a text file that describes user login accounts for the system. It should have read permission allowed for all users (many utilities, like ls(1) use it to map user IDs to usernames), but write access only for the superuser.
In the good old days there was no great problem with this general read permission. Everybody could read the encrypted passwords, but the hardware was too slow to crack a well-chosen password, and moreover the basic assumption used to be that of a friendly user-community. These days many people run some version of the shadow password suite, where /etc/passwd has an aqxaq character in the password field, and the encrypted passwords are in /etc/shadow, which is readable by the superuser only.

*/

#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){

    struct passwd *pw;
    uid_t uid;
    const uid_t NO_UID = -1;

    errno = 0;

    if((pw = getpwuid(uid = getuid())) == NULL){
        char errmsg[255];
        sprintf(errmsg, "%s: cannot find name for user ID %lu", argv[0], (unsigned long int)uid);
        perror(errmsg);
    }
    printf("name:\t\t%s\n",pw->pw_name);
    printf("uid:\t\t%d\n",pw->pw_uid);
    printf("gid:\t\t%d\n",pw->pw_gid);
    printf("user info:\t%s\n", pw->pw_gecos);
    printf("dir:\t\t%s\n",pw->pw_dir);
    printf("shell:\t\t%s\n",pw->pw_shell);

    return EXIT_SUCCESS;
}