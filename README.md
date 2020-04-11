# SoalShiftSISOP20_modul3_T20
Repository untuk praktikum Sistem Operasi 2020 Modul 3 <br />
Departemen Teknologi Informasi

Kelompok T20

Anggota :
- Fikri Haykal
- Hana Ghaliyah Azhar

# SOAL
## Soal 3
Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.<br />
- Semisal program dijalankan:<br />
```
# File kategori terletak di /home/izone/kategori
$ ./kategori -f path/to/file1.jpg path/to/file2.c path/to/file3.zip
#Hasilnya adalah sebagai berikut
/home/izone
|-jpg
|--file1.jpg
|-c
|--file2.c
|-zip
|--file3.zi
```
- Pada opsi -f tersebut, user bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang user inginkan seperti contoh di atas.<br />
- Pada program kategori tersebut, folder jpg,c,zip tidak dibuat secara manual, melainkan melalui program c. Semisal ada file yang tidak memiliki ekstensi, maka dia akan disimpan dalam folder “Unknown”.<br />
- Program kategori ini juga menerima perintah (*) seperti di bawah;<br />
```
$ ./kategori \*
```
- Artinya mengkategori seluruh file yang ada di working directory ketika menjalankan program C tersebut.<br />
- Selain hal itu program C ini juga menerima opsi -d untuk melakukan kategori pada suatu directory. Untuk opsi -d ini, user hanya bisa menginput 1 directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin.<br />
```
$ ./kategori -d /path/to/directory/
```
- Hasilnya perintah di atas adalah mengkategorikan file di /path/to/directory dan hasilnya akan disimpan di working directory di mana program C tersebut berjalan (hasil kategori filenya bukan di /path/to/directory).<br />
- Program ini tidak rekursif. Semisal di directory yang mau dikategorikan, atau menggunakan (*) terdapat folder yang berisi file, maka file dalam folder tersebut tidak dihiraukan, cukup file pada 1 level saja.<br />
- Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat. Dilarang juga menggunakan fork-exec dan system.<br />
- Silahkan download soal3.zip sebagai percobaan. Namun silahkan dicoba-coba sendiri untuk kemungkinan test case lainnya yang mungkin belum ada di soal3.zip.<br />

