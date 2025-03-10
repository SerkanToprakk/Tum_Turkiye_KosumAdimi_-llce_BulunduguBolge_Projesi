#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IL_SAYISI 81
#define MAX_IL_ADI_UZUNLUGU 50
#define MAX_BOLGE_ADI_UZUNLUGU 30
#define MAX_SATIR_UZUNLUGU 150

typedef struct {
    int trafik_kodu;
    char il_adi[MAX_IL_ADI_UZUNLUGU];
    char bolge_adi[MAX_BOLGE_ADI_UZUNLUGU];
} Il;


void parse_csv_line(char *line, int *kod, char *il, char *bolge) {
    char *token;
    
    
    token = strtok(line, ",");
    if (token != NULL) {
        *kod = atoi(token);
    }
    
    
    token = strtok(NULL, ",");
    if (token != NULL) {
        strcpy(il, token);
    }
    
    
    token = strtok(NULL, ",\n");
    if (token != NULL) {
        strcpy(bolge, token);
    }
}

int main() {
    FILE *dosya;
    Il iller[MAX_IL_SAYISI];
    int il_sayisi = 0;
    int girilen_kod;
    int i, bulundu = 0;
    char dosya_adi[] = "turkiye_trafik_kodlari.csv";
    char satir[MAX_SATIR_UZUNLUGU];
    
    
    dosya = fopen(dosya_adi, "r");
    if (dosya == NULL) {
        printf("Dosya açılamadı: %s\n", dosya_adi);
        return 1;
    }
    
    
    if (fgets(satir, MAX_SATIR_UZUNLUGU, dosya) == NULL) {
        printf("Dosya boş veya başlık satırı okunamadı\n");
        fclose(dosya);
        return 1;
    }
    

    while (fgets(satir, MAX_SATIR_UZUNLUGU, dosya) != NULL && il_sayisi < MAX_IL_SAYISI) {
        parse_csv_line(satir, &iller[il_sayisi].trafik_kodu, 
                      iller[il_sayisi].il_adi, 
                      iller[il_sayisi].bolge_adi);
        il_sayisi++;
    }
    
    
    fclose(dosya);
    
    
    printf("Trafik kodunu giriniz : ");
    scanf("%d", &girilen_kod);
    
    
    if (girilen_kod < 1 || girilen_kod > 81) {
        printf("Hatalı Kod Girdiniz\n");
        return 1;
    }
    
    
    for (i = 0; i < il_sayisi; i++) {
        if (iller[i].trafik_kodu == girilen_kod) {
            printf("%s\n%s bölgesinde yer alır\n", 
                   iller[i].il_adi, 
                   iller[i].bolge_adi);
            bulundu = 1;
            break;
        }
    }
    
    
    if (!bulundu) {
        printf("Hatalı Kod Girdiniz\n");
    }
    
    return 0;
}
