/*
 * error.h
 * IJC-DU1, priklad b), 20.3.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Rozhrani pro funkce z error.c vypisujici chybova hlaseni
 */ 

#ifndef MYERROR
#define MYERROR

void Error(const char *fmt, ...);
void FatalError(const char *fmt, ...);

#endif
