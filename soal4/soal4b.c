#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define x 4
#define y 2
#define z 5

pthread_t tid[x*z];
pthread_attr_t attr;
int iret[x*z];
key_t key = 1234;
int *matrix;

void *hitung(void *arguments);

int main(void){
    int total=x*z;
    
    int shmid = shmget(key, sizeof(matrix), IPC_CREAT | 0666);
    matrix = shmat(shmid, 0, 0);

    int cnt=0;
    for(int i=1; i<x+1; i++){
        for(int j=1; j<z+1; j++){
            printf("%d\t", matrix[cnt]);
            cnt++;
        }
        printf("\n");
    }
    printf("\n");

    cnt=0;
    for(int i=1; i<x+1; i++){
        for(int j=1; j<z+1; j++){
            pthread_attr_init(&attr);
            iret[cnt] = pthread_create(&tid[cnt], &attr, hitung, &matrix[cnt]);
            if(iret[cnt]){
                fprintf(stderr,"Error - pthread_create() return code: %d\n", iret[cnt]);
                exit(EXIT_FAILURE);
            }
            pthread_join(tid[cnt], NULL);
            cnt++;
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
    int c = *((int *)arguments);
    for(c; c>0; c--){
        temp=temp+c;
    }
    printf("%d\t", temp);
    pthread_exit(0);
}