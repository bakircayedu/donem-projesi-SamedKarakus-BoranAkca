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

int urunVeriSecenegi, tedarikciVeriSecenegi, urunStokVeriSecenegi;

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
void urunBilgiGirisi(char x[20], char y[20], int z, int k, float i);
void urunBilgileri (int girdi);
void tedarikciBilgileri(int tedarikciGirdi);
void tedarikciBilgiGirisi(int x, char y[20], char z[100], char a[30]);
void urunStokBilgileri(int urunStokGirdi);
void urunStokBilgiGirisi(int x, int y, int z, float a, int b);

int main(){
    int baslangicSecenegi;
    printf("%s\n", baslangicMetni);
    scanf("%d", &baslangicSecenegi);

    sistemSecenegi(baslangicSecenegi);


    //urunBilgileri(baslangicSecenegi);

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
            //urunBilgileri(tedarikciVeriSecenegi);
            break;
        case urunStokVerileri:
            printf("\n%s\n", urunStokVeriSecmeMetni);
            scanf("%d", &urunStokVeriSecenegi);
            //urunBilgileri(urunStokVeriSecenegi);
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
        urunBilgiGirisi(girilenUrunBilgileri.urunAdi, girilenUrunBilgileri.kategori, girilenUrunBilgileri.urunKodu, girilenUrunBilgileri.stokMiktari, girilenUrunBilgileri.urunSatisFiyati);
        break;
    //case urunGuncelleme:

    default:
        printf("Lutfen gecerli degisken giriniz.");
        break;
    }
}

void urunBilgiGirisi(char x[20], char y[20], int z, int k, float i){
    printf("Urun adi: ");
    gets(x);

    printf("Kategori: ");
    gets(y);
    
    printf("Urun Kodu: ");
    scanf("%d", &z);

    printf("Miktar: ");
    scanf("%d", &k);

    printf("Urun Satis Fiyati: ");
    scanf("%f", &i);
}
///////////////////////////////////////////////

///////////////////////TEDARİKÇİ İLE İLGİLİ FONKSİYONLAR
void tedarikciBilgileri(int tedarikciGirdi){
    switch(tedarikciGirdi){
        case tedarikciEkleme:
        printf("\n%s\n", bilgiGirisMetni);
        tedarikciBilgiGirisi(girilenTedarikciBilgileri.tedarikciNo, girilenTedarikciBilgileri.tedarikciAdi, girilenTedarikciBilgileri.adres, girilenTedarikciBilgileri.sehir);
        break;
        //case tedarikciGuncelleme:

        default:
            printf("Lutfen gecerli degisken giriniz.");
            break;
    }
}

void tedarikciBilgiGirisi(int x, char y[20], char z[100], char a[30]){
    printf("Tedarikci No: ");
    scanf("%d", &x);

    printf("Tedarikci Adi: ");
    gets(y);
    
    printf("Adres: ");
    gets(z);

    printf("Sehir: ");
    gets(a);   
}
/////////////////////////////////////////////////

/////////////////////////////ÜRÜN STOK İLE İLGİLİ FONKSİYONLAR
void urunStokBilgileri(int urunStokGirdi){
    switch(urunStokGirdi){
        case urunStokEkleme:
            printf("\n%s\n", bilgiGirisMetni);
            urunStokBilgiGirisi(girilenUrunStokBilgileri.tedarikciNo, girilenUrunStokBilgileri.urunKodu, girilenUrunStokBilgileri.alisMiktari, girilenUrunStokBilgileri.alisFiyati, girilenUrunStokBilgileri.tarih);
            break;
        //case urunStokGuncelleme:

        default:
            printf("Lutfen gecerli degisken giriniz.");
            break;
    }
}

void urunStokBilgiGirisi(int x, int y, int z, float a, int b){
    printf("Tedarikci No: ");
    scanf("%d", &x);

    printf("Urun Kodu: ");
    scanf("%d", &y);
    
    printf("Alis Miktari: ");
    scanf("%d", &z);

    printf("Alis Fiyati: ");
    scanf("%f", &a);

    printf("Tarih: ");
    scanf("%d", &b);
}

/////////////////////////////////////////////////
