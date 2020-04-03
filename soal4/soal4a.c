#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>

const int x=4, y=2, z=5;
const int matrix1[x][y] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
const int matrix2[y][z] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}};
int hasil[x][z];

pthread_t tid[x*z];
pthread_attr_t attr;
int iret[x*z];
key_t key = 1234;
int (*matrix)[x][z];

void *hitung(void *arguments);

struct arg_struct{
    int arg1;
    int arg2;
}

int main(){
    int total=x*z;
    
    int shmid = shmget(key, sizeof(int[x][z]), IPC_CREAT | 0666);
    matrix = shmat(shmid, 0, 0);

    for(int i=1; i<=x; i++){
        for(int j=1; j<=z; j++){
            int cnt= (i*j)-1;
            struct arg_struct args;
            args.arg1 = i-1;
            args.arg2 = j-1;

            pthread_attr_init(&attr);
            iret[cnt] = pthread_create(&tid[cnt], &attr, hitung, (void *)&args);
            if(iret[cnt]){
                fprintf(stderr,"Error - pthread_create() return code: %d\n", iret[cnt]);
                exit(EXIT_FAILURE);
            }
        }
    }

    for(int i=0; i<total; i++){
        pthread_join(tid[i]);
    }

    for(int i=0; i<x; i++){
        for(int j=0; j<z; j++){
            printf("%d\t", hasil[i][j]);
        }
    }

    shmd(matrix);

    return 0;
}

void *hitung(void *arguments){
    int temp = 0;
    int i=args->arg1;
    int j=args->arg2;

    for(int i=0; i<y; i++){
        temp = temp + (matrix1[i][y] * matrix2[y][j])
    }

    hasil[i][j] = temp;
    matrix[i][j] = hasil[i][j];
    pthread_exit(0);
}