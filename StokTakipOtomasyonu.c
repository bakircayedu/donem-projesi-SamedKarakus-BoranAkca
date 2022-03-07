#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char kategori[20];
    int urunKodu;
    char urunAdi[20];
    float urunSatisFiyati;
    int stokMiktari;
} urun;


typedef struct{
    int tedarikciNo;
    char tedarikciAdi[20];
    char adres[50];
    char sehir[20];
} tedarikci;


typedef struct{
    int tedarikciNo;
    int urunKodu;
    int alisMiktari;
    float alisFiyati;

} urunStokGirisi;


int main(){

    printf("\nLutfen sistemin sizden istedigi bilgileri sirasiyla giriniz.\nDevam etmek icin tiklayiniz.\n\n");
    getch();

    urun urun1;
    printf("Urun adi: ");
    gets(urun1.urunAdi);

    printf("Kategori: ");
    gets(urun1.kategori);
    
    printf("Urun Kodu: ");
    scanf("%d", &urun1.urunKodu);

    printf("Miktar: ");
    scanf("%d", &urun1.stokMiktari);

    printf("Urun Satis Fiyati: ");
    scanf("%f", &urun1.urunSatisFiyati);

    printf("\n\n- Girilen urun bilgileri -\n\nUrun Adi: %s\nKategori: %s\nKod: %d\nMiktar: %d adet\nUrun Satis Fiyati: %.2f TL", urun1.urunAdi, urun1.kategori, urun1.urunKodu, urun1.stokMiktari, urun1.urunSatisFiyati);

    /*urunStokGirisi stok1 = {1235, 852, 15, 12};
    printf("%d", stok1.alisMiktari);*/

    getch();
}