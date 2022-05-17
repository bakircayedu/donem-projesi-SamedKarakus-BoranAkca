#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#define baslangicMetni "- Stok Takip Sistemi -\nSistem uzerinde ne yapmak istediginizi seciniz\n\n1)Urun Islemleri\n2)Tedarikci Islemleri\n3)Urun Stok Islemleri\n4)Cikis"
#define urunVeriSecmeMetni "Sistem uzerinde ne yapmak istediginizi seciniz\n\n1)Urun Ekleme\n2)Urun Guncelleme\n3)Urun Silme\n4)Urun Arama\n"
#define tedarikciVeriSecmeMetni "Sistem uzerinde ne yapmak istediginizi seciniz\n\n1)Tedarikci Ekleme\n2)Tedarikci Guncelleme\n3)Tedarikci Silme\n4)Tedarikci Arama\n"
#define urunStokVeriSecmeMetni "Sistem uzerinde ne yapmak istediginizi seciniz\n\n1)Urun Stok Ekleme\n2)Urun Stok Guncelleme\n3)Urun Stok Silme\n4)Urun Stok Arama\n"
#define DEVAM "Devam etmek icin tiklayiniz."
#define bilgiGirisMetni "Lutfen sistemin sizden istedigi bilgileri sirasiyla giriniz.\n"
#define guncellemeMetni "\nListelenen hangi secenegi guncellemek istiyorsunuz? (Lutfen kayit numarasini giriniz)\n\n"
#define silmeMetni "\nListelenen silmek istediginiz urun ismini giriniz: \n\n"
#define aramaMetni "Lutfen aradiginiz urunu giriniz: "
#define MAX 256

int urunVeriSecenegi, tedarikciVeriSecenegi, urunStokVeriSecenegi;
FILE *urunVeriGirisiDosyasi, *tedarikciVeriGirisiDosyasi, *urunStokVeriGirisiDosyasi;

enum genelSistemselSecenek{
    urunVerileri = 1, tedarikciVerileri, urunStokVerileri, cikis
}secenek;

enum urunIslemleri{
    urunEkleme = 1, urunGuncelleme, urunSilme, urunArama
}urunSecenegi;

enum tedarikciIslemleri{
    tedarikciEkleme = 1, tedarikciGuncelleme, tedarikciSilme, tedarikciArama
}tedarikciSecenegi;

enum urunStokIslemleri{
    urunStokEkleme = 1, urunStokGuncelleme, urunStokSilme, urunStokArama
}urunStokSecenegi;

typedef struct{
    const char kategori[MAX];          //Sabit
    int urunKodu;
    char urunAdi[MAX];
    float urunSatisFiyati;
    int stokMiktari;
} urun;

typedef struct{
    int tedarikciNo;
    char tedarikciAdi[MAX];
    char adres[MAX];
    const char sehir[MAX];         //Sabit
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
void urunBilgiGirisi(FILE *urunVeriGirisiDosyasi);
void urunBilgiGuncelleme(FILE *urunVeriGirisiDosyasi);
void urunBilgileri (int girdi);
void urunBilgiSilme(FILE *urunVeriGirisiDosyasi);
void urunBilgiArama(FILE *urunVeriGirisiDosyasi);
void tedarikciBilgileri(int tedarikciGirdi);
void tedarikciBilgiGirisi(FILE *tedarikciVeriGirisiDosyasi);
void tedarikciBilgiGuncelleme(FILE *tedarikciVeriGirisiDosyasi);
void tedarikciBilgiSilme(FILE *urunVeriGirisiDosyasi);
void tedarikciBilgiArama(FILE *urunVeriGirisiDosyasi);
void urunStokBilgileri(int urunStokGirdi);
void urunStokBilgiGirisi(FILE *urunStokVeriGirisiDosyasi);
void urunStokBilgiGuncelleme(FILE *urunStokVeriGirisiDosyasi);
void urunStokBilgiSilme(FILE *urunVeriGirisiDosyasi);
void urunStokBilgiArama(FILE *urunVeriGirisiDosyasi);
void dosyaIcerikKontrolu(FILE *girisDosyasi);
void dosyaVarligi(FILE *urunVeriGirisiDosyasi);

int main(){
    int baslangicSecenegi;
    printf("%s\n\n", baslangicMetni);
    scanf("%d", &baslangicSecenegi);
    sistemSecenegi(baslangicSecenegi);
    return 0;
}

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
        case cikis:
            printf("\nSistemden basariyla cikis yapildi.");
            exit(1);
            break;
        default:
            printf("Lutfen gecerli degisken giriniz.");
            break;
    }
}

