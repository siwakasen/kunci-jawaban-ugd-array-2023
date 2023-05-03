#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

typedef char string[50];

int checkLog(string user, string pass);
int getEmptyIndex(string kode_barang[]);
bool checkSameCode(string kode, string kode_barang[]);
void show(string nama_barang[],string kode_barang[], float harga_barang[]);
void showMarket(string kode_barang[], float harga_barang[]);
int findItem(string kode, string kode_barang[]);
void sorting(string nama_barang[],string kode_barang[], float harga_barang[]);
void newPrice(float harga_barang[]);

int main(int argc, char *argv[]) {
	srand(time(NULL));
	string nama_barang[10] ={"Razer Viper Mini","Apple Macbook Air 2020",
                            "XBOX Series S","Iphone 12 Mini","HyperX Cloud II","Lenovo Ideapad 3",
                            "Nintendo Switch","Rexus Daxa Air IV","Intel Core I5 Gen 12","SSD 256GB"};
    string kode_barang[10]={"RZM","MAC20","XBXS","IP12M","HXCII","LNID3",
							"NTDS","RXDA4","ICI5","SSD"};
    float harga_barang[10]={8.59,999.99,559.31,632.32 ,13.45,19.72,89.41,
                            30.15,400.99,5.21};

	string user,pass;
	int menu,index,hari=1;
	string nama,kode;
	float harga;
	do{
		system("cls");
		printf("\n\t[Menu Login]\n");
		printf("\n\tUsername : "); fflush(stdin); gets(user);
		printf("\tPassword : "); fflush(stdin); gets(pass);
		if(checkLog(user,pass)==1){
			do{
				system("cls");
				printf("\n\t--=== [Auction Online] ===--\n");
				printf("\n[1] Tambah Barang");
				printf("\n[2] Tampil Barang");
				printf("\n[3] Ubah Data Barang");
				printf("\n[4] Hapus Barang");
				printf("\n[0] Logout");
				printf("\n[5] Sorting by Kode Barang (Bonus)");
				printf("\n>>> "); scanf("%d", &menu);
				switch(menu){
					case 1:
						index=getEmptyIndex(kode_barang);
						if(index!=-1){
							printf("[Tambah Barang]\n");
							do{
								printf("\nNama barang : "); fflush(stdin); gets(nama);
								if(strlen(nama)==0) printf("\n\t[!] Nama tidak boleh kosong");
							}while(strlen(nama)==0);
							do{
								printf("\nKode barang : "); fflush(stdin); gets(kode);
								if(strlen(kode)<3 || strlen(kode)>5) printf("\t[!] Kode barang harus berjumlah 3 s/d 5 karakter\n");
								else if(checkSameCode(kode,kode_barang)) printf("\n\t[!] Kode barang tidak boleh sama\n");
							}while((strlen(kode)<3 || strlen(kode)>5) || checkSameCode(kode,kode_barang));
							do{
								printf("\nHarga barang : "); scanf("%f",&harga);
								if(harga<0) printf("\n\t[!] Harga barang tidak boleh minus");
							}while(harga<0);
							strcpy(nama_barang[index],nama);
							strcpy(kode_barang[index],kode);
							harga_barang[index]=harga;
							printf("\n\t[+] Berhasil menambah data barang");
						}else{
							printf("\n\t[!] Data Barang sudah penuh");
						}
					break;
					case 2:
						show(nama_barang,kode_barang,harga_barang);
					break;
					case 3:
						printf("[Ubah Data Barang]\n");
						printf("\nMasukkan kode barang yang ingin diubah : "); fflush(stdin); gets(kode);
						index=findItem(kode,kode_barang);
						if(index!=-1){
                            printf("\nNama barang  : %s",nama_barang[index]);
							printf("\nKode barang  : %s",kode_barang[index]);
							printf("\nHarga barang : %.2f $\n",harga_barang[index]);
							do{
								printf("\nHarga barang baru: "); scanf("%f",&harga);
								if(harga<0) printf("\n\t[!] Harga barang tidak boleh minus");
							}while(harga<0);
							harga_barang[index]=harga;
							printf("\n\t[+] Berhasil mengubah harga barang");
						}else{
							printf("\n\t[!] Kode barang yang dicari tidak ditemukan");
						}
					break;
					case 4:
						printf("[Hapus Barang]\n");
						printf("\nMasukkan kode barang yang ingin dihapus : "); fflush(stdin); gets(kode);
						index=findItem(kode,kode_barang);
						if(index!=-1){
							strcpy(nama_barang[index],"");
							strcpy(kode_barang[index],"");
							harga_barang[index]=0;
							printf("\n\t[+] Berhasil menghapus data barang");
						}else{
							printf("\n\t[!] Kode barang yang dicari tidak ditemukan");
						}
					break;
					case 5:
						sorting(nama_barang,kode_barang,harga_barang);
						printf("[~] Berhasil men-sorting Barang");
					break;
					case 0:
						printf("\n\t[~] Logout berhasil . . .");
					break;
					default:
						printf("\n\t[!] Menu tidak tersedia");
					break;
				}getch();
			}while(menu!=0);
		}else if(checkLog(user,pass)==2){
			do{
				system("cls");
				printf("\n\t--=== [Auction Online] ===--\n");
				printf("\n[1] Live price");
				printf("\n[2] Cari by Kode Barang");
				printf("\n[0] Logout");
				printf("\n[3] Next Day (Bonus)");
				printf("\n>>> "); scanf("%d", &menu);
				switch(menu){
					case 1:
						printf("\n[Live price]\n");
						showMarket(kode_barang,harga_barang);
					break;
					case 2:
						printf("[Cari Barang]\n");
						printf("\nMasukkan kode barang yang ingin dicari : "); fflush(stdin); gets(kode);
						index=findItem(kode,kode_barang);
						if(index!=-1){
							printf("\nNama barang  : %s",nama_barang[index]);
							printf("\nKode barang  : %s",kode_barang[index]);
							printf("\nHarga barang : %.2f $",harga_barang[index]);
						}else{
							printf("\n\t[!] Kode barang yang dicari tidak ditemukan");
						}
					break;
					case 3:
						newPrice(harga_barang);
						printf("\n\t[Hari ke-%d]",++hari);
					break;
					case 0:
						printf("\n\t[~] Logout berhasil . . .");
					break;
					default:
						printf("\n\t[!] Menu tidak tersedia");
					break;
				}getch();
			}while(menu!=0);
		}else if(checkLog(user,pass)==0){
			printf("\n\t[~] Keluar dari program");
		}else{
			printf("\n\t[!] Username atau Password salah"); getch(); 
		}
	}while(checkLog(user,pass)!=0);
	return 0;
}

