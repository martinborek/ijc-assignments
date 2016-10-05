/*
 * htable.h
 * IJC-DU2, priklad 2, 24.4.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Rozhrani hashovaci tabulky
 */ 

/**
 * Polozka seznamu hashovaci tabulky
 */
typedef struct htable_listitem listitem_t;
struct htable_listitem
{
  char * key; // ukazatel na dynamicky alokovany retezec
  unsigned int data; // pocet vyskytu daneho slova
  listitem_t * next;
};

/**
 * Hashovaci tabulka
 */
typedef struct htable
{
  unsigned int size;
  listitem_t *array[];
} htable_t;

/**
 * Ziskani indexu retezce do tabulky, rozptylovaci funkce
 */
unsigned int hash_function(const char *str, unsigned int htable_size);

/**
 * Vytvoreni a inicializace tabulky, neni-li pamet, vraci NULL
 */
htable_t * htable_init(unsigned int size);

/**
 * Vyhledavani, vraci ukazatel na prvek nebo NULL 
 */
listitem_t * htable_lookup(htable_t * t, const char * key);

/**
 * Volani zadane funkce pro kazdy prvek tabulky
 */
void htable_foreach(htable_t * t, void (*function)(const char * key, unsigned int value));

/**
 * Vyhledani a zruseni polozky
 */
void htable_remove(htable_t * t, const char * key);

/**
 * Zruseni vsech polozek v tabulce
 */
void htable_clear(htable_t * t);

/**
 * Zruseni cele tabulky (vola hash_clear)
 */
void htable_free(htable_t * t);

