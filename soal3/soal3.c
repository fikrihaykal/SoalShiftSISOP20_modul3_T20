#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <ctype.h>

pthread_t tid[100];

void *moveFile(void *args);
char *namaFile(char str[]);
char rootDir[100] = "/home/fikri/Modul3/soal3";
int temp=0;
char **argtemp;

int main(int argc, char **argv){
    argtemp = argv;
    char workFolder[200] = "./soal3";
    if(!strcmp(argv[1], "-f") && argc>2){
        for(int i=2; argv[i]!=NULL; i++){
            pthread_create(&tid[++temp], NULL, &moveFile, argv[i]);
            // printf("%s\n", argv[i]);
        }
    } else{
        if((!strcmp(argv[1], "*") && argc==2) || (!strcmp(argv[1], "-d") && argc==3)){
            if(!strcmp(argv[1], "-d")){
                // chdir(argv[2]);
                strcat(workFolder, argv[2]);
            }
            DIR *folder;
            struct dirent *directory;
            folder = opendir(workFolder);
            if(folder){
                while((directory = readdir(folder)) != NULL){
                    char finalDir[1000] = "/soal3";
                    if(!strcmp(argv[1], "-d")){
                        strcat(finalDir, argv[2]);
                    } else{
                        strcat(finalDir, "/");
                    }
                    strcat(finalDir, directory->d_name);
                    struct stat buffer;
                    stat(finalDir, &buffer);
                    if(!S_ISDIR(buffer.st_mode)){
                        // printf("%s\n", directory->d_name);
                        pthread_create(&tid[++temp], NULL, &moveFile, directory->d_name);

                        pthread_join(tid[temp], NULL);
                    }
                }
            }

            closedir(folder);
        }
    }
        
    for(int i=0; i<temp+1; i++){
        // pthread_join(tid[i], NULL);
    }

    return 0;
}

void *moveFile(void *args){
    pthread_t pid=pthread_self();
    char *fileEks;
    char target[1000];
    char srcDir[1000], targetDir[1000];
    fileEks = strrchr(namaFile((char *)args), '.');
    if(fileEks== NULL){
        strcpy(target, "Unknown");
    } else{
        strcpy(target, fileEks);
        for(int i=0; i<strlen(target); i++){
            if(target[i]>64 && target[i]<91){
                target[i] += 32;
            }
        }
    }

    if(mkdir(target, 0777) == -1);
    if(argtemp[1] != "-f" && argtemp[1] != "*"){
        snprintf(srcDir, 1000, "%s/soal3%s/%s", rootDir, argtemp[2], (char *)args);
    } else if(argtemp[1] != "-f"){
        snprintf(srcDir, 1000, "%s/soal3/%s", rootDir, (char *)args);
    }
    snprintf(targetDir, 1000, "%s/%s/%s", rootDir, target, namaFile((char *) args));

    if(argtemp[1] == "-f"){
        rename((char *)args, targetDir);
        printf("%s to %s\n", (char*)args, targetDir);
    } else{
        rename(srcDir, targetDir);
        printf("%s to %s\n", srcDir, targetDir);
    }

    // remove(srcDir);
}

char* namaFile(char str[]){
    char* pch;
    char* result;
    pch = strchr(str,'/');
    if(pch == NULL)
        return str;
    while (pch != NULL) {
        result = pch+1;
        pch = strchr(pch+1,'/');
    }
    return result;
}