int checkLog(string user, string pass){
	if(strcmp(user,"auction")==0 && strcmp(pass,"sg")==0) return 1;
	else if(strcmp(user,"guest")==0 && strcmp(pass,"guest")==0) return 2;
	else if(strcmp(user,"0")==0 && strcmp(pass,"0")==0) return 0;
	else return -1; 
}

int getEmptyIndex(string kode_barang[]){
	int i;
	for(i=0;i<10;i++){
		if(strcmp(kode_barang[i],"")==0) return i;
	}
	return -1;
}
bool checkSameCode(string kode, string kode_barang[]){
	int i;
	for(i=0;i<10;i++){
		if(strcmpi(kode,kode_barang[i])==0) return true;
	}
	return false;
}
void show(string nama_barang[],string kode_barang[], float harga_barang[]){
	int i;
	printf("[Kode]		        [Harga]");
	for(i=0;i<10;i++){
		if(strlen(kode_barang[i])!=0){
			printf("\n%s		        %.2f $",kode_barang[i],harga_barang[i]);
			printf("\n%s",nama_barang[i]);
		}
	}
}
int findItem(string kode, string kode_barang[]){
	int i;
	for(i=0;i<10;i++){
		if(strcmpi(kode,kode_barang[i])==0) return i;
	}
	return -1;
}
void showMarket(string kode_barang[], float harga_barang[]){
	int i;
	printf("[Kode]	[Harga]");
	for(i=0;i<10;i++){
		if(strlen(kode_barang[i])!=0){
			printf("\n%s	%.2f $",kode_barang[i],harga_barang[i]);
		}
	}
}
void sorting(string nama_barang[],string kode_barang[], float harga_barang[]){
	string n,k;
	float h;
	int i,j;
	for(i=0;i<9;i++){
		for(j=i+1;j<10;j++){
			if(strcmp(kode_barang[i],kode_barang[j])>0){
				strcpy(n,nama_barang[i]);
				strcpy(k,kode_barang[i]);
				h=harga_barang[i];

				strcpy(nama_barang[i],nama_barang[j]);
				strcpy(kode_barang[i],kode_barang[j]);
				harga_barang[i]=harga_barang[j];

				strcpy(nama_barang[j],n);
				strcpy(kode_barang[j],k);
				harga_barang[j]=h;
			}
		}
	}
}
void newPrice(float harga_barang[]){
	float temp;
	int i;

	for(i=0;i<10;i++){
		do{
			temp=(((float)rand()/(float)(RAND_MAX)) * 130.50)-50.49;
		}while(harga_barang[i]+temp<0);
		harga_barang[i]+=temp;
	}
}
