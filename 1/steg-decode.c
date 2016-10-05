/*
 * ppm.c
 * IJC-DU1, priklad b), 20.3.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Programek najde tajnou zpravu ze zadaneho obrazku (format PPM). Zprava je
* umistena po jednotlivych bitech (pocinaje LSb) na LSb bytu urcenych prvocisly
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit-array.h"
#include "ppm.h"
#include "eratosthenes.h"
#include "error.h"

/**
 * Dekodovani zpravy ulozene ve strukture Tppm.
 * @param ppm Obsahuje nacteny obrazek, ze ktereho se ma zprava ziskat.
 * @return Vraci ukazatel na ziskanou zpravu.
 */
char * dekodovani(Tppm * ppm)
{
  unsigned long i, j; // indexy pro pristup k poli
  unsigned long pocetBytu = ppm->xsize * ppm->ysize * 3; // pocet bytu v obrazku
  char * zprava; // pro vyslednou dekodovanou zpravu
  if ((zprava = (char *) malloc(pocetBytu / 8)) == NULL)
    FatalError("Nedostatek mista v pameti.");
  
  BitArray(sito, 3932160); // pocita s obrazkem do velikosti 1280*1024
  Eratosthenes(sito); // zjisteni prvocisel

  for (i = 0, j = 0; i < pocetBytu; i++)
  { // prochazeni jednotlivych bitu nacteneho obrazku
    
    if (!GetBit(sito, i))
    { // kontrola, zda-li dany byte patri pod prvocislo

      // nastaveni zjistene hodnoty LSb do bitoveho pole zpravy
      DU1_SET_BIT(zprava, j, DU1_GET_BIT(ppm->data, (i * 8)));
      j++;

      if (j % 8 == 0 && zprava[j / 8 - 1] == '\0') // zprava konci \0
        break;
    }

  }

  return zprava;
}

int main(int argc, char *argv[])
{
  if (argc == 1)
    FatalError("Nebyla zadana cesta k obrazku se zasifrovanou zpravou.");
  Tppm * ppm = ppm_read(argv[1]); // nacteni obrazku

  if (ppm == NULL) // ppm_read vraci NULL, nastane-li chyba pri nacitani
    FatalError("Dekodovani zpravy nemuze pokracovat.");
  
  char * zprava = dekodovani(ppm);

  printf("%s\n", zprava);

  return 0;
}