///////////////////////ÜRÜN İLE İLGİLİ FONKSİYONLAR
void urunBilgileri (int urunGirdi){
    switch (urunGirdi){
        case urunEkleme:
            printf("\n%s\n", bilgiGirisMetni);
            urunBilgiGirisi(urunVeriGirisiDosyasi);
            break;
        case urunGuncelleme:
            urunBilgiGuncelleme(urunVeriGirisiDosyasi);
            break;
        case urunSilme:
            printf("%s", silmeMetni);
            urunBilgiSilme(urunVeriGirisiDosyasi);
            break;
        case urunArama:
            printf("%s", aramaMetni);
            urunBilgiArama(urunVeriGirisiDosyasi);
            break;
        default:
            printf("Lutfen gecerli degisken giriniz.");
            break;
    }
}

void urunBilgiGirisi(FILE *urunVeriGirisiDosyasi){
    char urunAdi[MAX], kategori[MAX];
    int urunKodu, miktar;
    float urunSatisFiyati;
    urunVeriGirisiDosyasi = fopen("urunVeriGirisiDosyasi.txt", "a+");
    dosyaVarligi(urunVeriGirisiDosyasi);

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
        scanf("%f", &urunSatisFiyati);
        fprintf(urunVeriGirisiDosyasi, "%s %s %d %d %f\n", urunAdi, kategori, urunKodu, miktar, urunSatisFiyati);
    }
    fclose(urunVeriGirisiDosyasi);
}

void urunBilgiArama(FILE *urunVeriGirisiDosyasi){
    char urunAdi[MAX], kategori[MAX], arananUrun[MAX], karakterSayaci;
    int urunKodu, miktar, siraSayisi;
    float urunSatisFiyati;

    scanf("%s", arananUrun);

    urunVeriGirisiDosyasi = fopen("urunVeriGirisiDosyasi.txt", "r");

    dosyaVarligi(urunVeriGirisiDosyasi);

    while((karakterSayaci = fgetc(urunVeriGirisiDosyasi)) != EOF){
        if (karakterSayaci == '\n'){
            siraSayisi++;
        }
    }
    dosyaIcerikKontrolu(urunVeriGirisiDosyasi);

    for(int i = 0; i < siraSayisi; i++){
        fscanf(urunVeriGirisiDosyasi, "%s %s %d %d %f", urunAdi, kategori, &urunKodu, &miktar, &urunSatisFiyati);

        if (strcmp(arananUrun, urunAdi) == 0){
            printf("Aranan urun bulundu.\n\n");
            printf("%d. Kayit\n", i+1);
            printf("---------\n");
            printf("Urun adi: %s\n", urunAdi);
            printf("Kategori: %s\n", kategori);
            printf("Urun Kodu: %d\n", urunKodu);
            printf("Miktar: %d\n", miktar);
            printf("Urun Satis Fiyati: %f\n\n", urunSatisFiyati);
            break;
        }
    }
    if (strcmp(arananUrun, urunAdi) == 1){
        puts("Aranan urun bulunamadi.");
        exit(EXIT_SUCCESS);
    }
}

void urunBilgiSilme(FILE *urunVeriGirisiDosyasi){
    FILE *urunGeciciDosyasi;
    char urunAdi[MAX], kategori[MAX], degisecekKelime[MAX], yeniKelime[MAX], okunanKelime[MAX];
    int urunKodu, miktar, siraSayisi = 0, silinecekKayit = 0;
    float urunSatisFiyati;
    char karakterSayaci;
    char dosyalarArasiBaglanti[MAX];

    urunVeriGirisiDosyasi = fopen("urunVeriGirisiDosyasi.txt", "r");
    urunGeciciDosyasi = fopen("urunGeciciDosyasisi.txt", "w");

    dosyaVarligi(urunVeriGirisiDosyasi);

    while((karakterSayaci = fgetc(urunVeriGirisiDosyasi)) != EOF){
        if (karakterSayaci == '\n'){
            siraSayisi++;
        }
    }
    dosyaIcerikKontrolu(urunVeriGirisiDosyasi);

    for(int i = 0; i < siraSayisi; i++){
        fscanf(urunVeriGirisiDosyasi, "%s %s %d %d %f", urunAdi, kategori, &urunKodu, &miktar, &urunSatisFiyati);

        printf("%d. Kayit\n", i+1);
        printf("---------\n");
        printf("Urun adi: %s\n", urunAdi);
        printf("Kategori: %s\n", kategori);
        printf("Urun Kodu: %d\n", urunKodu);
        printf("Miktar: %d\n", miktar);
        printf("Urun Satis Fiyati: %f\n\n", urunSatisFiyati);
    }

    puts("Kayitlar siralanmistir.\nSilmek istediginiz kayit numarasini yaziniz.\n");
    scanf("%d", &silinecekKayit);

    bool devamEt = true;
    int anlikSira = 1;
    do
    {
        fgets(dosyalarArasiBaglanti, MAX, urunVeriGirisiDosyasi);
        if(feof(urunVeriGirisiDosyasi))
            devamEt == false;
        else if (anlikSira != silinecekKayit)
            fputs(dosyalarArasiBaglanti, urunGeciciDosyasi);
        anlikSira++;

    } while (devamEt);
    
    fclose(urunVeriGirisiDosyasi);
    fclose(urunGeciciDosyasi);

    remove("urunVeriGirisiDosyasi.txt");
    rename("urunGeciciDosyasi.txt", "urunVeriGirisiDosyasi.txt");
}

