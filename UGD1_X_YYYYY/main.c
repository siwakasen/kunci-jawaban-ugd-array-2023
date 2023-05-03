#include <stdio.h>
#include <stdlib.h>
#include <string.h>  //library untuk memakai function string
#include <time.h>    //library yg digunakan saat membuat angka random
#include <conio.h>   //library untuk getch()  *beberapa IDE untuk c tidak perlu memanggil library ini karena sudah otomatis diisi

typedef char string[100];

int checkLog(string user, string pass);
int getIndex(string emiten[]);
int checkCode(string kode[], string code);

void tampil(string emiten[], string kode[], int harga[]);
void tampilKode(string kode[], int harga[]);
void sorting(string emiten[], string kode[], int harga[]);
void newPrice(int harga[], int history[10][10], int *day);
void oldPrice(int history[10][10], int day, string kode[], int harga[]);


int main(int argc, char *argv[]) {
    
    string emiten[10] = {"Sido Muncul", "Bank Central Asia", "Indofood Sukses Makmur", "Bank Mandiri", "Bank Rakyat Indonesia",
                         "Bank Negara Indonesia", "Astra Internasional", "Telkom Indonesia", "Unilever Indonesia", "Gojek Tokopedia"};
    string kode[10] = {"SIDO", "BBCA", "INDF", "BMRI", "BBRI",
                       "BBNI", "ASII", "TLKM", "UNVR", "GOTO"};
    int harga[10] = {865, 8675, 6575, 10125, 4760, 8950, 5750, 4040, 4350, 120};

    string user,pass;
    string name,code;
    int harga_saham;
    int menu, index,day=1;
    int history[10][10];

    do{
        do{
            system("cls");
            printf("\n\t\t[Menu Login]\n");
            printf("\n\tUsername : "); fflush(stdin); gets(user);
            printf("\n\tPassword : "); fflush(stdin); gets(pass);
            if(checkLog(user,pass)==0){
                printf("\n\t[!] Username atau password salah"); getch();
            }
        }while(checkLog(user,pass)==0);

        if(checkLog(user,pass)==1){
            do{
                system("cls");
                printf("\n\t--== [Indonesia Stock Exchange] ==--\n");
                printf("\n[1] Tambah emiten");
                printf("\n[2] Tampil emiten");
                printf("\n[3] Ubah data emiten");
                printf("\n[4] Hapus emiten");
                printf("\n[0] Log out");
                printf("\n[5] Sorting by Kode Saham (Bonus)");
                printf("\n>>> "); scanf("%d", &menu);
                switch(menu){
                    case 1:
                        if(getIndex(emiten)!=-1){
                            index=getIndex(emiten);
                            do{
                                printf("\nNama perusahaan : "); fflush(stdin); gets(name);
                                if(strlen(name)==0){
                                    printf("\n\t[!] Nama tidak boleh kosong");getch();
                                }
                            }while(strlen(name)==0);
                            do{
                                printf("\nKode saham : "); fflush(stdin); gets(code);
                                if(strlen(code)!=4){
                                    printf("\n\t[!] kode saham harus memiliki 4 karakter");getch();
                                }else if(checkCode(kode,code)!=-1){
                                    printf("\n\t[!] Kode saham tidak boleh sama");getch();
                                }
                            }while(strlen(code)!=4 || checkCode(kode,code)!=-1);
                            do{
                                printf("\nHarga per lembar saham : "); scanf("%d", &harga_saham);
                                if(harga_saham<0){
                                    printf("\n\t[!] Harga saham tidak boleh kurang dari 0");getch();
                                }
                            }while(harga_saham<0);
                            strcpy(emiten[index],name);
                            strcpy(kode[index],code);
                            harga[index]=harga_saham;
                            printf("\n\t[!] Berhasil menambah data");
                        }else{
                            printf("\n\t[!] Data emiten sudah penuh");
                        }
                    break;
                    case 2:
                        tampil(emiten,kode,harga);
                    break;
                    case 3:
                        printf("\nMasukkan kode saham yang dicari : "); fflush(stdin); gets(code);
                        if(checkCode(kode,code)!=-1 && strlen(code)!=0){
                            index=checkCode(kode,code);
                            do{
                                printf("\nNama perusahaan : "); fflush(stdin); gets(name);
                                if(strlen(name)==0){
                                    printf("[!] Nama tidak boleh kosong");getch();
                                }
                            }while(strlen(name)==0);
                            do{
                                printf("\nKode saham : "); fflush(stdin); gets(code);
                                if(strlen(code)!=4){
                                    printf("\n\t[!] kode saham harus memiliki 4 karakter"); getch();   
                                }else if(checkCode(kode,code)!=-1){
                                    printf("\n\t[!] Kode saham tidak boleh sama"); getch();
                                }
                            }while(strlen(code)!=4 || checkCode(kode,code)!=-1);
                            strcpy(emiten[index],name);
                            strcpy(kode[index],code);
                            printf("\n\t[~] Berhasil mengubah data");
                        }else{
                            printf("\n\t[!] Kode saham yang dicari tidak ditemukan");
                        }
                    break;
                    case 4:
                        printf("\nMasukkan kode saham yang akan dihapus : "); fflush(stdin); gets(code);
                        if(checkCode(kode,code)!=-1 && strlen(code)!=0){
                            index=checkCode(kode,code);
                            strcpy(emiten[index],"");
                            strcpy(kode[index],"");
                            harga[index]=0;
                            printf("\n\t[~] Berhasil menghapus data");
                        }else{
                            printf("\n\t[!] Kode saham yang dicari tidak ditemukan");
                        }
                    break;
                    case 0:
                        printf("\n\t[~] Log out . . .");
                    break;
                    case 5:
                        sorting(emiten,kode,harga);
                        printf("\n\t[~] berhasil men-sorting data");
                    break;
                    default:
                        printf("\n\t[!] Menu tidak ditemukan");
                    break;
                }getch();
            }while(menu!=0);

        }else if(checkLog(user,pass)==2){
            do{
                system("cls");
                printf("\n\t--== [Indonesia Stock Exchange] ==--\n");
                printf("\n[1] Marketprice");
                printf("\n[2] Cari by Kode Saham");
                //printf("\n[4] History Harga Saham (Bonus)");
                printf("\n[0] Log out");
                printf("\n[3] Next Day (Bonus)");
                printf("\n>>> "); scanf("%d", &menu);
                switch(menu){
                    case 1:
                        system("cls");
                        printf("\n[Marketprice Today]");
                        tampilKode(kode,harga);
                    break;
                    case 2:
                        printf("\nMasukkan kode saham yang dicari: "); fflush(stdin); gets(code);
                            if(checkCode(kode,code)!=-1 && strlen(code)!=0){
                                index=checkCode(kode,code);
                                printf("\nNama perusahaan : %s",emiten[index]);
                                printf("\nKode saham      : %s",kode[index]);
                                printf("\nHarga per lembar saham : %d",harga[index]);
                            }else{
                                printf("\n\t[!] Kode saham yang dicari tidak ditemukan");
                            }
                    break;
                    case 3:
                        newPrice(harga,history,&day);
                    break;
                    // case 4:
                    //     oldPrice(history,day,kode,harga); //*bersyukurlah yg ini ga jadi ditambahin
                    // break;
                    case 0:
                        printf("\n\t[~] Log out  . . .");
                    break;
                    default:
                        printf("\n\t[!] Menu tidak ditemukan");
                    break;
                }getch();
            }while(menu!=0);
        }else if(checkLog(user,pass)==-1){
        	printf("\n\t[*] Keluar dari program [*]");
		}
    }while(checkLog(user,pass)!=-1);

    return 0;
}
int checkLog(string user, string pass){  // ---->>  fungsi ini akan mengecek user mana yang melakukan login
    if(strcmp(user,"bursa")==0 && strcmp(pass,"efek")==0){ //kondisi sebagai pengelola 
        return 1;
    }else if(strcmp(user,"guest")==0 && strcmp(pass,"guest")==0){ //kondisi sebagai pengunjung
        return 2;
    }else if(strcmp(user,"0")==0 && strcmp(pass,"0")==0){ //kondisi jika ingin keluar dari program
        return -1; 
    }else{
        return 0; // jika memenuhi kondisi di atas (inputan username/password salah) maka return 0
    }
}
int getIndex(string emiten[]){  //untuk menemukan index yang belum berisi data
    int i;
    for(i=0;i<10;i++){
        if(strlen(emiten[i])==0) return i;
    }
    return -1;
}
int checkCode(string kode[], string code){ //untuk menyocokkan kode inputan dengan kode array dan akan mengembalikan indexnya
    int i;                                 //selain itu digunakan untuk mengecek jika terdapat inputan kode yang sama
    for(i=0;i<10;i++){
        if(strcmpi(kode[i],code)==0){
            return i;
        }
    }
    return -1;
}
void tampil(string emiten[], string kode[], int harga[]){  //menampilkan semua data(kode saham,harga saham, nama perusahaan terbuka(emiten))
    int i;
    printf("\n[Kode]\t\t\t[Harga]");
    for(i=0;i<10;i++){
        if(strlen(emiten[i])!=0){
        printf("\n%s\t\t\t%d",kode[i],harga[i]);
        printf("\n%s",emiten[i]);
        }
    }
}

