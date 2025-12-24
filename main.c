#include <stdio.h>
#include<string.h>
int tc_rakamlari[11];
//Bursiyer bilgilerini tutan yapı
struct BURSIYER_BILGILERI {
    char ad_soyad[100];
    char tc_no[12];
};
//TC kimlik numaralarını kontrol eden fonksiyon
int tc_kontrol(char tc_no[]) {
    int ilkOntoplam =0, tekSayiToplam=0, ciftSayiToplam=0;
    //TC no 11 basamaklı mı?
    if (strlen(tc_no)!=11) return 0;
    //TC no rakamlardan mı oluşuyor?
    for (int i = 0; i < 11; i++) {
        if (tc_no[i] < '0' || tc_no[i] > '9') return 0;
        tc_rakamlari[i] = tc_no[i] - '0';
    }
    //TC numarasının ilk hanesi 0'a eşit mi?
    if (tc_rakamlari[0]==0) return 0;
    //TC numarasının ilk 10 basamak toplamının birler basamağı 11. Basamağa eşit mi?
    for (int i=0;i<10;i++) {
        ilkOntoplam+=tc_rakamlari[i];
    }
    if (tc_rakamlari[10]!=ilkOntoplam%10) return 0;
    //10. basamak kontrolü
    for (int i=0; i<9; i++) {
        if (i%2==0) {
            tekSayiToplam += tc_rakamlari[i];
        }
        else {
            ciftSayiToplam += tc_rakamlari[i];
        }
    }
    if (((tekSayiToplam*7) + (ciftSayiToplam*9)) %10 != tc_rakamlari[9]) {
        return 0;
    }
    //Tüm şartları sağlayan TC kimlik numaraları geçerli
    return 1 ;
}
int main() {
    struct BURSIYER_BILGILERI bursiyer;
    FILE *basvuru= fopen("basvuru.txt", "r");
    FILE *gecerli=  fopen("gecerli.txt", "w");
    //Dosyaların kontrolü
    if (basvuru == NULL || gecerli == NULL) {
        printf("Dosya acilamadi\n");
        return 1;
    }
    //Bursiyerlerin bilgilerinin kontrolü ve geçerli olanların dosyaya aktarılması
    while (fscanf (basvuru," %[^0-9] %s" , bursiyer.ad_soyad, &bursiyer.tc_no)!=EOF)
        if (tc_kontrol(bursiyer.tc_no)) {
            fprintf(gecerli, "%s %s\n", bursiyer.ad_soyad, bursiyer.tc_no);
        }
    fclose(gecerli);
    fclose(basvuru);
    printf("veriler gecerli.txt dosyasina basariyla yazildi.\n");
    return 0;
}
