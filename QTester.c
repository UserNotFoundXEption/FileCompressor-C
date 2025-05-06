#include "Kolejka.h"
#include "Kompresja.h"
#include "Kodowanie.h"
#include "Klucz.h"



int main(int argc, char **argv) {
    
    
    
    for(int i=1;i<53;i++){
    char plik[32];
    	if(i<10){
    		strcpy(plik,"testy/");
    		plik[6]=i+'0';
    		plik[7]='\0';
   		strcat(plik,".txt");
   	}
   	else{
   		strcpy(plik,"testy/");
   		plik[6]=i/10+'0';
   		plik[7]=i%10+'0';
   		plik[8]='\0';
   		strcat(plik,".txt");
   	}
    
 
    FILE *in = fopen(plik, "r");
    FILE *out = fopen("testy/kom.txt", "w");

    long int wszystkie_znaki[256];
    zlicz_znaki(&wszystkie_znaki, in);
    rewind(in);

    drzewo *kolejka, *kopiec;
    int dlugosc_kolejki = stworz_kolejke(wszystkie_znaki, &kolejka);
    if(dlugosc_kolejki == 0){
    printf("Plik %s jest pusty\n",plik);
    fclose(in);
    fclose(out);
    return -2;
    }	
    kopiec = malloc(sizeof(*kopiec) * (dlugosc_kolejki + 1));
    int index = 1;
    stworz_kopiec(kolejka, &kopiec, &index, dlugosc_kolejki);
    drzewo huffman = stworz_drzewo_huffmana(&kopiec, &index);
    int reszta = zakoduj_plik(huffman, in, out, dlugosc_kolejki);
    fclose(in);
    fclose(out);

    FILE *klucz = fopen("testy/klu.txt", "w");
    zapisz_klucz(huffman, klucz, reszta);
    fclose(klucz);

    wyczysc_drzewo(huffman);
    free(kolejka);
    free(kopiec);
			
    klucz = fopen("testy/klu.txt", "r");
    drzewo nowe_drzewo_huffmana = odkoduj_klucz(klucz, &reszta);
    fclose(klucz);
    dlugosc_kolejki = zwroc_ilosc_elementow_drzewa(nowe_drzewo_huffmana);

    in = fopen("testy/kom.txt", "r");    
    out = fopen("testy/dek.txt","w");
    odkoduj_plik(nowe_drzewo_huffmana, in, out, dlugosc_kolejki, reszta);
    fclose(in);
    fclose(out);
    wyczysc_drzewo(nowe_drzewo_huffmana);
    
    FILE *pierwotny = fopen(plik,"r");
    FILE *zdekompresowany = fopen("testy/dek.txt","r");
    int c1,c2;
    while((c1=getc(pierwotny)) != EOF){
    	c2=getc(zdekompresowany);
    	if(c1 != c2){
    		printf("Plik wynikowy rozni sie od pierwotnego pliku %s\n", plik);
    		return -1;
    	}}
    printf("Testy pliku %s przebiegly pomyslnie\n", plik);
    fclose(pierwotny);
    fclose(zdekompresowany);
    
}
return 0;
}
