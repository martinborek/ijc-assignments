/*
 * tail.c
 * IJC-DU2, priklad 2, 24.4.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Funkce tail v C
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>

#define POCETZNAKU 1024

/** Hodnoty chyb programu */
enum tecodes
{
  EOK = 0,     /**< Bez chyby */
  ERADKY,
  EPARAM,    /**< Chybny prikazovy radek */
  EMALLOC,   /**< Zadny volny prostor pri alokaci */
  ESOUBOR,   /**< Chyba pri otevirani souboru pro cteni */
  ERADEK,   /**< Spatne zadana matice */
  EVYPIS, /**< Soubor obsahuje vic cisel */
  EUNKNOWN,    /**< Neznama chyba */
};

/** Chybova hlaseni odpovidajici hodnotam chyb. */
const char *ECODEMSG[] =
{
  [EOK] = "Vse v poradku.\n",
  [ERADKY] = "Pocet radku nebyl zadan korektne!\n",
  [EPARAM] = "Parametry byly spatne zadany!\n",
  [EMALLOC] = "Nepodarilo se ziskat pozadovanou pamet!\n",
  [ESOUBOR] = "Nepodarilo se otevrit soubor pro cteni!\n",
  [ERADEK] = "Minimalne jeden radek v souboru je delsi nez maximum!\n",
  [EVYPIS] = "Nastala chyba pri vypisu!\n",
  [EUNKNOWN] = "Nastala nepredvidana chyba!\n",
};

/** Struktura obsahujici hodnoty parametru prikazove radky. */
typedef struct params
{
  int ecode; // chybovy status
  int (*vypisRadky)(const char *, unsigned long);
  unsigned long pocetRadku;
  const char * vstupniSoubor;
}tParams;

/**
 * Vytiskne hlaseni odpovidajici hodnote chyby.
 * @param ecode Hodnota chyby programu.
 */
void printECode(int ecode)
{
  if (ecode < EOK || ecode > EUNKNOWN)
    ecode = EUNKNOWN;

  fprintf(stderr, "%s", ECODEMSG[ecode]);
}

int vypisPosledni(const char * nazevSouboru, unsigned long pocetRadku)
{
  unsigned long nacteno = 0;
  FILE * soubor;
  if (nazevSouboru != NULL)
  {
    if ((soubor = fopen(nazevSouboru, "r")) == NULL)
      return ESOUBOR;
  }
  else
    soubor = stdin;

  char * retezce = NULL;
  if ((retezce = (char *)malloc(sizeof(char) * pocetRadku * (POCETZNAKU + 1))) == 0)
    return EMALLOC;
 
  unsigned long posledniZnak = 0;
  unsigned long i = 0;
  while (1)
  {
    i = nacteno % pocetRadku;
    posledniZnak = (i + 1) * (POCETZNAKU + 1) - 2;
    retezce[posledniZnak] = '\n'; // ke zjisteni, zda se nahral cely radek

    if (fgets((retezce + i * (POCETZNAKU + 1)), POCETZNAKU + 1, soubor) == NULL)
      break;

    if (retezce[posledniZnak] != '\n' && retezce[posledniZnak - 1] != '\n')
    {
      free(retezce);
      return ERADEK; // radek je prilis dlouhy
    }
    nacteno++;
  }

  if (nazevSouboru != NULL)
    fclose(soubor);
  
  unsigned int j;
  for (j = 0; j < nacteno && j < pocetRadku; j++, i++)
  {
    i %= pocetRadku;
    if (fputs((retezce + i * (POCETZNAKU + 1)), stdout) == EOF)
    {
      free(retezce);
      return EVYPIS;
    }
  }
  free(retezce);
  return EOK;
}

int vypisOd(const char * nazevSouboru, unsigned long odRadku)
{
  FILE * soubor;
  if (nazevSouboru != NULL)
  {
    if ((soubor = fopen(nazevSouboru, "r")) == NULL)
      return ESOUBOR;
  }
  else
    soubor = stdin;

  char * retezec = NULL;
  if ((retezec = (char *)malloc(sizeof(char) * (POCETZNAKU + 1))) == 0)
    return EMALLOC;
 
  unsigned long cisloRadku = 1;
  while (1)
  {
    retezec[POCETZNAKU - 1] = '\n'; // ke zjisteni, zda se nahral cely radek
    if (fgets(retezec, POCETZNAKU + 1, soubor) == NULL)
      break;
    if (retezec[POCETZNAKU - 1] != '\n' && retezec[POCETZNAKU - 2] != '\n')
    {
      free(retezec);
      return ERADEK; // radek je prilis dlouhy
    }
    if (cisloRadku >= odRadku)
    {
      if (fputs((retezec), stdout) == EOF)
      {
        free(retezec);
        return EVYPIS;
      }
    }
    cisloRadku++;
  }

  free(retezec);
  return EOK;
}

/**
 * Zpracuje parametry prikazoveho radku a vrati je ve strukture tParams.
 * Je-li format parametru chybny, vrati hodnotu chyby.
 * @param argc Pocet argumentu.
 * @param argv Pole textovych retezcu s argumenty.
 * @return Vraci analyzovane argumenty prikazoveho radku.
 */
tParams getParams(int argc, char *argv[])
{
  tParams result =
  { // inicializace struktury na defaultni hodnoty
    .ecode = EOK,
    .vypisRadky = vypisPosledni,
    .pocetRadku = 10,
    .vstupniSoubor = NULL,
  };

  if (argc == 2)
    result.vstupniSoubor = argv[1];
  else if (argc == 3 || argc == 4)
  {
    if (strcmp("-n", argv[1]) == 0)
    {
      char * ukazatel;
      result.pocetRadku = strtoul(argv[2], &ukazatel, 10);
      if (ukazatel[0] != '\0') // chybny pocet radku
        result.ecode = ERADKY;
      else if (errno == ERANGE)
      {
        fprintf(stderr, "Jako pocet radku jste zadali prilis vysoke cislo. Bude pouzito %lu\n", ULONG_MAX);
      }
      else if (argc == 4)
        result.vstupniSoubor = argv[3];
      if (argv[2][0] == '-')
        result.ecode = ERADKY;
      if (argv[2][0] == '+')
      {
        result.vypisRadky = vypisOd;
	if (result.pocetRadku == 0)
          result.pocetRadku = 1;
      }
    }
    else // nespravne zadane parametry
      result.ecode = EPARAM;
  }
  else if (argc != 1) // nespravny pocet parametru
    result.ecode = EPARAM;

  return result;
}

int main (int argc, char *argv[])
{
  tParams params = getParams(argc, argv);
  if (params.ecode != EOK)
  { // chyba pri nacitani parametru
    printECode(params.ecode);
    return EXIT_FAILURE;
  }
  if (params.pocetRadku == 0)
    return EXIT_SUCCESS;

  int error = EOK;
  if ((error = params.vypisRadky(params.vstupniSoubor, params.pocetRadku)) != EOK)
  {
    printECode(error);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
