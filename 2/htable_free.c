/*
 * htable_free.c
 * IJC-DU2, priklad 2, 24.4.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Funkce htable_free
 * Zruseni cele tabulky (vola hash_clear)
 */

#include <stdlib.h>
#include "htable.h"

void htable_free(htable_t * t)
{
  if (t == NULL)
    return;
  htable_clear(t);
  
  free(t);
}
