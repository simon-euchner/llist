/* -------------------------------------------------------------------------- *
 *                                                                            *
 * This file is part of the C library *llist* by Simon Euchner.               *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 *                                                                            *
 * LICENSE: GPL-3.0                                                           *
 *                                                                            *
 * IMPORTANT: THIS IS FREE SOFTWARE WITHOUT ANY WARRANTY. THE USER IS FREE TO *
 *            MODIFY AND REDISTRIBUTE THIS SOFTWARE UNDER THE TERMS OF THE    *
 *            LICENSE LISTED ABOVE PUBLISHED BY THE FREE SOFTWARE FOUNDATION. *
 *            THE PUBLISHER, SIMON EUCHNER, IS NOT RESPONSIBLE FOR ANY        *
 *            NEGATIVE EFFECTS THIS SOFTWARE MAY CAUSE.                       *
 *                                                                            *
 * -------------------------------------------------------------------------- *
 *                                                                            *
 * Functions for working with linked lists.                                   *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#ifndef LLIST_H
#define LLIST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <complex.h>

// Data types
typedef uint64_t LLIST_INT;
typedef uint64_t LLIST_MAXINT;
typedef double LLIST_DTYPE;
typedef long double complex LLIST_MAXDTYPE;

// Definition of linked lists
typedef struct LListNode {
    LLIST_DTYPE x;
    struct LListNode *next;
} llist_node;
typedef struct LList {
    LLIST_INT length;
    llist_node *first;
    llist_node *final;
} llist;

// Methods
llist *llist_empty();
void llist_append(llist *, LLIST_DTYPE);
void llist_prepend(llist *, LLIST_DTYPE);
void llist_insert(llist *, LLIST_INT, LLIST_DTYPE);
void llist_print(llist *);
void llist_destroy(llist*);
llist *llist_copy(llist *);
llist *llist_zeros(LLIST_INT);
llist *llist_ones(LLIST_INT);
llist *llist_fromFunc(void *, LLIST_DTYPE (*)(void *, LLIST_INT), LLIST_INT);
void llist_concatenate(llist *, llist *);
void llist_add(llist *, const llist *);
void llist_multiply(llist *, const llist *);
void llist_scale(LLIST_DTYPE, llist *);
void llist_removeFirst(llist *);
void llist_removeLast(llist *);
LLIST_DTYPE llist_sum(llist *);
LLIST_DTYPE llist_product(llist *);
void llist_remove(llist *, LLIST_INT);
void llist_map(llist *,
               void *,
               LLIST_DTYPE (*)(void *, LLIST_INT, LLIST_DTYPE));
LLIST_DTYPE llist_get(llist *, LLIST_INT);
void llist_swap(llist *, LLIST_INT, LLIST_INT);
llist *llist_split(llist *, LLIST_INT);
llist *llist_qsort(llist *, bool (*)(LLIST_DTYPE, LLIST_DTYPE));

#endif
