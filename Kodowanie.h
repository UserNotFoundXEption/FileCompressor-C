
#ifndef PODZIA_NA_PLIKI_KODOWANIE_H
#define PODZIA_NA_PLIKI_KODOWANIE_H

#include "Drzewo.h"

void
wygeneruj_kody(drzewo t, int *tablica_na_kody, int index_tablicy_na_kody, int **tablica_znakow, int ***tablica_kodow,
               int *index, int **tablica_dlugosc);

int zakoduj_plik(drzewo huffman, FILE *in, FILE *out, int liczba_znakow);

void odkoduj_plik(drzewo huffman, FILE *in, FILE *out, int liczba_znakow, int reszta);

#endif //PODZIA_NA_PLIKI_KODOWANIE_H
