/*
 * htable_lookup.c
 * IJC-DU2, priklad 2, 24.4.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Funkce htable_lookup
 * Vyhledavani, vraci ukazatel na prvek tabulky
 */

#include <stdlib.h>
#include <string.h>
#include "htable.h"

listitem_t * htable_lookup(htable_t * t, const char * key)
{
  unsigned int index = hash_function(key, t->size);
  
  listitem_t * item;
  item = t->array[index]; //prvni prvek, odpovidajici klici
  while (item != NULL)
  { // porovavani klicu a posouvani na dalsi vhodnou polozku, neni-li ta prava
    if (strcmp(item->key, key) == 0)
      return item;
    if (item->next != NULL)
      item = item->next;
    else
      break;
  }

  listitem_t * new; // bude se vytvaret novy prvek
  if ((new = (listitem_t *) malloc(sizeof(listitem_t))) == NULL)
    return NULL;

  if ((new->key = (char *) malloc(sizeof(char) * (strlen(key) + 1))) == NULL)
  {
    free(new);
    return NULL;
  }
  strcpy(new->key, key);
  new->next = NULL;
  new->data = 0;

  if (item == NULL) // prvni prvek pro dany hash, tudiz ukazatel do tabulky
    t->array[index] = new;
  else // ukazatel do predchoziho prvku
    item->next = new;

  return new;
}
