#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[]){

    char *para[MAXARG];
    char buf[1024];

    int para_idx=0;
    int buf_idx=0;

    char ch;
    char* p = buf;

    for(int i=1;i<argc;i++){
        para[para_idx++]=argv[i];
    }

    while(read(0,&ch,1)){
        if(ch==' '){
            buf[buf_idx++]=0;
            para[para_idx++]=p;
            p=buf+buf_idx;
        }
        else if(ch=='\n'){
            para[para_idx++] = p;
            p = buf+buf_idx;

            if(fork()==0){
                exec(argv[1], para);
                exit(0);
            }
            else{
                wait(0);
                para_idx = argc-1;
            }
        }
        else{
            buf[buf_idx++]=ch;
        }
    }
    exit(0);
}