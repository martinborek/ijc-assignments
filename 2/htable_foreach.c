/*
 * htable_foreach.c
 * IJC-DU2, priklad 2, 24.4.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Funkce htable_foreach
 * Volani zadane funkce pro kazdy prvek tabulky
 */
#include <stdlib.h>
#include "htable.h"

void htable_foreach(htable_t * t, void (*function)(const char * key, unsigned int value))
{
  listitem_t * item;
  unsigned int i;
  for (i = 0; i < t->size; i++)
  { // prochazeni celeho pole
    item = t->array[i];
    while (item != NULL)
    { // prochazeni vsech prvku se stejnym indexem hashe
      function(item->key, item->data);
      item = item->next;
    }
  }
}
