#include <stdio.h>
#include <unistd.h>

int main(){

    char *tty=ttyname(STDIN_FILENO);
    if(!*tty){
        tty="Not found...\n";
    }
    puts(tty);

    return 1;
}