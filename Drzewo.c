#include "Drzewo.h"

drzewo stworz_drzewo(int symbol, int piorytet, drzewo lewy, drzewo prawy) {
    drzewo nowy;
    if ((nowy = malloc(sizeof(*nowy))) == NULL) {
        printf("stworz_drzewo BŁAD_1\n");
        exit(10);
    }
    nowy->symbol = symbol;
    nowy->piorytet = piorytet;
    nowy->l_syn = lewy;
    nowy->p_syn = prawy;
    return nowy;
}

void wyczysc_drzewo(drzewo t) {
    if (t != NULL) {
        wyczysc_drzewo(t->l_syn);
        wyczysc_drzewo(t->p_syn);
        free(t);
    }
}

int zwroc_ilosc_elementow_drzewa(drzewo h) {
    if (h == NULL) {
        return 0;
    } else if (h->l_syn == NULL && h->p_syn == NULL) {
        return 1;
    } else {
        return zwroc_ilosc_elementow_drzewa(h->p_syn) + zwroc_ilosc_elementow_drzewa(h->l_syn);
    }
}

void zaminen_na_zapis_binarny(int **tab, int *index, int symbol) {
    int zajete = 7;
    while (symbol > 0) {
        if (symbol % 2 == 0) (*tab)[(*index) + zajete] = 0;
        else (*tab)[*index + zajete] = 1;
        zajete--;
        symbol /= 2;
    }
    while (zajete > -1) {
        (*tab)[*index + zajete] = 0;
        zajete--;
    }
    (*index) += 8;
}

int zamien_na_zapis_dziesiety(int tab[], int i) {
    int symbol = tab[i];
    for (int j = 1; j < 8; j++) {
        symbol *= 2;
        if (tab[i + j] == 1) symbol++;
    }
    return symbol;
}