### Penyelesaian Soal 3
- Masuk ke directory soal 3 <br />
Syntax : `cd Modul3/soal3/`<br />
- Membuat file <b>soal3.c</b> yang berisi program C<br />
Syntax : `touch soal3.c`<br />
___source code : [soal3.c](https://github.com/fikrihaykal/SoalShiftSISOP20_modul3_T20/blob/master/soal3/soal3.c)___ <br />
- Mengompile program<br />
Syntax : `gcc -pthread soal3.c -o soal`<br />
- Menjalankan program<br />
Perintah 1 : `./soal -d /path/to/directory`<br />
Digunakan untuk memindah file dari `directory` yang spesifik<br />
Perintah 2 : `./soal -f /path/to/file.ext`<br />
Digunakan untuk memindah file yang dipilih secara spesifik<br />
Perintah 3 : `./soal \*`<br />
Digunakan untuk memindah seluruh file dari folder yang baru diunzip dari file `soal3.zip`<br />

### Penjelasan Script yang ada di dalam file _soal3.c_<br />
- Input library
```
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
```

- Deklarasi variabel
```
pthread_t tid[100];

void *moveFile(void *args);
char *namaFile(char str[]);
char rootDir[100] = "/home/fikri/Modul3/revisi/soal3";
int temp=0;
char **argtemp;
```

- Jika argument bertipe `-f`<br />
```
    argtemp = argv;
    char workFolder[200] = "./soal3";
    if(!strcmp(argv[1], "-f") && argc>2){
        for(int i=2; argv[i]!=NULL; i++){
            pthread_create(&tid[++temp], NULL, &moveFile, argv[i]);
        }
```

- Membuka direktori, dan jika bertipe `-d` maka mengubah string untuk direktori<br />
```
        if((!strcmp(argv[1], "*") && argc==2) || (!strcmp(argv[1], "-d") && argc==3)){
            if(!strcmp(argv[1], "-d")){
                strcat(workFolder, argv[2]);
            }
            DIR *folder;
            struct dirent *directory;
            folder = opendir(workFolder);
```

- Memanggil fungsi `moveFile()` dengan menggunakan `pthread`<br />
```
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
                    if(directory->d_type == 8){
                        pthread_create(&tid[++temp], NULL, &moveFile, directory->d_name);
                    }
                }
```

- Memanggil fungsi `pthread_join()`<br />
```
    for(int i=0; i<temp+1; i++){
        pthread_join(tid[i], NULL);
    }

    return 0;
```

- Mengambil ekstensi sebuah file, dan mengubah menjadi lowercase<br />
```
if(fileEks == NULL){
        strcpy(target, "Unknown");
    } else{
        strcpy(target, fileEks);
        for(int i=0; i<strlen(target); i++){
            if(target[i]>64 && target[i]<91){
                target[i] += 32;
            }
        }
    }
```

- Menghilangkan titik `.` pada string ekstensi file<br />
```
    int i=0;
    while(target[i] != 0){
        if(target[i] != '.'){
            strncat(dumpFolder, &target[i], 1);
        }
        i++;
    }
```

- Mendefinisikan lokasi awal dan target file yang akan dipindah <br />
```
    if(mkdir(dumpFolder, 0777) == -1);

    if(!strcmp(argtemp[1], "*")){
        snprintf(srcDir, 1000, "%s/soal3/%s", rootDir, namaFile((char *) args));
    } else if(!strcmp(argtemp[1], "-d")){
        snprintf(srcDir, 1000, "%s/soal3%s%s", rootDir, argtemp[2], namaFile((char *) args));
    } else if(!strcmp(argtemp[1], "-f")){
        snprintf(srcDir, 1000, "%s/soal3%s", rootDir, argtemp[2]);
    }
    snprintf(targetDir, 1000, "%s/%s/%s", rootDir, dumpFolder, namaFile((char *) args));

    rename(srcDir, targetDir);
```

- Fungsi untuk mengambil nama file<br />
```
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
```

### Hasil Run program _soal3_ saat dijalankan pada Linux
- Perintah 1 : `./soal -d /adjaisd/`<br />
Memindah file didalam folder `/soal3/adjaisd/`<br />

- Perintah 2 : `./soal -f /folderku/namafile.png`<br />
Memindah file `/soal3/folderku/namafile.png`<br />

- Perintah 3 : `./soal \*`<br />
Memindah semua file dalam folder `/soal3/`<br />



## Nomor 4
Norland adalah seorang penjelajah terkenal. Pada suatu malam Norland menyusuri jalan setapak menuju ke sebuah gua dan mendapati tiga pilar yang pada setiap pilarnya ada sebuah batu berkilau yang tertancap. Batu itu berkilau di kegelapan dan
setiap batunya memiliki warna yang berbeda. Norland mendapati ada sebuah teka-teki yang tertulis di setiap pilar. Untuk dapat mengambil batu mulia di suatu pilar, Ia harus memecahkan teka-teki yang ada di pilar tersebut. Norland menghampiri setiap pilar secara bergantian.<br />

## Soal 4A
<b>Batu mulia pertama.</b> Emerald. Batu mulia yang berwarna hijau mengkilat. Pada batu itu Ia menemukan sebuah kalimat petunjuk. Ada sebuah teka-teki yang berisi:
- Buatlah program C dengan nama "4a.c", yang berisi program untuk melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).
- Tampilkan matriks hasil perkalian tadi ke layar.

