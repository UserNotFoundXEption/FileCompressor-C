#ifndef PODZIA_NA_PLIKI_KOMPRESJA_H
#define PODZIA_NA_PLIKI_KOMPRESJA_H

#include "Kopiec.h"

void zlicz_znaki(long int (*wszystkie_znaki)[256], FILE *in);

drzewo stworz_drzewo_huffmana(drzewo **kopiec, int *index);

#endif //PODZIA_NA_PLIKI_KOMPRESJA_H
