/*
 * bitarray.h
 * IJC-DU1, priklad a), 20.3.2012
 * Autor: Martin Borek (xborek08), FIT
 * Prelozeno: gcc 4.5.3
 * Makra a inline funkce pro praci s bitovym polem.
 * V prvnim prvku pole je ulozena velikost pole bitoveho.
 */ 

#ifndef BARRAY
#define BARRAY

#include <limits.h> // kvuli CHAR_BIT
#include <stdbool.h>
#include "error.h"

/** Pocet bitu v jednom UL */
#define ULBITU (8 * sizeof (unsigned long))

/** Velikost bitoveho pole */
#define BAVELIKOST(velikost) ((velikost % ULBITU) ?\
  (velikost/ULBITU) + 1 : velikost/ULBITU) 

#define BitArray(jmeno, velikost) \
  /** v prvnim prvku pole je ulozena velikost bitoveho pole */\
  unsigned long jmeno[BAVELIKOST(velikost) + 1] = {velikost};\

typedef unsigned long *BitArray_t; // pro predavani funkcim

#ifndef USE_INLINE
/** Vytvoreni bitoveho pole */
#define BitArraySize(pole) pole[0]

/** Nastaveni zadaneho bitu na 0 ci 1 */
#define SetBit(pole, index, hodnota) \
  if (index >= BitArraySize(pole) || index < 0)\
    FatalError("Index %ld mimo rozsah 0..%ld", (long)index, (long)BitArraySize(pole));\
  if (hodnota)\
    pole[(index / ULBITU) + 1] |= (1L << (index % ULBITU));\
  else\
    pole[(index / ULBITU) + 1] &= ~(1L << (index % ULBITU));

/** Zjisteni hodnoty zadaneho bitu */
#define GetBit(pole, index)\
  ((index >= BitArraySize(pole) || index < 0) ?\
FatalError("Index %ld mimo rozsah 0..%ld", (long)index, (long)BitArraySize(pole)), 0 :\
((pole[(index) / ULBITU + 1] & (1L << (index % ULBITU))) != 0))
  
#endif

#define DU1_SET_BIT(pole, index, hodnota) \
  if (hodnota)\
    ((char *)pole)[index / CHAR_BIT] |= (1 << (index % CHAR_BIT));\
  else\
    ((char *)pole)[index / CHAR_BIT] &= ~(1 << (index % CHAR_BIT));

#define DU1_GET_BIT(pole, index) ((((char *)pole)[index / CHAR_BIT] &\
(1 << (index % CHAR_BIT))) != 0)

#ifdef USE_INLINE

/** Vytvoreni bitoveho pole */
static inline unsigned long BitArraySize(BitArray_t pole)
{
  return pole[0];
}

/** Nastaveni zadaneho bitu na 0 ci 1 */
static inline void SetBit(BitArray_t pole, unsigned long index, bool hodnota)
{
  if (index >= BitArraySize(pole) || index < 0)
    FatalError("Index %ld mimo rozsah 0..%ld", (long)index, (long)BitArraySize(pole));

  if (hodnota)
    pole[(index / ULBITU) + 1] |= (1L << (index % ULBITU));
  else
    pole[(index / ULBITU) + 1] &= ~(1L << (index % ULBITU));
}

/** Zjisteni hodnoty zadaneho bitu */
static inline bool GetBit(BitArray_t pole, unsigned long index)
{
  if (index >= BitArraySize(pole) || index < 0)
    FatalError("Index %ld mimo rozsah 0..%ld", (long)index, (long)BitArraySize(pole));

  return ((pole[(index / ULBITU) + 1] & (1L << (index % ULBITU))) != 0);
}

#endif
#endif