void urunBilgiGuncelleme(FILE *urunVeriGirisiDosyasi){
    FILE *urunGeciciDosyasi;
    char urunAdi[MAX], kategori[MAX], degisecekKelime[MAX], yeniKelime[MAX], okunanKelime[MAX];
    int urunKodu, miktar, siraSayisi = 0;
    float urunSatisFiyati;
    char karakterSayaci;

    urunVeriGirisiDosyasi = fopen("urunVeriGirisiDosyasi.txt", "r");
    urunGeciciDosyasi = fopen("urunGeciciDosyasisi.txt", "w");

    dosyaVarligi(urunVeriGirisiDosyasi);

    while((karakterSayaci = fgetc(urunVeriGirisiDosyasi)) != EOF){
        if (karakterSayaci == '\n'){
            siraSayisi++;
        }
    }
    dosyaIcerikKontrolu(urunVeriGirisiDosyasi);

    for(int i = 0; i < siraSayisi; i++){
        fscanf(urunVeriGirisiDosyasi, "%s %s %d %d %f", urunAdi, kategori, &urunKodu, &miktar, &urunSatisFiyati);

        printf("%d. Kayit\n", i+1);
        printf("---------\n");
        printf("Urun adi: %s\n", urunAdi);
        printf("Kategori: %s\n", kategori);
        printf("Urun Kodu: %d\n", urunKodu);
        printf("Miktar: %d\n", miktar);
        printf("Urun Satis Fiyati: %f\n\n", urunSatisFiyati);
    }

    puts("Kayitlar siralanmistir.\nGuncellemek istediginiz veriyi yaziniz.\n");
    scanf("%s", degisecekKelime);
    degisecekKelime[strlen(degisecekKelime) - 1] = degisecekKelime[strlen(degisecekKelime)];

    puts("\nYerini alacak veriyi yaziniz:\n");
    scanf("%s", yeniKelime);
    yeniKelime[strlen(yeniKelime) - 1] = yeniKelime[strlen(yeniKelime)]; //yeni satırı siler

    rewind(urunVeriGirisiDosyasi);
    while(!feof(urunVeriGirisiDosyasi)){
        fscanf(urunVeriGirisiDosyasi, "%s", okunanKelime);

        if(strcmp(okunanKelime, degisecekKelime) == 0)
            strcpy(okunanKelime, yeniKelime);
        fprintf(urunGeciciDosyasi, "%s", okunanKelime);
    }

    fclose(urunVeriGirisiDosyasi);
    fclose(urunGeciciDosyasi);

    remove("urunVeriGirisiDosyasi.txt");
    rename("urunGeciciDosyasi.txt", "urunVeriGirisiDosyasi.txt");
}


///////////////////////TEDARİKÇİ İLE İLGİLİ FONKSİYONLAR
void tedarikciBilgileri(int tedarikciGirdi){
    switch(tedarikciGirdi){
        case tedarikciEkleme:
            printf("\n%s\n", bilgiGirisMetni);
            tedarikciBilgiGirisi(tedarikciVeriGirisiDosyasi);
            break;
        case tedarikciGuncelleme:
            printf("%s", guncellemeMetni);
            tedarikciBilgiGuncelleme(tedarikciVeriGirisiDosyasi);
            break;
        default:
            printf("Lutfen gecerli degisken giriniz.");
            break;
    }
}

void tedarikciBilgiGuncelleme(FILE *tedarikciVeriGirisiDosyasi){
    int tedarikciNo;
    char tedarikciAdi[MAX], adres[MAX], sehir[MAX];
    tedarikciVeriGirisiDosyasi = fopen("tedarikciVeriGirisiDosyasi.txt", "r");

    if(urunVeriGirisiDosyasi == NULL){
        printf("Dosya acilamadi.");
        exit(1);
    }

    for(int i = 0; i < 2; i++){
        fscanf(tedarikciVeriGirisiDosyasi, "%d %s %s %s", &tedarikciNo, tedarikciAdi, adres, sehir);
        
        printf("%d. Kayit\n", i+1);
        printf("---------\n");
        printf("Tedarikci No: %d\n", tedarikciNo);
        printf("Tedarikci Adi: %s\n", tedarikciAdi);
        printf("Adres: %s\n", adres);        
        printf("Sehir: %s\n\n", sehir);
    }
    fclose(tedarikciVeriGirisiDosyasi);
}

