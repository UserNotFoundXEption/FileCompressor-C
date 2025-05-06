#include "Kodowanie.h"

void
wygeneruj_kody(drzewo t, int *tablica_na_kody, int index_tablicy_na_kody, int **tablica_znakow, int ***tablica_kodow,
               int *index, int **tablica_dlugosc) {
    if (t != NULL) {
        if (t->symbol == -1) {
            tablica_na_kody[index_tablicy_na_kody] = 1;
            wygeneruj_kody(t->p_syn, tablica_na_kody, index_tablicy_na_kody + 1, tablica_znakow, tablica_kodow, index,
                           tablica_dlugosc);
            tablica_na_kody[index_tablicy_na_kody] = 0;
            wygeneruj_kody(t->l_syn, tablica_na_kody, index_tablicy_na_kody + 1, tablica_znakow, tablica_kodow, index,
                           tablica_dlugosc);
        } else {
            if (index_tablicy_na_kody == 0) {
                (*tablica_znakow)[*index] = t->symbol;
                tablica_na_kody[index_tablicy_na_kody] = 1;
                (*tablica_dlugosc)[*index] = 1;
                index_tablicy_na_kody++;
                if (((*tablica_kodow)[*index] = malloc(sizeof(*((*tablica_kodow)[*index])) * index_tablicy_na_kody)) ==
                    NULL) {
                    printf("wygeneruj_kody BLAD_1\n");
                    exit(21);
                }
                for (int i = 0; i < index_tablicy_na_kody; i++)
                    (*tablica_kodow)[*index][i] = tablica_na_kody[i];
                (*index)++;
            } else {
                (*tablica_znakow)[*index] = t->symbol;
                (*tablica_dlugosc)[*index] = index_tablicy_na_kody;
                if (((*tablica_kodow)[*index] = malloc(sizeof(*((*tablica_kodow)[*index])) * index_tablicy_na_kody)) ==
                    NULL) {
                    printf("wygeneruj_kody BLAD_2\n");
                    exit(22);
                }
                for (int i = 0; i < index_tablicy_na_kody; i++)
                    (*tablica_kodow)[*index][i] = tablica_na_kody[i];
                (*index)++;
            }
        }
    }
}

int zakoduj_plik(drzewo huffman, FILE *in, FILE *out, int liczba_znakow) {
    int *tablica_znakow, *tablica_na_kod, *tablica_dlugosc, *tablica_bitow, **tablica_kodow;

    if ((tablica_kodow = malloc(sizeof(*tablica_kodow) * liczba_znakow)) == NULL) {
        printf("zakoduj_plik BLAD_1\n");
        exit(23);
    }
    if ((tablica_znakow = malloc(sizeof(*tablica_znakow) * liczba_znakow)) == NULL) {
        printf("zakoduj_plik BLAD_2\n");
        exit(24);
    }
    if ((tablica_na_kod = malloc(sizeof(*tablica_na_kod) * liczba_znakow)) == NULL) {
        printf("zakoduj_plik BLAD_3\n");
        exit(25);
    }
    if ((tablica_dlugosc = malloc(sizeof(*tablica_dlugosc) * liczba_znakow)) == NULL) {
        printf("zakoduj_plik BLAD_4\n");
        exit(26);
    }
    if ((tablica_bitow = malloc(800 * sizeof(int))) == NULL) {
        printf("zakoduj_plik BLAD_5\n");
        exit(27);
    }

    int index = 0;
    wygeneruj_kody(huffman, tablica_na_kod, 0, &tablica_znakow, &tablica_kodow, &index, &tablica_dlugosc);

    int c, liczba_bitow = 0, max_bitow = 800;
    while ((c = fgetc(in)) != EOF) {
        int i = 0;
        while (tablica_znakow[i] != c)
            i++;
        for (int j = 0; j < tablica_dlugosc[i]; j++) {
            tablica_bitow[liczba_bitow] = tablica_kodow[i][j];
            liczba_bitow++;
        }
        if (liczba_bitow > max_bitow - 20) {
            max_bitow *= 2;
            if ((tablica_bitow = realloc(tablica_bitow, max_bitow * sizeof(*tablica_bitow))) == NULL) {
                printf("zakoduj_plik BLAD_6\n");
                exit(28);
            }
        }
    }

    int reszta = 8 - (liczba_bitow % 8);
    for (int i = 0; i < reszta; i++)
        tablica_bitow[liczba_bitow + i] = 0;
    liczba_bitow += reszta;

    int liczba_znakow2 = liczba_bitow / 8;

    for (int i = 0; i < liczba_znakow2; i++) {
        int symbol = zamien_na_zapis_dziesiety(tablica_bitow, i * 8);
        fputc(symbol, out);
    }

    for (int i = 0; i < liczba_znakow; i++) free(tablica_kodow[i]);
    free(tablica_kodow);
    free(tablica_znakow);
    free(tablica_na_kod);
    free(tablica_dlugosc);
    free(tablica_bitow);
    return reszta;
}

void odkoduj_plik(drzewo huffman, FILE *in, FILE *out, int liczba_znakow, int reszta) {
    int *tablica_znakow, *tablica_na_kod, *tablica_dlugosc, *tablica_bitow, **tablica_kodow;

    if ((tablica_kodow = malloc(sizeof(*tablica_kodow) * liczba_znakow)) == NULL) {
        printf("odkoduj_plik BLAD_1\n");
        exit(29);
    }
    if ((tablica_znakow = malloc(sizeof(*tablica_znakow) * liczba_znakow)) == NULL) {
        printf("odkoduj_plik BLAD_2\n");
        exit(30);
    }
    if ((tablica_na_kod = malloc(sizeof(*tablica_na_kod) * liczba_znakow)) == NULL) {
        printf("odkoduj_plik BLAD_3\n");
        exit(31);
    }
    if ((tablica_dlugosc = malloc(sizeof(*tablica_dlugosc) * liczba_znakow)) == NULL) {
        printf("odkoduj_plik BLAD_4\n");
        exit(32);
    }
    if ((tablica_bitow = malloc(800 * sizeof(int))) == NULL) {
        printf("odkoduj_plik BLAD_5\n");
        exit(33);
    }
    int index = 0, liczba_znakow2 = 0, c, max_bitow = 800;
    wygeneruj_kody(huffman, tablica_na_kod, 0, &tablica_znakow, &tablica_kodow, &index, &tablica_dlugosc);

    int index_tablicy_bitow = 0;
    while ((c = fgetc(in)) != EOF) {
        liczba_znakow2++;
        zaminen_na_zapis_binarny(&tablica_bitow, &index_tablicy_bitow, c);
        if (index_tablicy_bitow > max_bitow - 20) {
            max_bitow *= 2;
            if ((tablica_bitow = realloc(tablica_bitow, sizeof(*tablica_bitow) * max_bitow)) == NULL) {
                printf("odkoduj_plik BLAD_6\n");
                exit(34);
            }
        }
    }

    drzewo p = huffman;
    for (int i = 0; i < index_tablicy_bitow - reszta; i++) {
        if (p->symbol == -1) {
            if (tablica_bitow[i] == 0) p = p->l_syn;
            else p = p->p_syn;
        }
        if (p->symbol != -1) {
            fputc(p->symbol, out);
            p = huffman;
        }
    }

    for (int i = 0; i < liczba_znakow; i++) free(tablica_kodow[i]);
    free(tablica_dlugosc);
    free(tablica_bitow);
    free(tablica_znakow);
    free(tablica_kodow);
    free(tablica_na_kod);
}
