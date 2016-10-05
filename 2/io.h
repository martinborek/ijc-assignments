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
int fgetword(char * s, int max, FILE * f);
