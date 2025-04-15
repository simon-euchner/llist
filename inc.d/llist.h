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
typedef uint64_t INT;
typedef uint64_t MAXINT;
typedef double DTYPE;
typedef long double complex MAXDTYPE;

// Definition of linked lists
typedef struct LListNode {
    DTYPE x;
    struct LListNode *next;
} llist_node;
typedef struct LList {
    INT length;
    llist_node *first;
    llist_node *final;
} llist;

// Methods
llist *llist_empty();
void llist_append(llist *, DTYPE);
void llist_prepend(llist *, DTYPE);
void llist_insert(llist *, INT, DTYPE);
void llist_print(llist *);
void llist_destroy(llist*);
llist *llist_copy(llist *);
llist *llist_zeros(INT);
llist *llist_ones(INT);
llist *llist_fromFunc(void *, DTYPE (*)(void *, INT), INT);
void llist_concatenate(llist *, llist *);
void llist_add(llist *, const llist *);
void llist_multiply(llist *, const llist *);
void llist_scale(DTYPE, llist *);
void llist_removeFirst(llist *);
void llist_removeLast(llist *);
DTYPE llist_sum(llist *);
DTYPE llist_product(llist *);
void llist_remove(llist *, INT);
void llist_map(llist *, void *, DTYPE (*)(void *, INT, DTYPE));
DTYPE llist_get(llist *, INT);
void llist_swap(llist *, INT, INT);
llist *llist_split(llist *, INT);
llist *llist_qsort(llist *, bool (*)(DTYPE, DTYPE));

#endif
