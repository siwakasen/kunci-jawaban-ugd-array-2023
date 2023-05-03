#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

typedef char string[50];

int checkLog(string user, string pass);
int getEmptyIndex(string kode_koin[]);
bool checkSameCode(string kode, string kode_koin[]);
void show(string nama_koin[],string kode_koin[], float harga_koin[]);
void showMarket(string kode_koin[], float harga_koin[]);
int findCoin(string kode, string kode_koin[]);
void sorting(string nama_koin[],string kode_koin[], float harga_koin[]);
void newPrice(float harga_koin[]);

int main(int argc, char *argv[]) {
	srand(time(NULL));
	string nama_koin[10] ={"Bitcoin","Ethereum","Tether","Cardano","Dogecoin",
						   "Polygon","Solana","Litecoin","Shiba Inu","Chainlink"};
	string kode_koin[10]={"BTC","ETH","USDT","ADA","DOGE",
						  "MATIC","SOL","LTC","SHIB","LINK"};
	float harga_koin[10]={29000,1912,1,0.41,0.08,
						   1.02,23.41,91,0.01,7.21};

	string user,pass;
	int menu,index,n=1;
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
				printf("\n\t--=== [CryptoCurrency] ===--\n");
				printf("\n[1] Tambah Crypto");
				printf("\n[2] Tampil Crypto");
				printf("\n[3] Ubah Data Crypto");
				printf("\n[4] Hapus Crypto");
				printf("\n[0] Logout");
				printf("\n[5] Sorting by Kode Koin (Bonus)");
				printf("\n>>> "); scanf("%d", &menu);
				switch(menu){
					case 1:
						index=getEmptyIndex(kode_koin);
						if(index!=-1){
							printf("[Tambah Crypto]\n");
							do{
								printf("\nNama koin : "); fflush(stdin); gets(nama);
								if(strlen(nama)==0) printf("\n\t[!] Nama tidak boleh kosong");
							}while(strlen(nama)==0);
							do{
								printf("\nKode koin : "); fflush(stdin); gets(kode);
								if(strlen(kode)<3 || strlen(kode)>5) printf("\t[!] Kode koin harus berjumlah 3 s/d 5 karakter\n");
								else if(checkSameCode(kode,kode_koin)) printf("\n\t[!] Kode koin tidak boleh sama\n");
							}while((strlen(kode)<3 || strlen(kode)>5) || checkSameCode(kode,kode_koin));
							do{
								printf("\nHarga koin : "); scanf("%f",&harga);
								if(harga<0) printf("\n\t[!] Harga koin tidak boleh minus");
							}while(harga<0);
							strcpy(nama_koin[index],nama);
							strcpy(kode_koin[index],kode);
							harga_koin[index]=harga;
							printf("\n\t[+] Berhasil menambah data Crypto");
						}else{
							printf("\n\t[!] Data Crypto sudah penuh");
						}
					break;
					case 2:
						show(nama_koin,kode_koin,harga_koin);
					break;
					case 3:
						printf("[Ubah Data Crypto]\n");
						printf("\nMasukkan kode koin yang ingin diubah : "); fflush(stdin); gets(kode);
						index=findCoin(kode,kode_koin);
						if(index!=-1){
							do{
								printf("\nNama koin baru : "); fflush(stdin); gets(nama);
								if(strlen(nama)==0) printf("\n\t[!] Nama tidak boleh kosong");
							}while(strlen(nama)==0);
							do{
								printf("\nKode koin baru: "); fflush(stdin); gets(kode);
								if(strlen(kode)<3 || strlen(kode)>5) printf("\n\t[!] Kode koin harus berjumlah 3 s/d 5 karakter\n");
								else if(checkSameCode(kode,kode_koin)) printf("\n\t[!] Kode koin tidak boleh sama\n");
							}while((strlen(kode)<3 || strlen(kode)>5) || checkSameCode(kode,kode_koin));
							strcpy(nama_koin[index],nama);
							strcpy(kode_koin[index],kode);
							printf("\n\t[+] Berhasil mengubah data Crypto");
						}else{
							printf("\n\t[!] Kode koin yang dicari tidak ditemukan");
						}
					break;
					case 4:
						printf("[Hapus Crypto]\n");
						printf("\nMasukkan kode koin yang ingin dihapus : "); fflush(stdin); gets(kode);
						index=findCoin(kode,kode_koin);
						if(index!=-1){
							strcpy(nama_koin[index],"");
							strcpy(kode_koin[index],"");
							harga_koin[index]=0;
							printf("\n\t[+] Berhasil menghapus data Crypto");
						}else{
							printf("\n\t[!] Kode koin yang dicari tidak ditemukan");
						}
					break;
					case 5:
						sorting(nama_koin,kode_koin,harga_koin);
						printf("[~] Berhasil men-sorting crypto");
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
				printf("\n\t--=== [CryptoCurrency] ===--\n");
				printf("\n[1] Cryptoprice");
				printf("\n[2] Cari by Kode Koin");
				printf("\n[0] Logout");
				printf("\n[3] Next Day (Bonus)");
				printf("\n>>> "); scanf("%d", &menu);
				switch(menu){
					case 1:
						printf("\n[Cryptoprice Today]\n");
						showMarket(kode_koin,harga_koin);
					break;
					case 2:
						printf("[Cari Crypto]\n");
						printf("\nMasukkan kode koin yang ingin dicari : "); fflush(stdin); gets(kode);
						index=findCoin(kode,kode_koin);
						if(index!=-1){
							printf("\nNama koin  : %s",nama_koin[index]);
							printf("\nKode koin  : %s",kode_koin[index]);
							printf("\nHarga koin : %.2f $",harga_koin[index]);
						}else{
							printf("\n\t[!] Kode koin yang dicari tidak ditemukan");
						}
					break;
					case 3:
						newPrice(harga_koin);
						printf("\n\t[Hari ke-%d]",++n);
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
	if(strcmp(user,"koin")==0 && strcmp(pass,"kripto")==0) return 1;
	else if(strcmp(user,"guest")==0 && strcmp(pass,"guest")==0) return 2;
	else if(strcmp(user,"0")==0 && strcmp(pass,"0")==0) return 0;
	else return -1; 
}

int getEmptyIndex(string kode_koin[]){
	int i;
	for(i=0;i<10;i++){
		if(strcmp(kode_koin[i],"")==0) return i;
	}
	return -1;
}
bool checkSameCode(string kode, string kode_koin[]){
	int i;
	for(i=0;i<10;i++){
		if(strcmpi(kode,kode_koin[i])==0) return true;
	}
	return false;
}
void show(string nama_koin[],string kode_koin[], float harga_koin[]){
	int i;
	printf("[Kode]		[Harga]");
	for(i=0;i<10;i++){
		if(strlen(kode_koin[i])!=0){
			printf("\n%s		%.2f $",kode_koin[i],harga_koin[i]);
			printf("\n%s",nama_koin[i]);
		}
	}
}
int findCoin(string kode, string kode_koin[]){
	int i;
	for(i=0;i<10;i++){
		if(strcmpi(kode,kode_koin[i])==0) return i;
	}
	return -1;
}
void showMarket(string kode_koin[], float harga_koin[]){
	int i;
	printf("[Kode]	[Harga]");
	for(i=0;i<10;i++){
		if(strlen(kode_koin[i])!=0){
			printf("\n%s	%.2f $",kode_koin[i],harga_koin[i]);
		}
	}
}
void sorting(string nama_koin[],string kode_koin[], float harga_koin[]){
	string n,k;
	float h;
	int i,j;
	for(i=0;i<9;i++){
		for(j=i+1;j<10;j++){
			if(strcmp(kode_koin[i],kode_koin[j])<0){
				strcpy(n,nama_koin[i]);
				strcpy(k,kode_koin[i]);
				h=harga_koin[i];

				strcpy(nama_koin[i],nama_koin[j]);
				strcpy(kode_koin[i],kode_koin[j]);
				harga_koin[i]=harga_koin[j];

				strcpy(nama_koin[j],n);
				strcpy(kode_koin[j],k);
				harga_koin[j]=h;
			}
		}
	}
}
void newPrice(float harga_koin[]){
	float temp;
	int i;

	for(i=0;i<10;i++){
		do{
			temp=(((float)rand()/(float)(RAND_MAX)) * 10.16)-5.15;
		}while(harga_koin[i]+temp<0);
		harga_koin[i]+=temp;
	}
}