### Penyelesaian Soal 4A
- Masuk ke directory soal 4<br />
Syntax : `cd Modul3/soal4/`<br />
- Membuat file <b>soal4a.c</b> yang berisi program C<br />
Syntax : `touch soal4a.c`<br />
___source code : [soal4a.c](https://github.com/fikrihaykal/SoalShiftSISOP20_modul3_T20/blob/master/soal4/soal4a.c)___ <br />
- Mengompile program<br />
Syntax : `gcc -pthread soal4a.c -o soal4a`<br />
- Menjalankan program<br />
Syntax : `./soal4a`<br />

### Penjelasan Script yang ada di dalam file _soal4a.c_<br />
- Input library<br />
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
```

- Deklarasi variabel dan fungsi<br />
```
#define x 4
#define y 2
#define z 5

const int matrix1[x][y] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
const int matrix2[y][z] = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}};
int hasil[x][z];

pthread_t tid[x*z];
pthread_attr_t attr;
int iret[x*z];
key_t key = 1234;
int *matrix;
int cnt=0;

void *hitung(void *arguments);

struct arg_struct{
    int arg1;
    int arg2;
};
```

- Mengalokasikan _shared memory_<br />
```
    int shmid = shmget(key, sizeof(matrix), IPC_CREAT | 0666);
    matrix = shmat(shmid, 0, 0);
```

- Memanggil fungsi hitung sesuai `x dan y` matriks hasil dengan `pthread`<br />
```
    for(int i=1; i<x+1; i++){
        for(int j=1; j<z+1; j++){
            struct arg_struct *args = (struct arg_struct *) malloc(sizeof(struct arg_struct));
            args->arg1 = i-1;
            args->arg2 = j-1;
            pthread_attr_init(&attr);
            iret[cnt] = pthread_create(&tid[cnt], &attr, hitung, args);
            if(iret[cnt]){
                fprintf(stderr,"Error - pthread_create() return code: %d\n", iret[cnt]);
                exit(EXIT_FAILURE);
            }
            cnt++;
        }
    }
```

- Memanggil fungsi `pthread_join()` serta memasukkan hasil matriks ke _shared memory_<br />
```
cnt=0;
    for(int i=0; i<x; i++){
        for(int j=0; j<z; j++){
            pthread_join(tid[cnt], NULL);
            printf("%d\t", hasil[i][j]);
            matrix[cnt] = hasil[i][j];
            cnt++;
        }
        printf("\n");
    }

    shmdt(matrix);

    return 0;
```

- Fungsi untuk menghitung hasil perkalian matriks<br />
```
void *hitung(void *arguments){
    struct arg_struct *args = arguments;

    int temp = 0;
    int d1=args->arg1;
    int d2=args->arg2;

    for(int i=0; i<y; i++){
        temp = temp + (matrix1[d1][i] * matrix2[i][d2]);
    }

    hasil[d1][d2] = temp;
    pthread_exit(0);
}
```


### Hasil Run program _soal4a_ saat dijalankan pada Linux
- Syntax : `./soal4a`<br />



## Soal 4B
<b>Batu kedua</b> adalah Amethyst. Batu mulia berwarna ungu mengkilat. Teka-tekinya adalah:
- Buatlah program C kedua dengan nama "4b.c". Program ini akan mengambil variabel hasil perkalian matriks dari program "4a.c" (program sebelumnya), dan tampilkan hasil matriks tersebut ke layar.<br />
(Catatan!: gunakan shared memory)
- Setelah ditampilkan, berikutnya untuk setiap angka dari matriks tersebut, carilah nilai faktorialnya, dan tampilkan hasilnya ke layar dengan format seperti matriks.<br />
```
Contoh: misal array [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], ...],

maka:

1 2 6 24
120 720 ... ...
...
```
(Catatan! : Harus menggunakan Thread dalam penghitungan
faktorial)

### Penyelesaian Soal 4B
- Masuk ke directory soal 4<br />
Syntax : `cd Modul3/soal4/`<br />
- Membuat file <b>soal4b.c</b> yang berisi program C<br />
Syntax : `touch soal4b.c`<br />
___source code : [soal4b.c](https://github.com/fikrihaykal/SoalShiftSISOP20_modul3_T20/blob/master/soal4/soal4b.c)___ <br />
- Mengompile program<br />
Syntax : `gcc -pthread soal4b.c -o soal4b`<br />
- Menjalankan program<br />
Syntax : `./soal4b`<br />

### Penjelasan Script yang ada di dalam file _soal4b.c_<br />
- Input library<br />
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
```

