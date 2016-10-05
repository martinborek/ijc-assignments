/*
 * io.h
 * IJC-DU2, priklad 2, 24.4.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Rozhrani funkce fgetword
 * Cte jedno slovo ze souboru f do zadaneho pole znaku a vrati delku slova
 * Z delsich slov vrati pouze max-1 znaku a zbytek preskoci.
 * Funkce vraci EOF, pokud je konec souboru.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "io.h"
int fgetword(char * s, int max, FILE * f)
{
  if (f == NULL || max <= 1)
    return EOF; // spatny ukazatel na soubor
  max--;
  int c;
  int i = 0;
  while ((c = getchar()) != EOF && isspace(c))
  {} // preskoceni mezer
  ungetc(c, stdin);

  while ((c = getchar()) != EOF && !isspace(c))
  {
    if (i >= max)
    {
      while ((c = getchar()) != EOF && !isspace(c))
      { } // preskoceni mezer
      break;
    }
    s[i] = c;
    i++;
  }
  s[i] = '\0';
  return (c == EOF) ? EOF : i;
}
