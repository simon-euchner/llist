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


#include "../inc.d/llist.h"


// Empty list
llist *llist_empty() {
    llist *l = (llist *)malloc(sizeof(llist));
    l->length = 0; l->final = l->first = NULL;
    return l;
}

// Append element
void llist_append(llist *l, DTYPE x) {
    llist_node *new = (llist_node *)malloc(sizeof(llist_node)); l->length++;
    if (l->final) { l->final->next = new; } else { l->first = new; }
    l->final = new; l->final->x = x; l->final->next = NULL;
}

// Prepend element
void llist_prepend(llist *l, DTYPE x) {
    llist_node *new = (llist_node *)malloc(sizeof(llist_node)); l->length++;
    if (l->first) {
        new->next = l->first;
    } else {
        new->next = NULL; l->final = new;
    }
    l->first = new; l->first->x = x;
}

// Insert element at given position
void llist_insert(llist *l, INT position, DTYPE x) {
    if ((!l->first) || (position >= l->length)) {
        llist_append(l, x);
    } else
    if (!position) {
        llist_prepend(l, x);
    } else {
        llist_node *n = l->first; l->length++;
        llist_node *new = (llist_node *)malloc(sizeof(llist_node));
        while (position > 1) { n = n->next; position--; }
        new->next = n->next; n->next = new; new->x = x;
    }
}

// Print
void llist_print(llist *l) {
    printf("\n---\nLINKED LIST WITH %lu ENTRIE(S)\n\n", (MAXINT)l->length);
    llist_node *n = l->first;
    while (n) {
        MAXDTYPE x = (MAXDTYPE)n->x; n = n->next;
        printf("%+1.3E%+1.3E*I\n", creal(x), cimag(x));
    }
    printf("%s\n", "---");
}

// Destroy
void llist_destroy(llist *l) {
    llist_node *m, *n = l->first;
    if (n) { while ((m = n->next)) { free(n); n = m; } free(n); } free(l);
}

// Copy
llist *llist_copy(llist *l) {
    llist *result = llist_empty(); llist_node *n = l->first;
    while (n) { llist_append(result, n->x); n = n->next; }
    return result;
}

// Linked list with *length* entries, all zero
llist *llist_zeros(INT length) {
    llist *result = llist_empty();
    for (INT k=0; k<length; k++) llist_append(result, (DTYPE)0);
    return result;
}

// Linked list with *length* entries, all ones
llist *llist_ones(INT length) {
    llist *result = llist_empty();
    for (INT k=0; k<length; k++) llist_append(result, (DTYPE)1);
    return result;
}

// Initialize elements by sequance ai, i=0, ..., length; [a0, a1, a2, ... ]
llist *llist_fromFunc(void *data, DTYPE (*ai)(void *, INT), INT length) {
    llist *l = llist_empty();
    for (INT i=0; i<length; i++) llist_append(l, ai(data, i));
    return l;
}

// Concatenate l1 = (l1, l2); after call l1 is the result; l2 is destroyed
void llist_concatenate(llist *l1, llist *l2) {
    if (l1->final) {
        l1->final->next = l2->first; l1->length += l2->length;
        if(l2->final) l1->final = l2->final;
    } else {
        l1->length = l2->length; l1->first = l2->first; l1->final = l2->final;
    }
    free(l2);
}

// Element wise addition; result is saved in l1; l1 = l1 + l2
void llist_add(llist *l1, const llist *l2) {
    if (l1->length != l2->length) {
        printf("%s\n", "llist: Dimension mismatch in *llist_add*"); exit(1);
    } else {
        llist_node *n, *m; n = l1->first; m = l2->first;
        while (n) { n->x += m->x; n = n->next; m = m->next; }
    }
}

// Element wise multiplication; result is saved in l1; l1 = l1 * l2
void llist_multiply(llist *l1, const llist *l2) {
    if (l1->length != l2->length) {
        printf("%s\n", "llist: Dimension mismatch in *llist_add*"); exit(1);
    } else {
        llist_node *n, *m; n = l1->first; m = l2->first;
        while (n) { n->x *= m->x; n = n->next; m = m->next; }
    }
}

// Scale; result is saved in l; l = alpha * l
void llist_scale(DTYPE alpha, llist *l) {
    llist_node *n = l->first; while (n) { n->x *= alpha; n = n->next; }
}

