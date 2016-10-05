/*
 * eratosthenes.c
 * IJC-DU1, priklad a), 20.3.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Ziskani prvocisel na zaklade Eratosthenova sita
 */ 

#include <stdio.h> 
#include <math.h> // kvuli sqrt()
#include "eratosthenes.h"
#include "bit-array.h"

/**
 * Ziskani prvocisel na zaklade Eratosthenova sita.
 * @param pole Obsahuje vynulovane bitove pole, ve kterem se vyznaci prvocisla 
 */
void Eratosthenes(BitArray_t pole)
{
  unsigned int iMax = sqrt(BitArraySize(pole));
  unsigned int i;
  unsigned int j;

  SetBit(pole, 0, 1); // 0 neni prvocislo
  SetBit(pole, 1, 1); // 1 neni prvocislo
  
  for (i = 2; i <= iMax; i++)
  {
    if (GetBit(pole, i))
      continue;

    for (j = i<<1; j < BitArraySize(pole); j += i)
    {
      SetBit(pole, j, 1);
    }
  }
}
