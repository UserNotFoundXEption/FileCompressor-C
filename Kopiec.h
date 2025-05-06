#ifndef PODZIA_NA_PLIKI_KOPIEC_H
#define PODZIA_NA_PLIKI_KOPIEC_H

#include "Drzewo.h"

void dodaj_do_kopca(drzewo **kopiec, int *index, drzewo element_dodawany);

drzewo sciagnij_z_kopca(drzewo **kopiec, int *index);

void wypisz_kopiec(drzewo *kopiec, int index);

void stworz_kopiec(drzewo *kolejka, drzewo **kopiec, int *index, int dlugosc_kolejki);

#endif //PODZIA_NA_PLIKI_KOPIEC_H
