/*
 * wordcount.c
 * IJC-DU2, priklad 2, 24.4.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Implementace hashovaci tabulky pro pocitani vyskytu slov ze stdin
 */ 

#include <stdlib.h>
#include <stdio.h>
#include "io.h"
#include "htable.h"
#define VELIKOSTPOLE 32749 // podle textu z IAL, musi byt prvocislo
#define CHARLIMIT 255 // maximalni delka slova

/**
 * Vypis nalezeneho slova a poctu jeho vyskytu
 */
void print_item(const char *key, unsigned int value)
{
  printf("%s\t%u\n", key, value);
}

int main ()
{
  htable_t * table;
  if ((table = htable_init(VELIKOSTPOLE)) == NULL)
  {
    printf("Nedostatek pameti!\n");
    exit(EXIT_FAILURE);
  }
  char string[CHARLIMIT + 1];
  
  listitem_t * item;
  
  while (fgetword(string, CHARLIMIT + 1, stdin) != EOF)
  {
    if ((item = htable_lookup(table, string)) == NULL)
    {
      printf("Nedostatek pameti!\n");
      htable_free(table);
      exit(EXIT_FAILURE);
    }
    item->data++;
  }

  htable_foreach(table, print_item); // vypis
  htable_free(table); // naravceni pameti
  return EXIT_SUCCESS;
}
