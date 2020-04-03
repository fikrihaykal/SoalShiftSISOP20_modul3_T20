#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>

const int x=4, y=2, z=5;

pthread_t tid[x*z];
pthread_attr_t attr;
int iret[x*z];
key_t key = 1234;
int *matrix;

void *hitung(void *arguments);

int main(void){
    int total=x*z;
    
    int shmid = shmget(key, total, IPC_CREAT | 0666);
    matrix = shmat(shmid, 0, 0);

    for(int i=0; i<x; i++){
        for(int j=0; j<z; j++){
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    for(int i=1; i<=x; i++){
        for(int j=1; j<=z; j++){
            int cnt= (i*j)-1;

            pthread_attr_init(&attr);
            iret[cnt] = pthread_create(&tid[cnt], &attr, hitung, matrix[i][j]);
            if(iret[cnt]){
                fprintf(stderr,"Error - pthread_create() return code: %d\n", iret[cnt]);
                exit(EXIT_FAILURE);
            }
        }
        printf("\n");
    }

    for(int i=0; i<total; i++){
        pthread_join(tid[i], NULL);
    }

    shmdt(matrix);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

void *hitung(void *arguments){
    int temp=0;
    for(arguments , arguments>0, arguments--){
        temp=temp+arguments;
    }
    printf("%d\t", temp);
    pthread_exit(0);
}