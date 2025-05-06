#ifndef PODZIA_NA_PLIKI_KLUCZ_H
#define PODZIA_NA_PLIKI_KLUCZ_H

#include "Drzewo.h"


void zapisz(drzewo huffman, int **tablica_znakow, int *index, int *dlugosc);

void zapisz_klucz(drzewo huffman, FILE *klucz, int reszta);

void odkoduj_klucz_tablica(FILE *in, int **tab, int *index, int *dlugosc);

drzewo odkoduj(int *tab, int *obecny_index, int wielkosc);

drzewo odkoduj_klucz(FILE *in, int *reszta);


#endif //PODZIA_NA_PLIKI_KLUCZ_H
