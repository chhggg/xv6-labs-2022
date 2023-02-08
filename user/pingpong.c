#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(){

    char buf[3];
    int p[2];
    pipe(p);

    if(fork()==0){
        close(p[0]);
        strcpy(buf, "hh");
        write(p[1], buf, strlen(buf));
        printf("%d: received ping\n",getpid());
        
    }
    else{
        wait(0);
        close(p[1]);
        read(p[0], buf, 3);
        printf("%d: received pong\n",getpid());
    }
    exit(0);
}