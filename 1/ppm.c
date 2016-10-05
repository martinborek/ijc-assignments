/*
 * ppm.c
 * IJC-DU1, priklad b), 20.3.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Funkce nacitajici a ukladajicici obrazek ve formatu PPC
 */ 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // kvuli isspace()

#include "ppm.h"
#include "error.h"

/** makra pro vypis chyb a ukonceni */

#define REERR(chyba) {\
    Error(chyba);\
    free(ppm);\
    return NULL;\
  }

#define REERRFI(chyba) {\
    fclose(soubor);\
    REERR(chyba)\
  }

#define REERRFR(chyba) {\
    free (ppm->data);\
    REERRFI(chyba)\
  }  

/**
 * Nacteni obrazku formatu PPM do struktury Tppm.
 * @param filename Nazev obrazku, ktery se ma nacist.
 * @return Vraci ukazatel na funkci alokovanou strukturu s obrazkem.
 */
Tppm * ppm_read(const char * filename)
{
  Tppm * ppm;

  if ((ppm = (Tppm *) malloc(sizeof(Tppm))) == NULL) // alokace mista pro obrazek 
    REERR("Nedostatek mista v pameti.");
  
  char magicNum[3]; // obrazek musi zacinat magickym cislem P6
  unsigned int maxClr; // maximalni barva musi mit hodnout 255

  FILE *soubor;
  if ((soubor = fopen(filename, "r")) == NULL)
    REERR("Zadany soubor se nepodarilo otevrit pro cteni.");

  if (fgets(magicNum, 3, soubor) == NULL || strcmp("P6", magicNum) != 0)
    REERRFI("Spatny format souboru - neshoduje se magicke cislo.");
  
  if (fscanf(soubor, "%u", &(ppm->xsize)) != 1)
    REERRFI("Spatny format souboru - nepodarilo se nacist rozmer obrazku.");
 
  
  if (fscanf(soubor, "%u", &(ppm->ysize)) != 1)
    REERRFI("Spatny format souboru - nepodarilo se nacist rozmer obrazku.");

  if ((fscanf(soubor, "%u", &maxClr) != 1) || maxClr != 255)
    REERRFI("Program umi zpracovat pouze obrazek s barvami do hodnoty 255");

  unsigned long pocetBytu = ppm->xsize * ppm->ysize * 3; // pocet bytu v obrazku
  if ((ppm->data = (char *) malloc(pocetBytu)) == NULL)
    REERRFI("Nedostatek mista v pameti.");

  if (!isspace(fgetc(soubor))) // test na bily znak pred obrazkovymi daty
    REERRFR("Spatny format souboru - chybi bily znak.");
 
  unsigned int i = 0;
  while (i < pocetBytu && !feof(soubor))
  { // nacitani jednotlivych bytu do pameti
    ppm->data[i] = fgetc(soubor);
    i++;
  }

  if (i < pocetBytu)
    REERRFR("Rozmery obrazku neodpovidaji - soubor je prilis kratky.");

  if (fgetc(soubor) != EOF)
    REERRFR("Rozmery obrazku neodpovidaji - soubor je prilis dlouhy.");

  fclose(soubor);
  return ppm;
}

/**
 * Zapis obrazku formatu PPM ze struktury Tppm do souboru.
 * @param filename Nazev soboru, kam se ma obrazek ulozit.
 * @return Vraci 0, pokud vse probehlo v poradku a -1 v pripade chyby.
 */
int ppm_write(Tppm *p, const char * filename)
{
  FILE *soubor;
  if ((soubor = fopen(filename, "w")) == NULL)
  {
    Error("Zadany soubor se nepodarilo otevrit pro zapis.");
    return -1;
  }
  fprintf(soubor, "P6\n%u %u\n255\n", p->xsize, p->ysize); // zapis hlavicky PPM

  unsigned long pocetBytu = p->xsize * p->ysize * 3; // pocet bytu v obrazku
  
  for (int i = 0; i < pocetBytu; i++) // zapis jednotlivych bytu
    fprintf(soubor, "%c", p->data[i]);
  
  if (fclose(soubor) == EOF)
  {
    Error("Obrazek se nepodarilo uspesne zavrit.");
    return -1;
  }

  return 0;
}



