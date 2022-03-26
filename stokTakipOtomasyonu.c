#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define baslangicMetni "- Stok Takip Sistemi -\nSistem uzerinde ne yapmak istediginizi seciniz\n\n1)Urun Islemleri\n2)Tedarikci Islemleri\n3)Urun Stok Islemleri"
#define urunVeriSecmeMetni "Sistem uzerinde ne yapmak istediginizi seciniz\n\n1)Urun Ekleme\n2)Urun Guncelleme\n"
#define tedarikciVeriSecmeMetni "Sistem uzerinde ne yapmak istediginizi seciniz\n\n1)Tedarikci Ekleme\n2)Tedarikci Guncelleme\n"
#define urunStokVeriSecmeMetni "Sistem uzerinde ne yapmak istediginizi seciniz\n\n1)Urun Stok Ekleme\n2)Urun Stok Guncelleme\n"
#define DEVAM "Devam etmek icin tiklayiniz."
#define bilgiGirisMetni "Lutfen sistemin sizden istedigi bilgileri sirasiyla giriniz.\n"
#define guncellemeMetni "\nHangi secenegi guncellemek istiyorsunuz?\n\n"

int urunVeriSecenegi, tedarikciVeriSecenegi, urunStokVeriSecenegi;
FILE *urunVeriDosyasi, *tedarikciVeriDosyasi, *urunStokVeriDosyasi;

enum genelSistemselSecenek{
    urunVerileri = 1, tedarikciVerileri, urunStokVerileri
}secenek;

enum urunIslemleri{
    urunEkleme = 1, urunGuncelleme
}urunSecenegi;

enum tedarikciIslemleri{
    tedarikciEkleme = 1, tedarikciGuncelleme
}tedarikciSecenegi;

enum urunStokIslemleri{
    urunStokEkleme = 1, urunStokGuncelleme
}urunStokSecenegi;

typedef struct{
    char kategori[20];          //Sabit
    int urunKodu;
    char urunAdi[20];
    float urunSatisFiyati;
    int stokMiktari;
} urun;

typedef struct{
    int tedarikciNo;
    char tedarikciAdi[20];
    char adres[50];
    char sehir[20];         //Sabit
} tedarikci;


typedef struct{
    int tedarikciNo;
    int urunKodu;
    int alisMiktari;
    float alisFiyati;
    int tarih;
} urunStok;


urun girilenUrunBilgileri;
tedarikci girilenTedarikciBilgileri;
urunStok girilenUrunStokBilgileri;

void sistemSecenegi(int sistemGirdisi);
void urunBilgiGirisi(FILE *urunVeriDosyasi);
void urunBilgiGuncelleme(FILE *urunVeriDosyasi);
void urunBilgileri (int girdi);
void tedarikciBilgileri(int tedarikciGirdi);
void tedarikciBilgiGirisi(FILE *tedarikciVeriDosyasi);
void tedarikciBilgiGuncelleme(FILE *tedarikciVeriDosyasi);
void urunStokBilgileri(int urunStokGirdi);
void urunStokBilgiGirisi(FILE *urunStokVeriDosyasi);
void urunStokBilgiGuncelleme(FILE *urunStokVeriDosyasi);

int main(){
    int baslangicSecenegi;
    printf("%s\n", baslangicMetni);
    scanf("%d", &baslangicSecenegi);

    sistemSecenegi(baslangicSecenegi);

    return 0;
}

///////////GENEL SİSTEMSEL FONKSİYON
void sistemSecenegi(int sistemGirdisi){
    switch(sistemGirdisi){
        case urunVerileri:
            printf("\n%s\n", urunVeriSecmeMetni);
            scanf("%d", &urunVeriSecenegi);
            urunBilgileri(urunVeriSecenegi);
            break;
        case tedarikciVerileri:
            printf("\n%s\n", tedarikciVeriSecmeMetni);
            scanf("%d", &tedarikciVeriSecenegi);
            tedarikciBilgileri(tedarikciVeriSecenegi);
            break;
        case urunStokVerileri:
            printf("\n%s\n", urunStokVeriSecmeMetni);
            scanf("%d", &urunStokVeriSecenegi);
            urunStokBilgileri(urunStokVeriSecenegi);
            break;
        default:
            printf("Lutfen gecerli degisken giriniz.");
            break;
    }
}
////////////////////////////////////////////

///////////////////////ÜRÜN İLE İLGİLİ FONKSİYONLAR
void urunBilgileri (int urunGirdi){
    switch (urunGirdi){
        case urunEkleme:
            printf("\n%s\n", bilgiGirisMetni);
            urunBilgiGirisi(urunVeriDosyasi);
            break;
        case urunGuncelleme:
            printf("%s", guncellemeMetni);
            urunBilgiGuncelleme(urunVeriDosyasi);
            break;
        default:
            printf("Lutfen gecerli degisken giriniz.");
            break;
    }
}

void urunBilgiGuncelleme(FILE *urunVeriDosyasi){  //Ürünün kayıtta olan verilerini sunar ve hangisini güncellemek istediğinin üzerinde durur.
    char urunAdi[20], kategori[20];
    int urunKodu, miktar, urunSatisFiyati;
    urunVeriDosyasi = fopen("urunVeriDosyasi.txt", "r");
    for(int i = 0; i < 2; i++){
        fscanf(urunVeriDosyasi, "%s %s %d %d %d", urunAdi, kategori, &urunKodu, &miktar, &urunSatisFiyati);

        printf("Urun adi: %s\n", urunAdi);
        printf("Kategori: %s\n", kategori);
        printf("Urun Kodu: %d\n", urunKodu);
        printf("Miktar: %d\n", miktar);
        printf("Urun Satis Fiyati: %d\n\n", urunSatisFiyati);
    }
    fclose(urunVeriDosyasi);
}

