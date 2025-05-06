#include "Klucz.h"


void zapisz(drzewo huffman, int **tablica_bitow, int *index, int *dlugosc_bity) {
    if ((*index) + 8 >= *dlugosc_bity) {
        (*dlugosc_bity) *= 2;
        if (((*tablica_bitow) = realloc(*tablica_bitow,
                                        (sizeof(**tablica_bitow)) * (*dlugosc_bity))) == NULL) {
            printf("zapisz BLAD_1\n");
            exit(11);
        }
    }
    if (huffman != NULL) {
        if (huffman->symbol == -1) {
            (*tablica_bitow)[(*index)++] = 0;
        } else {
            (*tablica_bitow)[(*index)++] = 1;
            zaminen_na_zapis_binarny(tablica_bitow, index, huffman->symbol);
        }
        zapisz(huffman->l_syn, tablica_bitow, index, dlugosc_bity);
        zapisz(huffman->p_syn, tablica_bitow, index, dlugosc_bity);
    }
}

void zapisz_klucz(drzewo huffman, FILE *klucz, int reszta) {
    int *tablica_bitow, dlugosc_bity = 20, index = 0;
    if ((tablica_bitow = malloc(sizeof(*tablica_bitow) * dlugosc_bity)) == NULL) {
        printf("zapisz_klucz BLAD_1\n");
        exit(12);
    }
    if (huffman->p_syn == NULL && huffman->l_syn == NULL) {
        tablica_bitow[0] = 1;
        index = 1;
        zaminen_na_zapis_binarny(&tablica_bitow, &index, huffman->symbol);
    } else
        zapisz(huffman, &tablica_bitow, &index, &dlugosc_bity);

    int reszta_klucza = 8 - index % 8;
    if (reszta_klucza) {
        if (index + reszta_klucza > dlugosc_bity)
            if ((tablica_bitow = realloc(tablica_bitow, sizeof(*tablica_bitow) *
                                                        (index + reszta_klucza))) == NULL) {
                printf("zapisz_klucz BLAD_2\n");
                exit(13);
            }
        for (int i = 0; i < reszta_klucza; i++) tablica_bitow[index + i] = 0;
    }

    int dlugosc_znaki = (index + reszta_klucza) / 8;
    for (int i = 0; i < dlugosc_znaki; i++) {
        fputc(zamien_na_zapis_dziesiety(tablica_bitow, i * 8), klucz);
    }
    fputc(reszta_klucza + 48, klucz);
    fputc(reszta + 48, klucz);
    free(tablica_bitow);
}

void odkoduj_klucz_tablica(FILE *in, int **tab, int *index, int *dlugosc) {
    int c;
    while ((c = fgetc(in)) != EOF) {
        if ((*index) + 8 >= (*dlugosc)) {
            (*dlugosc) *= 2;
            if (((*tab) = realloc(*tab, sizeof(**tab) * (*dlugosc))) == NULL) {
                printf("odkoduj_klucz_tablica BLAD_1\n");
                exit(14);
            }
        }
        zaminen_na_zapis_binarny(tab, index, c);
    }
}

drzewo odkoduj(int *tab, int *obecny_index, int wielkosc) {
    if (*obecny_index < wielkosc) {
        if (tab[*obecny_index] == 0) {
            drzewo zwracane = stworz_drzewo(-1, 0, NULL, NULL);
            (*obecny_index)++;
            zwracane->l_syn = odkoduj(tab, obecny_index, wielkosc);
            zwracane->p_syn = odkoduj(tab, obecny_index, wielkosc);
            return zwracane;
        } else if (tab[*obecny_index] == 1) {
            (*obecny_index)++;
            int symbol = zamien_na_zapis_dziesiety(tab, *obecny_index);
            (*obecny_index) += 8;
            drzewo zwracane = stworz_drzewo(symbol, 1, NULL, NULL);
            return zwracane;
        } else {
            printf("odkoduj BLAD_1\n");
            exit(15);
        }
    }
    return NULL;
}

drzewo odkoduj_klucz(FILE *in, int *reszta) {
    int *tab_bitow, index = 0, dlugosc = 20;
    if ((tab_bitow = malloc((sizeof(*tab_bitow) * dlugosc))) == NULL) {
        printf("odkoduj_klucz BLAD_1\n");
        exit(16);
    }
    odkoduj_klucz_tablica(in, &tab_bitow, &index, &dlugosc);

    (*reszta) = zamien_na_zapis_dziesiety(tab_bitow, index - 8) - 48;
    int reszta_klucz = zamien_na_zapis_dziesiety(tab_bitow, index - 16) - 48;

    if ((*reszta) < 0 || reszta_klucz < 0 || (*reszta) > 8 || reszta_klucz > 8) {
        printf("odkoduj_klucz BLAD_2\n");
        free(tab_bitow);
        fclose(in); 
        exit(17);
    }

    int wielkosc = index - 16 - reszta_klucz;
    if (wielkosc < 1) {
        printf("odkoduj_klucz BLAD_3\n");
        exit(18);
    } else if (wielkosc == 9) { //jeden symbol
        if (tab_bitow[0] == 1) {
            int symbol = zamien_na_zapis_dziesiety(tab_bitow, 1);
            drzewo h = stworz_drzewo(symbol, 1, NULL, NULL);
            free(tab_bitow);
            return h;
        } else {
            printf("odkoduj_klucz BLAD_4\n");
            exit(19);
        }
    } else if (tab_bitow[0] == 0) {
        int obecny_index = 1;
        drzewo h = stworz_drzewo(-1, 0, NULL, NULL);
        h->l_syn = odkoduj(tab_bitow, &obecny_index, wielkosc);
        h->p_syn = odkoduj(tab_bitow, &obecny_index, wielkosc);
        free(tab_bitow);
        return h;
    } else {
        printf("odkoduj_klucz BLAD_5\n");
        exit(20);
    }
}
