/*
 * ppm.h
 * IJC-DU1, priklad b), 20.3.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Rozhrani pro funkce nacitajici a ukladajicici obrazek ve formatu PPC ze
 * souboru ppm.c
 */ 

/** Datovy typ pro obrazek PPM */
typedef struct ppm
{
  unsigned xsize;
  unsigned ysize;
  char * data;
}Tppm;

Tppm * ppm_read(const char * filename);

int ppm_write(Tppm *p, const char * filename);
