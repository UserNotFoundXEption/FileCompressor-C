#include "Kolejka.h"


int stworz_kolejke(long int wszystkie_znaki[256], drzewo **kolejka) {
    int dlugosc_kolejki = 10, zajete_elementy_kolejki = 0;

    if ((*kolejka = malloc(sizeof(**kolejka) * dlugosc_kolejki)) == NULL) {
        printf("stworz_kolejke BLAD_1");
        exit(35);
    }

    for (int i = 0; i < 256; i++) {
        if (wszystkie_znaki[i] > 0) {
            (*kolejka)[zajete_elementy_kolejki++] =
                    stworz_drzewo(i, wszystkie_znaki[i], NULL, NULL);
            if (zajete_elementy_kolejki == dlugosc_kolejki) {
                dlugosc_kolejki *= 2;
                if ((*kolejka = realloc(*kolejka,
                                        sizeof(**kolejka) * dlugosc_kolejki)) == NULL) {
                    printf("stworz_kolejke BLAD_2");
                    exit(36);
                }
            }
        }
    }
    if (dlugosc_kolejki != zajete_elementy_kolejki && zajete_elementy_kolejki != 0) {
        if ((*kolejka = realloc(
                *kolejka, sizeof(**kolejka) * zajete_elementy_kolejki)) == NULL) {
            printf("stworz_kolejke BLAD_3");
            exit(37);
        }
    }
    if(zajete_elementy_kolejki == 0) free(*kolejka);
    return zajete_elementy_kolejki;
}
