#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <wait.h>

int main(void){
    int fd[2];
    
    pid_t pid1;
    int status;

    pipe(fd);

    pid1 = fork();

    if(pid1 < 0){
        exit(EXIT_FAILURE);
    }

    if(pid1 == 0){
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        char *argv[] = {"ls", NULL};
        execv("/bin/ls", argv);
    } else{
        while(wait(&status) > 0);
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        char *argv[] = {"wc", "-l", NULL};
        execv("/usr/bin/wc", argv);
    }

    return 0;
}