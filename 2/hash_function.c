/*
 * hash_function.c
 * IJC-DU2, priklad 2, 24.4.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Funkce hash_function
 * Ziskani indexu retezce do tabulky, rozptylovaci funkce
 */ 

#include "htable.h"

unsigned int hash_function(const char *str, unsigned int htable_size)
{
  unsigned int h = 0;
  unsigned char *p;
  for (p = (unsigned char *) str; *p != '\0'; p++)
    h = 31 * h + *p;
  return h % htable_size;
}
