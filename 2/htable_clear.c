/*
 * htable_clear.c
 * IJC-DU2, priklad 2, 24.4.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Funkce htable_clear
 * Zruseni vsech polozek v tabulce
 */

#include <stdlib.h>
#include "htable.h"
void htable_clear(htable_t * t)
{
  if (t == NULL)
    return;
  unsigned int i;
  listitem_t * item;
  listitem_t * tmp; // pomocny prvek
  for (i = 0; i < t->size; i++)
  {
    item = t->array[i];
    while (item != NULL)
    {
      tmp = item;
      item = item->next;
      free(tmp->key);
      free(tmp);
    }
  }
}
