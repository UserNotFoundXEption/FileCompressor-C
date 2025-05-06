#include "Kolejka.h"
#include "Kompresja.h"
#include "Kodowanie.h"
#include "Klucz.h"


int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Blad -1\n");
        return -1;
    }
    if (argc < 3) {
        printf("Blad -2\n");
        return -2;
    }
    if (argc < 4) {
        printf("Blad -3\n");
        return -3;
    }
    if (argc < 5) {
        printf("Blad -4\n");
        return -4;
    }
    if (argc > 5) {
        printf("Podano za duzo argumentow\n");
        return -4;
    }

    char opcja_char;
    if (strlen(argv[1]) != 2) {
        printf("Blad -1\n");
        return -1;
    }
    if (strcmp(argv[1], "-k") != 0 && strcmp(argv[1], "-d") != 0) {
        printf("Blad -1\n");
        return -1;
    }
    opcja_char = argv[1][1];

    if (opcja_char == 'k') {
        FILE *in = fopen(argv[2], "r");
        if (in == NULL) {
            printf("Blad -2\n");
            return -2;
        }
        FILE *out = fopen(argv[3], "w");
        if (out == NULL) {
            printf("Blad -3\n");
            return -3;
        }

        long int wszystkie_znaki[256];
        zlicz_znaki(&wszystkie_znaki, in);
        rewind(in);

        drzewo *kolejka, *kopiec;
        int dlugosc_kolejki = stworz_kolejke(wszystkie_znaki, &kolejka);
        if (dlugosc_kolejki == 0) {
            printf("Plik %s jest pusty\n", argv[1]);
            return -2;
        }
        if ((kopiec = malloc(sizeof(*kopiec) * (dlugosc_kolejki + 1))) == NULL) {
            printf("main BLAD_1\n");
            exit(9);
        }
        int index = 1;
        stworz_kopiec(kolejka, &kopiec, &index, dlugosc_kolejki);
        drzewo huffman = stworz_drzewo_huffmana(&kopiec, &index);

        int reszta = zakoduj_plik(huffman, in, out, dlugosc_kolejki);
        if (reszta == -1) {
            printf("EMPTY FILE\n");
            return -2;
        }

        fclose(in);
        fclose(out);

        FILE *klucz = fopen(argv[4], "w");
        if (klucz == NULL) {
            printf("Blad -4\n");
            return -4;
        }
        zapisz_klucz(huffman, klucz, reszta);
        fclose(klucz);

        wyczysc_drzewo(huffman);
        free(kolejka);
        free(kopiec);
    }

    if (opcja_char == 'd') {
        int reszta, dlugosc_kolejki;
        FILE *klucz = fopen(argv[4], "r");
        if (klucz == NULL) {
            printf("Blad -4\n");
            return -4;
        }
        drzewo nowe_drzewo_huffmana = odkoduj_klucz(klucz, &reszta);
        if (nowe_drzewo_huffmana == NULL) {
            printf("MISSING KEY\n");
            return -4;
        }
        fclose(klucz);
        dlugosc_kolejki = zwroc_ilosc_elementow_drzewa(nowe_drzewo_huffmana);
        if (dlugosc_kolejki == 0) {
            printf("Plik %s jest pusty\n", argv[1]);
            return -2;
        }

        FILE *in = fopen(argv[2], "r");
        if (in == NULL) {
            printf("Blad -2\n");
            return -2;
        }
        FILE *out = fopen(argv[3], "w");
        if (out == NULL) {
            printf("Blad -3\n");
            return -3;
        }

        odkoduj_plik(nowe_drzewo_huffmana, in, out, dlugosc_kolejki, reszta);
        fclose(in);
        fclose(out);
        wyczysc_drzewo(nowe_drzewo_huffmana);
    }
    return 0;
}
