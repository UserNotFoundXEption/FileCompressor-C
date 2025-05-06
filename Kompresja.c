#include "Kompresja.h"

void zlicz_znaki(long int (*wszystkie_znaki)[256], FILE *in) {
    for (int i = 0; i < 256; i++) (*wszystkie_znaki)[i] = 0;
    int c;
    while ((c = fgetc(in))!=EOF) {
        (*wszystkie_znaki)[c]++;
    }
}

drzewo stworz_drzewo_huffmana(drzewo **kopiec, int *index) {
    while (*index != 2) {
        drzewo element_pierwszy = sciagnij_z_kopca(kopiec, index);
        drzewo element_drugi = sciagnij_z_kopca(kopiec, index);
        drzewo element_nowy =
                stworz_drzewo(-1, element_pierwszy->piorytet + element_drugi->piorytet,
                              element_pierwszy, element_drugi);
        dodaj_do_kopca(kopiec, index, element_nowy);
    }
    return sciagnij_z_kopca(kopiec, index);
}