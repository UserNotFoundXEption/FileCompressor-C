#include "Kopiec.h"

void dodaj_do_kopca(drzewo **kopiec, int *index, drzewo element_dodawany) {
    (*kopiec)[*index] = element_dodawany;
    int nie_jest_kopcem = 1, index_obecny = *index;
    (*index)++;

    while (nie_jest_kopcem) {
        if (index_obecny == 1)
            nie_jest_kopcem = 0;
        else {
            int index_ojca;
            if (index_obecny % 2 == 0)
                index_ojca = index_obecny / 2;
            else
                index_ojca = (index_obecny - 1) / 2;

            if ((*kopiec)[index_obecny]->piorytet > (*kopiec)[index_ojca]->piorytet)
                nie_jest_kopcem = 0;
            else {
                drzewo element_pomocniczy = (*kopiec)[index_obecny];
                (*kopiec)[index_obecny] = (*kopiec)[index_ojca];
                (*kopiec)[index_ojca] = element_pomocniczy;
                index_obecny = index_ojca;
            }
        }
    }
}

drzewo sciagnij_z_kopca(drzewo **kopiec, int *index) {
    if (*index == 1) return NULL;
    drzewo element_zwracany = (*kopiec)[1];
    (*kopiec)[1] = (*kopiec)[(*index) - 1];
    (*index)--;
    int nie_jest_kopcem = 1, obecny_index_ojca = 1;
    while (nie_jest_kopcem) {
        if (obecny_index_ojca >= *index) nie_jest_kopcem = 0;
        if (obecny_index_ojca * 2 >= *index)
            nie_jest_kopcem = 0;
        else {
            if (obecny_index_ojca * 2 + 1 >= *index) {
                if ((*kopiec)[obecny_index_ojca]->piorytet > (*kopiec)[obecny_index_ojca * 2]->piorytet) {
                    drzewo element_pomocniczy = (*kopiec)[obecny_index_ojca];
                    (*kopiec)[obecny_index_ojca] = (*kopiec)[obecny_index_ojca * 2];
                    (*kopiec)[obecny_index_ojca * 2] = element_pomocniczy;
                }
                nie_jest_kopcem = 0;
            } else {
                if ((*kopiec)[obecny_index_ojca]->piorytet > (*kopiec)[obecny_index_ojca * 2]->piorytet ||
                    (*kopiec)[obecny_index_ojca]->piorytet > (*kopiec)[obecny_index_ojca * 2 + 1]->piorytet) {
                    int index_zamieniany;
                    if ((*kopiec)[obecny_index_ojca * 2]->piorytet > (*kopiec)[obecny_index_ojca * 2 + 1]->piorytet) {
                        index_zamieniany = obecny_index_ojca * 2 + 1;
                    } else {
                        index_zamieniany = obecny_index_ojca * 2;
                    }
                    drzewo element_pomocniczy = (*kopiec)[index_zamieniany];
                    (*kopiec)[index_zamieniany] = (*kopiec)[obecny_index_ojca];
                    (*kopiec)[obecny_index_ojca] = element_pomocniczy;
                    obecny_index_ojca = index_zamieniany;
                } else
                    nie_jest_kopcem = 0;
            }
        }
    }
    return element_zwracany;
}

void stworz_kopiec(drzewo *kolejka, drzewo **kopiec, int *index, int dlugosc_kolejki) {
    for (int i = 0; i < dlugosc_kolejki; i++)
        dodaj_do_kopca(kopiec, index, kolejka[i]);
}


