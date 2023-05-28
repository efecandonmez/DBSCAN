#include <stdio.h>
#include <math.h>
#define MAX_NOKTA_SAYISI 100

typedef struct {
    double x;
    double y;
} Nokta;

typedef struct {
    int etiket;
    int ziyaret_edildi;
} NoktaBilgi;

double mesafe(Nokta nokta1, Nokta nokta2) {
    return sqrt(pow(nokta2.x - nokta1.x, 2) + pow(nokta2.y - nokta1.y, 2));
}

int minPtsIcindedir(Nokta nokta, Nokta noktalar[], int nokta_sayisi, double epsilon) {
    int i, sayac = 0;
    for (i=0; i<nokta_sayisi; i++) {
        if (mesafe(nokta, noktalar[i])<=epsilon) {
            sayac++;
        }
    }
    return (sayac>=nokta_sayisi)?1:0;
}

void dbscan(Nokta noktalar[], int nokta_sayisi, double epsilon, int minPts) {
    NoktaBilgi nokta_bilgileri[MAX_NOKTA_SAYISI];
    int i, j, etiket=0;

    for (i=0; i<nokta_sayisi; i++) {
        nokta_bilgileri[i].etiket=0;
        nokta_bilgileri[i].ziyaret_edildi=0;
    }

    for (i=0; i<nokta_sayisi; i++) {
        if (nokta_bilgileri[i].ziyaret_edildi==1) {
            continue;
        }
        nokta_bilgileri[i].ziyaret_edildi = 1;

        if (minPtsIcindedir(noktalar[i], noktalar, nokta_sayisi, epsilon)==0) {
            nokta_bilgileri[i].etiket=-1;  			// gürültü noktası
        } else {
            etiket++;
            nokta_bilgileri[i].etiket=etiket;

            // çekirdek noktalarının komşularını bulmak icin for döngüsü
            for (j=0; j<nokta_sayisi; j++) {
                if (mesafe(noktalar[i], noktalar[j])<=epsilon) {
                    nokta_bilgileri[j].ziyaret_edildi=1;
                    if (nokta_bilgileri[j].etiket==0) {
                        nokta_bilgileri[j].etiket=etiket;
                    }
                }
            }
        }
    }

    printf("Kumeleme Sonuclari:\n");
    for (i=0; i<nokta_sayisi; i++) {
        if (nokta_bilgileri[i].etiket==-1) {
            printf("Nokta %d: Gurultu noktasi\n", i+1);
        } else {
            printf("Nokta %d: Kume %d\n", i+1, nokta_bilgileri[i].etiket);
        }
    }
}

int main() {
    Nokta noktalar[MAX_NOKTA_SAYISI];
    int nokta_sayisi, i;
    double epsilon;
    int minPts;

    printf("Nokta sayisini girin: ");
    scanf("%d", &nokta_sayisi);

    printf("Noktalarin koordinatlarini girin:\n");
    for (i=0; i<nokta_sayisi; i++) {
        printf("Nokta %d: x = ", i+1);
        scanf("%lf", &noktalar[i].x);
        printf("Nokta %d: y = ", i+1);
        scanf("%lf", &noktalar[i].y);
    }

    printf("Epsilon degerini girin: ");
    scanf("%lf", &epsilon);

    printf("MinPts degerini girin: ");
    scanf("%d", &minPts);

    dbscan(noktalar, nokta_sayisi, epsilon, minPts);

    return 0;
}
