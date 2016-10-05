/*
 * htable_init.c
 * IJC-DU2, priklad 2, 24.4.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Funkce htable_init
 * Vytvoreni a inicializace tabulky, neni-li pamet, vraci NULL
 */

#include <stdlib.h>
#include "htable.h"

htable_t * htable_init(unsigned int size)
{
  htable_t * t;

  if ((t = (htable_t *) malloc(sizeof(htable_t) + sizeof(listitem_t *) * size)) == NULL)
    return NULL;

  unsigned int i;
  for (i = 0; i < size; i++) // vyprazdneni tabulky
    t->array[i] = NULL;

  t->size = size;
  return t;
}
