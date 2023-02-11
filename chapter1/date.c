#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    
    const char *format = "%a %b %e %H:%M:%S %Z %Y";
    time_t _time = time(NULL);
    struct tm _tm = *localtime(&_time);
    char tmp[64];

    strftime(tmp, 64, format, &_tm);
    printf("%s\n",tmp);

    return 1;
}