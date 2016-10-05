/*
 * error.c
 * IJC-DU1, priklad b), 20.3.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Funkce pro vypis chybovych hlaseni
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "error.h"

/**
 * Vypis chyby s obdrzenym textem na chybovy vystup.
 * @param fmt Popis chyby.
 * @param ... Promenny pocet parametru obsahujici hodnoty pro format printf.
 */
void Error(const char *fmt, ...)
{
  va_list parametry;
  va_start(parametry, fmt);
  fprintf(stderr, "CHYBA: ");
  vfprintf(stderr, fmt, parametry);
  fprintf(stderr, "\n");
  va_end(parametry);
}

/**
 * Vypis chyby s obdrzenym textem na chybovy vystup, ukonci program.
 * @param fmt Popis chyby.
 * @param ... Promenny pocet parametru obsahujici hodnoty pro format printf.
 */
void FatalError(const char *fmt, ...)
{
  va_list parametry;
  va_start(parametry, fmt);
  fprintf(stderr, "CHYBA: ");
  vfprintf(stderr, fmt, parametry);
  fprintf(stderr, "\n");
  va_end(parametry);
  exit(1);
}
