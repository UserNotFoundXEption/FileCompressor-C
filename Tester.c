#include "Kolejka.h"
#include "Kompresja.h"
#include "Kodowanie.h"
#include "Klucz.h"



int main(int argc, char **argv) {
    
    if(argc<5){
    printf("Za malo argumentow\n");
    printf("./Tester [PlikDoKompresji] [WyjscieDoPlikuSkompresowanego] [Klucz] [WyjscieDoPlikuPoDekompresji]\n");
    return -1;
    }
    
    
 
    FILE *in = fopen(argv[1], "r");
    if (in == NULL){
    printf("Blad -2\n");
    return -2;
    }
    FILE *out = fopen(argv[2], "w");
    if (out == NULL){
    printf("Blad -3\n");
    return -3;
    }

    long int wszystkie_znaki[256];
    zlicz_znaki(&wszystkie_znaki, in);
    rewind(in);

    drzewo *kolejka, *kopiec;
    int dlugosc_kolejki = stworz_kolejke(wszystkie_znaki, &kolejka);
    if(dlugosc_kolejki == 0){
    printf("Plik do kompresji jest pusty\n");
    return -2;
    }
    kopiec = malloc(sizeof(*kopiec) * (dlugosc_kolejki + 1));
    int index = 1;
    stworz_kopiec(kolejka, &kopiec, &index, dlugosc_kolejki);
    drzewo huffman = stworz_drzewo_huffmana(&kopiec, &index);


    int reszta = zakoduj_plik(huffman, in, out, dlugosc_kolejki);
    if(reszta==-1){
    printf("EMPTY FILE\n");
    return -2;
    }

    fclose(in);
    fclose(out);

    FILE *klucz = fopen(argv[3], "w");
    if (klucz == NULL){
    printf("Blad -4\n");
    return -4;
    }
    zapisz_klucz(huffman, klucz, reszta);
    fclose(klucz);

    wyczysc_drzewo(huffman);
    free(kolejka);
    free(kopiec);
    
			
    klucz = fopen(argv[3], "r");
    if (klucz == NULL){
    printf("Blad -4\n");
    return -4;
    }
    drzewo nowe_drzewo_huffmana = odkoduj_klucz(klucz, &reszta);
    if(nowe_drzewo_huffmana == NULL){
    	printf("MISSING KEY\n");
    	return -4;
    }
    fclose(klucz);
    dlugosc_kolejki = zwroc_ilosc_elementow_drzewa(nowe_drzewo_huffmana);	

    in = fopen(argv[2], "r");
    if (in == NULL){
    printf("Blad -2\n");
    return -2;
    }
    out = fopen(argv[4], "w");
    if (out == NULL){
    printf("Blad -3\n");
    return -3;
    }
    
    odkoduj_plik(nowe_drzewo_huffmana, in, out, dlugosc_kolejki, reszta);
    fclose(in);
    fclose(out);
    wyczysc_drzewo(nowe_drzewo_huffmana);
    
   
    
    FILE *pierwotny = fopen(argv[1],"r");
    FILE *zdekompresowany = fopen(argv[4],"r");
    
    int c1,c2;
    while((c1=getc(pierwotny)) != EOF){
    	c2=getc(zdekompresowany);
    	if(c1 != c2){
    		printf("Plik wynikowy rozni sie od pierwotnego\n");
    		return -1;
    	}}
    printf("Testy przebiegly pomyslnie\n");
    fclose(pierwotny);
    fclose(zdekompresowany);
    
    
    return 0;
}
