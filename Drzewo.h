#ifndef PODZIA_NA_PLIKI_DRZEWO_H
#define PODZIA_NA_PLIKI_DRZEWO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elem {
    int symbol, piorytet;
    struct elem *l_syn;
    struct elem *p_syn;
} elem, *drzewo;

drzewo stworz_drzewo(int symbol, int piorytet, drzewo lewy, drzewo prawy);

void wyczysc_drzewo(drzewo t);

void wypisz_pre_ord_drzewo(drzewo drzewo_do_wypisania);

int zwroc_ilosc_elementow_drzewa(drzewo h);

void zaminen_na_zapis_binarny(int **tab, int *index, int symbol);

int zamien_na_zapis_dziesiety(int tab[], int i);

#endif //PODZIA_NA_PLIKI_DRZEWO_H