void sorting(string emiten[], string kode[], int harga[]){ //untuk mensorting data menggunakan kode sahamnya
    int i,j;                                               //data akan diurutkan dari a ke z (ascending)
    string tempE;
    string tempK;
    int tempH;
    for(i=0;i<10;i++){
        for(j=i+1;j<10;j++){
            if(strcmp(kode[i],kode[j])>0){  //kondisi jika kode ke-j hurufnya lebih lebih awal dari kode ke-i
                strcpy(tempE,emiten[i]);                
                strcpy(tempK,kode[i]);          //pertama data ke-i disimpan ke temp
                tempH=harga[i];

                strcpy(emiten[i],emiten[j]);            //data ke-i ditimpa data ke-j
                strcpy(kode[i],kode[j]);
                harga[i]=harga[j];

                strcpy(emiten[j],tempE);               //data ke-j ditimpa data temp (data ke-i)
                strcpy(kode[j],tempK);
                harga[j]=tempH;
            }
        }
    }
}
void newPrice(int harga[], int history[10][10], int *day){ //pada prosedur ini akan mengenerate harga baru dari saham (harga next daynya)
    srand(time(NULL));                                     //dan harga lama akan dipindahkan ke array history harga
    int temp;                                              //variabel day akan digunakan untuk menghitung sudah berapa kali dilakukan next day
    int i=0,j;                                             //sehingga pada prosedur oldPrice bisa ditentukan sebanyak berapa index harga yang
    printf("\nHari ke-%d",++(*day));                       //akan ditampilkan
    for(j=0;j<10;j++){
        history[i][j]=harga[j];
    }
    
    for(i=0;i<10;i++){                              //akan melakukan perulangan sebanyak  (10) mengapa? karena ada 10 emiten
        do{
            temp=(rand() %(25-(-25)+1)+(-25));
        }while( harga[i]+temp<0 || (harga[i]+temp)%5!=0);                    //jika penjumlahan harga saat ini dengan hasil angka random itu minus maka akan mengulang mencari angka random baru
        harga[i]+=temp;
    }
    
    for(i=9;i>0;i--){
        for(j=9;j>=0;j--){
            history[i][j]=history[i-1][j];         //pada perulangan ini akan mengcopy dari blakang (data akan mundur ke index+1)
        }
    }
}
void oldPrice(int history[10][10], int day,string kode[], int harga[]){    //pada prosedur ini akan menampilkan harga saat ini dan harga sebelumnya
    int i=0,j,k;                                                             //dari harga saham
    int temp;

    for(j=0;j<10;j++){
        history[i][j]=harga[j];
    }

    for(j=0;j<10;j++){          
        temp=day;                            //temp ini akan berfungsi untuk menentukan seberapa banyak hari yang tampil pada history harga
        printf("\n[%s]\t",kode[j]);
        for(i=0;i<10;i++){
            if(temp>0){
                printf("|%d",history[i][j]);     //perulangan untuk menampilkan history ini menggunakan array dua dimensi
                temp--;                          //visualisasinya bisa dilihat di bawah!!
            }                                    
        }                                        
        printf("|");
    }
}
void tampilKode(string kode[], int harga[]){ //hanya menampilkan kode saham dan harganya
    int i;
    printf("\n[Kode]\t[Harga]");
    for(i=0;i<10;i++){
        if(strlen(kode[i])!=0){
        printf("\n %s\t  %d",kode[i],harga[i]);
        }
    }
}
//visualisasi history 
/* (perulangannya terbalik karena kita ingin menampilkan data sebelumnya *memang sedikit mind-blowing)

            hari (i) [0-saat ini] [1-satu hari sebelum]  [2]       [3]      [4]      [5]
  kode (j)    
     0  sido              100             120          .....       ....      ....    ....
     1  bbri              250             255           ....      ....        ...    ..
     2  bbca              256             258            ......  ...          ... begitu seterusnya
     3  asii              178             170
     4  tlkm              125             120
     5  bmri              456             450
*/
