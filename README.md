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

### Hasil Run program _soal3_ saat dijalankan pada Linux
- Perintah 1 : `./soal -d /adjaisd/`<br />

- Perintah 2 : `./soal -f /folderku/namafile.png`<br />

- Perintah 3 : `./soal \*`<br />



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

### Hasil Run program _soal4c_ saat dijalankan pada Linux
- Syntax : `./soal4c`<br />


## KENDALA
