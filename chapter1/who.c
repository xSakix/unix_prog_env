/**
sources: 
https://github.com/coreutils/coreutils/blob/master/src/who.c
https://man7.org/linux/man-pages/man5/utmp.5.html
https://stackoverflow.com/questions/26333279/reading-the-linux-utmp-file-without-using-fopen-and-fread

The utmp file allows one to discover information about who is
currently using the system.  There may be more users currently
using the system, because not all programs use utmp logging.

struct utmp {
               short   ut_type;               Type of record 
               pid_t   ut_pid;                PID of login process 
               char    ut_line[UT_LINESIZE];  Device name of tty - "/dev/" 
               char    ut_id[4];              Terminal name suffix,
                                                or inittab(5) ID 
               char    ut_user[UT_NAMESIZE];  Username 
               char    ut_host[UT_HOSTSIZE];  Hostname for remote login, or
                                                kernel version for run-level
                                                messages 
               struct  exit_status ut_exit;   Exit status of a process
                                                marked as DEAD_PROCESS; not
                                                used by Linux init(1) 
                The ut_session and ut_tv fields must be the same size when
                  compiled 32- and 64-bit.  This allows data files and shared
                  memory to be shared between 32- and 64-bit applications. 
           #if __WORDSIZE == 64 && defined __WORDSIZE_COMPAT32
               int32_t ut_session;            Session ID (getsid(2)),
                                                used for windowing 
               struct {
                   int32_t tv_sec;            Seconds 
                   int32_t tv_usec;           Microseconds 
               } ut_tv;                       Time entry was made 
           #else
                long   ut_session;            Session ID 
                struct timeval ut_tv;         Time entry was made 
           #endif

               int32_t ut_addr_v6[4];         Internet address of remote
                                                host; IPv4 address uses
                                                just ut_addr_v6[0] 
               char __unused[20];             Reserved for future use 
           };

ut_type is defined as:

#define EMPTY         0  Record does not contain valid info
                            (formerly known as UT_UNKNOWN on Linux) 
#define RUN_LVL       1  Change in system run-level (see
                            init(1)) 
#define BOOT_TIME     2  Time of system boot (in ut_tv) 
#define NEW_TIME      3  Time after system clock change
                            (in ut_tv) 
#define OLD_TIME      4  Time before system clock change
                            (in ut_tv) 
#define INIT_PROCESS  5  Process spawned by init(1) 
#define LOGIN_PROCESS 6  Session leader process for user login 
#define USER_PROCESS  7  Normal process 
#define DEAD_PROCESS  8  Terminated process 
#define ACCOUNTING    9  Not implemented 

*/

#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]){

    struct utmp *data;
    struct timeval tv;
    char tmbuf[64];
    time_t nowtime;
    char result[255];

    while((data  = getutent()) != NULL){
        
        if(data->ut_type != USER_PROCESS)
            continue;            

        nowtime = data->ut_tv.tv_sec;
        strftime(tmbuf, sizeof(tmbuf), "%Y-%m-%d %H:%M",localtime(&nowtime));
        sprintf(result, "%s\t%s\t%s (%s)\n", data->ut_user, data->ut_host, tmbuf, data->ut_host);
        printf("%s",result);
        
    }

    return EXIT_SUCCESS;
}