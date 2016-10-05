/*
 * htable_remove.c
 * IJC-DU2, priklad 2, 24.4.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Funkce htable_remove
 * Vyhledani a zruseni polozky
 */

#include <stdlib.h>
#include <string.h>
#include "htable.h"

void htable_remove(htable_t * t, const char * key)
{
  unsigned int index = hash_function(key, t->size); // pro pristup v poli
  
  listitem_t * item;
  listitem_t * previous = NULL; // ukazatel na predchozi prvek
  if ((item = t->array[index]) == NULL)
    return;
  while (item != NULL)
  {
    if (strcmp(item->key, key) == 0)
    {
      if (previous == NULL)
        t->array[index] = item->next;
      else
        previous->next = item->next;

      free(item->key);
      free(item);
      break;
    }
    previous = item;
    item = item->next;
  }
}