void tedarikciBilgiGirisi(FILE *tedarikciVeriGirisiDosyasi){
    int tedarikciNo;
    char tedarikciAdi[MAX], adres[MAX], sehir[MAX];
    tedarikciVeriGirisiDosyasi = fopen("tedarikciVeriGirisiDosyasi.txt", "a+");

    if(urunVeriGirisiDosyasi == NULL){
        printf("Dosya acilamadi.");
        exit(1);
    }

    for(int i = 0; i < 1; i++){
        printf("Tedarikci No: ");
        scanf("%d", &tedarikciNo);

        printf("Tedarikci Adi: ");
        scanf("%s", tedarikciAdi);
        
        printf("Adres: ");
        gets(adres);

        printf("Sehir: ");
        scanf("%s", sehir);

        fprintf(tedarikciVeriGirisiDosyasi, "%d %s %s %s\n", tedarikciNo, tedarikciAdi, adres, sehir);
    }
    fclose(tedarikciVeriGirisiDosyasi);
}

/////////////////////////////ÜRÜN STOK İLE İLGİLİ FONKSİYONLAR
void urunStokBilgileri(int urunStokGirdi){
    switch(urunStokGirdi){
        case urunStokEkleme:
            printf("\n%s\n", bilgiGirisMetni);
            urunStokBilgiGirisi(urunStokVeriGirisiDosyasi);
            break;
        case urunStokGuncelleme:
            printf("%s", guncellemeMetni);
            urunStokBilgiGuncelleme(urunStokVeriGirisiDosyasi);
            break;
        default:
            printf("Lutfen gecerli degisken giriniz.");
            break;
    }
}

void urunStokBilgiGirisi(FILE *urunStokVeriGirisiDosyasi){
    int tedarikciNo, urunKodu, alisMiktari, tarih;
    float alisFiyati;
    urunStokVeriGirisiDosyasi = fopen("urunStokVeriGirisiDosyasi.txt", "a+");

    if(urunVeriGirisiDosyasi == NULL){
        printf("Dosya acilamadi.");
        exit(1);
    }
    
    for(int i = 0; i < 1; i++){
        printf("Tedarikci No: ");
        scanf("%d", &girilenUrunStokBilgileri.tedarikciNo);

        printf("Urun Kodu: ");
        scanf("%d", &girilenUrunStokBilgileri.urunKodu);
        
        printf("Alis Miktari: ");
        scanf("%d", &girilenUrunStokBilgileri.alisMiktari);

        printf("Alis Fiyati: ");
        scanf("%f", &girilenUrunStokBilgileri.alisFiyati);

        printf("Tarih: ");
        scanf("%d", &girilenUrunStokBilgileri.tarih);

        fprintf(urunStokVeriGirisiDosyasi, "%d %d %d %.2f %d\n", tedarikciNo, urunKodu, alisMiktari, alisFiyati, tarih);
    }
    fclose(urunStokVeriGirisiDosyasi);
}

void urunStokBilgiGuncelleme(FILE *urunStokVeriGirisiDosyasi){
    int tedarikciNo, urunKodu, alisMiktari, tarih, alisFiyati;
    urunStokVeriGirisiDosyasi = fopen("urunStokVeriGirisiDosyasi.txt", "r");

    if(urunStokVeriGirisiDosyasi == NULL){
        perror("Dosya bulunamadi.");
        exit(1);
    }

    for(int i = 0; i < 2; i++){
        fscanf(urunStokVeriGirisiDosyasi, "%d %d %d %.2f %d", &tedarikciNo, &urunKodu, &alisMiktari, &alisFiyati, &tarih);
        
        printf("%d. Kayit\n", i+1);
        printf("---------\n");
        printf("Tedarikci No: %d\n", tedarikciNo);
        printf("Urun Kodu: %d\n", urunKodu);
        printf("Alis Miktari: %d\n", alisMiktari);
        printf("Alis Fiyati: %.2f\n", alisFiyati);
        printf("Tarih: %d\n\n", tarih);
    }
    fclose(urunStokVeriGirisiDosyasi);
}

void dosyaIcerikKontrolu(FILE *girisDosyasi){
    int urunVeriBoyutu = 0;
    if(girisDosyasi != NULL){
        fseek(girisDosyasi, 0, SEEK_END);
        urunVeriBoyutu = ftell(girisDosyasi);
        rewind(girisDosyasi);
    }
    
    if(urunVeriBoyutu == 0){
        printf("Sistemde kayitli veri bulunmamaktadir.");
        exit(0);
    }
}

void dosyaVarligi(FILE *urunVeriGirisiDosyasi){
    if(urunVeriGirisiDosyasi == NULL){
        printf("Dosya bulunamadi.");
        exit(EXIT_SUCCESS);
    }
}