void urunBilgiGirisi(FILE *urunVeriDosyasi){
    char urunAdi[20], kategori[20];
    int urunKodu, miktar, urunSatisFiyati;
    urunVeriDosyasi = fopen("urunVeriDosyasi.txt", "a+");
    for(int i = 0; i < 1; i++){
        printf("Urun adi: ");
        scanf("%s", urunAdi);

        printf("Kategori: ");
        scanf("%s", kategori);

        printf("Urun Kodu: ");
        scanf("%d", &urunKodu);

        printf("Miktar: ");
        scanf("%d", &miktar);

        printf("Urun Satis Fiyati: ");
        scanf("%d", &urunSatisFiyati);

        fprintf(urunVeriDosyasi, "%s %s %d %d %d\n", urunAdi, kategori, urunKodu, miktar, urunSatisFiyati);
    }
    fclose(urunVeriDosyasi);
}
///////////////////////////////////////////////

///////////////////////TEDARİKÇİ İLE İLGİLİ FONKSİYONLAR
void tedarikciBilgileri(int tedarikciGirdi){
    switch(tedarikciGirdi){
        case tedarikciEkleme:
            printf("\n%s\n", bilgiGirisMetni);
            tedarikciBilgiGirisi(tedarikciVeriDosyasi);
            break;
        case tedarikciGuncelleme:
            printf("%s", guncellemeMetni);
            tedarikciBilgiGuncelleme(tedarikciVeriDosyasi);
            break;
        default:
            printf("Lutfen gecerli degisken giriniz.");
            break;
    }
}

void tedarikciBilgiGuncelleme(FILE *tedarikciVeriDosyasi){
    int tedarikciNo;
    char tedarikciAdi[20], adres[50], sehir[20];
    tedarikciVeriDosyasi = fopen("tedarikciVeriDosyasi.txt", "r");
    for(int i = 0; i < 1; i++){
        fscanf(tedarikciVeriDosyasi, "%d %s %s %s", &tedarikciNo, tedarikciAdi, adres, sehir);
        
        printf("Tedarikci No: %d\n", tedarikciNo);
        printf("Tedarikci Adi: %s\n", tedarikciAdi);
        printf("Adres: %s\n", adres);        
        printf("Sehir: %s\n\n", sehir);
    }
    fclose(tedarikciVeriDosyasi);
}

void tedarikciBilgiGirisi(FILE *tedarikciVeriDosyasi){
    int tedarikciNo;
    char tedarikciAdi[20], adres[50], sehir[20];
    tedarikciVeriDosyasi = fopen("tedarikciVeriDosyasi.txt", "a+");
    for(int i = 0; i < 1; i++){
        printf("Tedarikci No: ");
        scanf("%d", &tedarikciNo);

        printf("Tedarikci Adi: ");
        scanf("%s", tedarikciAdi);
        
        printf("Adres: ");
        scanf("%s", adres); //BOŞLUKLU ADRES YAZINCA KAYMA OLUYOR.
        
        printf("Sehir: ");
        scanf("%s", sehir);

        fprintf(tedarikciVeriDosyasi, "%d %s %s %s\n", tedarikciNo, tedarikciAdi, adres, sehir);
    }
    fclose(tedarikciVeriDosyasi);
}
/////////////////////////////////////////////////

/////////////////////////////ÜRÜN STOK İLE İLGİLİ FONKSİYONLAR
void urunStokBilgileri(int urunStokGirdi){
    switch(urunStokGirdi){
        case urunStokEkleme:
            printf("\n%s\n", bilgiGirisMetni);
            urunStokBilgiGirisi(urunStokVeriDosyasi);
            break;
        case urunStokGuncelleme:
            printf("%s", guncellemeMetni);
            urunStokBilgiGuncelleme(urunStokVeriDosyasi);
            break;
        default:
            printf("Lutfen gecerli degisken giriniz.");
            break;
    }
}

void urunStokBilgiGuncelleme(FILE *urunStokVeriDosyasi){
    int tedarikciNo, urunKodu, alisMiktari, tarih, alisFiyati;
    urunStokVeriDosyasi = fopen("urunStokVeriDosyasi.txt", "r");
    for(int i = 0; i < 1; i++){
        fscanf(urunStokVeriDosyasi, "%d %d %d %d %d", &tedarikciNo, &urunKodu, &alisMiktari, &alisFiyati, &tarih);
        
        printf("Tedarikci No: %d\n", tedarikciNo);
        printf("Urun Kodu: %d\n", urunKodu);
        printf("Alis Miktari: %d\n", alisMiktari);
        printf("Alis Fiyati: %d\n", alisFiyati);
        printf("Tarih: %d\n\n", tarih);
    }
    fclose(urunStokVeriDosyasi);
}

void urunStokBilgiGirisi(FILE *urunStokVeriDosyasi){
    int tedarikciNo, urunKodu, alisMiktari, tarih, alisFiyati;
    urunStokVeriDosyasi = fopen("urunStokVeriDosyasi.txt", "a+");
    for(int i = 0; i < 1; i++){
        printf("Tedarikci No: ");
        scanf("%d", &tedarikciNo);

        printf("Urun Kodu: ");
        scanf("%d", &urunKodu);
        
        printf("Alis Miktari: ");
        scanf("%d", &alisMiktari);

        printf("Alis Fiyati: ");
        scanf("%d", &alisFiyati);

        printf("Tarih: ");
        scanf("%d", &tarih);

        fprintf(urunStokVeriDosyasi, "%d %d %d %d %d\n", tedarikciNo, urunKodu, alisMiktari, alisFiyati, tarih);
    }
    fclose(urunStokVeriDosyasi);
}
/////////////////////////////////////////////////