// Remove first entry
void llist_removeFirst(llist *l) {
    if (!l->length) {
        printf("%s\n", "llist: Cannot remove entry from empty list"); exit(1);
    }
    llist_node *n = l->first; l->first = l->first->next;
    if (!n->next) l->final = l->first;
    free(n); l->length--;
}

// Remove first entry
void llist_removeLast(llist *l) {
    if (!l->length) {
        printf("%s\n", "llist: Cannot remove entry from empty list"); exit(1);
    }
    if (l->length == 1) {
        free(l->first); l->first = l->final = NULL; l->length--; return;
    }
    llist_node *m, *n = l->first; m = n; while (n->next) { m = n; n = n->next; }
    m->next = NULL; free(n); l->length--; l->final = m;
}

// Remove element at given position
void llist_remove(llist *l, INT position) {
    if (l->length <= position) {
        printf("%s\n", "llist: Cannot remove non-existent entry"); exit(1);
    }
    if (position == 0) {
        llist_removeFirst(l);
    } else
    if (position == l->length-1) {
        llist_removeLast(l);
    } else {
        llist_node *m, *n = l->first; INT k = 0;
        while (k < position-1) { n = n->next; k++; }
        m = n->next->next; free(n->next); n->next = m; l->length--;
    }
}

// Sum
DTYPE llist_sum(llist *l) {
    DTYPE result = (DTYPE)0; llist_node *n = l->first;
    while (n) { result += n->x; n = n->next; }
    return result;
}

// Product
DTYPE llist_product(llist *l) {
    DTYPE result = (DTYPE)1; llist_node *n = l->first;
    while (n) { result *= n->x; n = n->next; }
    return result;
}

// Map entries to new ones using an index dependent function
void llist_map(llist *l, void *data, DTYPE (*fix)(void *, INT, DTYPE)) {
    llist_node *n = l->first; INT i = 0;
    while (n) { n->x = fix(data, i++, n->x); n = n->next; }
}

// Get entry; if position is to large, last one is returned
DTYPE llist_get(llist *l, INT position) {
    if (!l->length) {
        printf("%s\n", "llist: Cannot get entry from empty list"); exit(1);
    } else {
        llist_node *n = l->first; INT k = 0;
        while (n->next && (k < position)) { n = n->next; k++; };
        return n->x;
    }
}

// Swap list entries
void llist_swap(llist *l, INT i, INT j) {
    if ((i >= l->length) || (j >= l->length)) {
        printf("%s\n", "llist: Cannot swap non-existent entries"); exit(1);
    } else
    if (i == j)
    {
        return;
    } else {
        llist_node *n, *nmin; INT min, max, k = 0; DTYPE xmin;
        if (i < j) min = i; else min = j;
        if (i > j) max = i; else max = j;
        n = l->first;
        while (k < min) { n = n->next; k++; } xmin = n->x; nmin = n;
        while (k < max) { n = n->next; k++; } nmin->x = n->x; n->x = xmin;
    }
}

// Split after *i* entries; *left* is returned, *l* is overwritten with *right*
llist *llist_split(llist *l, INT i) {
    if (i > l->length) {
        printf("%s\n", "llist: Cannot split at non-existent position");
        exit(1);
    }
    llist *m = llist_empty(); if (!i) return m;
    llist_node *ln_prev, *ln, *mn; ln_prev = mn = ln = l->first;
    m->first = mn; ln = ln->next;
    l->length--; m->length++; INT j = 1;
    while (j++ < i) {
        mn->next = ln; ln_prev = ln; ln = ln->next; mn = mn->next;
        l->length--; m->length++;
    }
    l->first = ln; m->final = ln_prev; m->final->next = NULL;
    return m;
}

// Quick sort; l is destroyed and the sorted list returned
llist *llist_qsort(llist *l, bool (*cmp)(DTYPE, DTYPE)) {
    if (l->length == 0 || l->length == 1) {
        llist *ll = llist_copy(l); llist_destroy(l);
        return ll;
    }
    DTYPE x; llist *ll, *lg; llist_node *n;
    x = llist_get(l, 0); llist_removeFirst(l); n = l->first;
    ll = llist_empty(); lg = llist_empty();
    while (n) {
        if (cmp(x, n->x)) {
            llist_append(ll, n->x);
        } else {
            llist_append(lg, n->x);
        }
        n = n->next;
    }
    ll = llist_qsort(ll, cmp); lg = llist_qsort(lg, cmp);
    llist_append(ll, x); llist_concatenate(ll, lg); llist_destroy(l);
    return ll;
}