- Deklarasi variabel dan fungsi<br />
```
#define x 4
#define y 2
#define z 5

pthread_t tid[x*z];
pthread_attr_t attr;
int iret[x*z];
key_t key = 1234;
int *matrix;

void *hitung(void *arguments);
```

- Mengalokasikan _shared memory_<br />
```
    int shmid = shmget(key, sizeof(matrix), IPC_CREAT | 0666);
    matrix = shmat(shmid, 0, 0);
```

- Menampilkan matriks dari _shared memory_<br />
```
    int cnt=0;
    for(int i=1; i<x+1; i++){
        for(int j=1; j<z+1; j++){
            printf("%d\t", matrix[cnt]);
            cnt++;
        }
        printf("\n");
    }
    printf("\n");
```

- Memanggil fungsi hitung untuk setiap elemen matriks dengan fungsi `pthread_create()`<br />
```
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
```

- Memanggil fungsi `pthread_join`<br />
```
    for(int i=0; i<total; i++){
        pthread_join(tid[i], NULL);
    }
```

- Menutup shared memory<br />
```
    shmdt(matrix);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
```

- Fungsi untuk menghitung permutasi tambah tiap elemen matriks <br />
```
void *hitung(void *arguments){
    int temp=0;
    int c = *((int *)arguments);
    for(c; c>0; c--){
        temp=temp+c;
    }
    printf("%d\t", temp);
    pthread_exit(0);
}
```

### Hasil Run program _soal4b_ saat dijalankan pada Linux
- Syntax : `./soal4b`<br />



## Soal 4C
<b>Batu ketiga</b> adalah Onyx. Batu mulia berwarna hitam mengkilat. Pecahkan teka-teki berikut!
- Buatlah program C ketiga dengan nama "4c.c". Program ini tidak memiliki hubungan terhadap program yang lalu.
- Pada program ini, Norland diminta mengetahui jumlah file dan folder di direktori saat ini dengan command "ls | wc -l". Karena sudah belajar IPC, Norland mengerjakannya dengan semangat.<br />
(Catatan! : Harus menggunakan IPC Pipes)

### Penyelesaian Soal 4C
- Masuk ke directory soal 4<br />
Syntax : `cd Modul3/soal4/`<br />
- Membuat file <b>soal4c.c</b> yang berisi program C<br />
Syntax : `touch soal4c.c`<br />
___source code : [soal4c.c](https://github.com/fikrihaykal/SoalShiftSISOP20_modul3_T20/blob/master/soal4/soal4c.c)___ <br />
- Mengompile program<br />
Syntax : `gcc soal4c.c -o soal4c`<br />
- Menjalankan program<br />
Syntax : `./soal4c`<br />

### Penjelasan Script yang ada di dalam file _soal4c.c_<br />
- Input library<br />
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <wait.h>
```

- Menggunakan fungsi `fork()`<br />
```
    int fd[2];
    
    pid_t pid1;
    int status;

    pipe(fd);

    pid1 = fork();

    if(pid1 < 0){
        exit(EXIT_FAILURE);
    }
```

- Melakukan fungsi `execv()` serta menyimpannya pada pipe `fd[1]` dengan dup2<br />
```
    if(pid1 == 0){
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        char *argv[] = {"ls", NULL};
        execv("/bin/ls", argv);
    } 
```

- Membaca pipe `fd[0]` dengan dup2 dan melanjutkan fungsi `execv()`<br />
```
else{
        while(wait(&status) > 0);
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        char *argv[] = {"wc", "-l", NULL};
        execv("/usr/bin/wc", argv);
    }
```

### Hasil Run program _soal4c_ saat dijalankan pada Linux
- Syntax : `./soal4c`<br />


## KENDALA
