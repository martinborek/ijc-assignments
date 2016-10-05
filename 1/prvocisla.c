/*
 * prvocisla.c
 * IJC-DU1, priklad a), 20.3.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Programek vypise vzestupne 10 nejvyssich prvocisel mensich nez 99 000 000
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <time.h> //zjisteni delky vypoctu programu

#include "error.h"
#include "bit-array.h"
#include "eratosthenes.h"


int main(void)
{
  BitArray(a, 99000000L);  // bitove pole o 99 000 000 prvcich
//  clock_t t1, t2;
//  t1  = clock();

  Eratosthenes(a);

  unsigned long prvocisla[10]; // pole pro nejvyssich 10 prvocisel, jenz se maji vypsat
  unsigned long cislo = BitArraySize(a) - 1; // prirazeni nejvyssiho cisla v poli
  int i;
  
  for (i = 9; i >= 0; i--)
  { 
    if (cislo < 1)
      break;

    while (GetBit(a, cislo) == 1 && cislo > 0)
    { // prochazi bitove pole s vyznacenymi prvocisly a hleda nejvyssi
      cislo--;
    }

    if (cislo < 1)
      break;

    prvocisla[i] = cislo; //

    cislo--;
  }

  for (i = 0; i < 10; i++)
    printf("%lu\n", prvocisla[i]);

//  t2 = clock();
//  printf("%f", (double) (t2 - t1) / CLOCKS_PER_SEC);
  return 0;
}
