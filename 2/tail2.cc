/*
 * tail.c
 * IJC-DU2, priklad 2, 24.4.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: g++ 4.6.1
 * Funkce tail v C++
 */

#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <climits>

#include <string>
#include <deque>
#include <iostream>
#include <fstream>

using namespace std;

/** Hodnoty chyb programu */
enum tecodes
{
  EOK,     /**< Bez chyby */
  ERADKY,
  EPARAM,    /**< Chybny prikazovy radek */
  ESOUBOR,   /**< Chyba pri otevirani souboru pro cteni */
  EVYPIS, /**< Soubor obsahuje vic cisel */
  EUNKNOWN    /**< Neznama chyba */
};

/** Chybova hlaseni odpovidajici hodnotam chyb. */
const char *ECODEMSG[] =
{
  "Vse v poradku.",
  "Pocet radku nebyl zadan korektne!",
  "Parametry byly spatne zadany!",
  "Nepodarilo se otevrit soubor pro cteni!",
  "Nastala chyba pri vypisu!",
  "Nastala nepredvidana chyba!",
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
  
  cerr << ECODEMSG[ecode] << endl;
}

int vypisPosledni(const char * nazevSouboru, unsigned long pocetRadku)
{
  istream * vstup;
  ifstream soubor;
  if (nazevSouboru != NULL)
  {  
    soubor.open(nazevSouboru, ios::in);
    if (!soubor)
      return ESOUBOR;
    vstup = &soubor;
  }
  else
    vstup = &cin;

  deque<string> retezce;
  string str;
  while (getline(*vstup, str))
  {
    retezce.push_back(str);
    if (retezce.size() > pocetRadku)
      retezce.pop_front();
  }

  if (nazevSouboru != NULL)
    soubor.close();

  deque<string>::iterator iter;
  for (iter = retezce.begin(); iter != retezce.end(); iter++)
    cout << *iter << endl;

  return EOK;
}

int vypisOd(const char * nazevSouboru, unsigned long odRadku)
{
  istream * vstup;
  ifstream soubor;
  if (nazevSouboru != NULL)
  {
    soubor.open(nazevSouboru, ios::in);
    if (!soubor)
      return ESOUBOR;
    vstup = &soubor;
  }
  else
    vstup = &cin;

  string str;
  while (getline(*vstup, str))
    cout << str << endl;

  if (nazevSouboru != NULL)
    soubor.close();

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
  tParams result; // inicializace struktury na defaultni hodnoty
  result.ecode = EOK;
  result.vypisRadky = vypisPosledni;
  result.pocetRadku = 10;
  result.vstupniSoubor = NULL;

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
        cerr << "Jako pocet radku jste zadali prilis vysoke cislo. Bude pouzito" << ULONG_MAX;
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
