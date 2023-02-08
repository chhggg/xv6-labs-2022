#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int filter(int p, int prime){
    int fd[2];
    int n;
    pipe(fd);

    if(fork()==0){
        close(fd[0]);
        printf("prime %d\n", prime);
        while(read(p,&n,sizeof(int))){
            if(n%prime!=0){
                write(fd[1],&n,sizeof(int));
            }
        }
        exit(0);
    }
    else{
        wait(0);
        close(fd[1]);
        close(p);
        return fd[0];
    }
}

int main(void){

    int p[2];
    pipe(p);

    int prime;

    if(fork() == 0){
        close(p[0]);
        for(int i=2;i<36;i++){
            write(p[1],&i,sizeof(int));
        }
    }
    else{
        wait(0);
        close(p[1]);
        while(read(p[0],&prime, sizeof(int))){
            p[0] = filter(p[0], prime);
        }

    }
    exit(0);
}