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
 * Tests for the library *llist*.                                             *
 *                                                                            *
 * -------------------------------------------------------------------------- */


#include "../inc.d/llist.h"
#include <math.h>


LLIST_DTYPE f(void *, LLIST_INT);
void perm(LLIST_INT, llist *, llist *);
void print_perm(LLIST_INT);
bool cmp(LLIST_DTYPE, LLIST_DTYPE);


LLIST_INT main(LLIST_INT argc, char **argv)
{
    (void)argc; (void)argv;

    // Define list
    llist *l = llist_fromFunc(NULL, &f, 10);

    // Mess up ordering
    llist_swap(l, 1, 0);
    llist_swap(l, 9, 7);
    llist_swap(l, 7, 6);
    llist_swap(l, 4, 2);
    llist_swap(l, 1, 4);
    llist_swap(l, 3, 5);

    // print messed up list
    llist_print(l);

    // Sort it
    llist *ls = llist_qsort(l, &cmp);

    // This now should be ordered again
    llist_print(ls);

    // Clean up
    llist_destroy(ls);

    // PrLLIST_INT permutations of LLIST_INTegers 1, ..., N
    LLIST_INT N = 3;
    print_perm(N);

    return 0;
}


// List initializer
LLIST_DTYPE f(void *data, LLIST_INT i) {
    (void)data;
    return (LLIST_DTYPE)(i+1);
}

// Get permutations of l and save them in ls
void perm(LLIST_INT Nfac, llist *l, llist *ls) {

    LLIST_INT i, j, Nfac_new;
    LLIST_DTYPE x;
    llist *m, *ms;

    // Trivial cases
    if (l->length == 0) { ls[0] = *llist_empty(); return; }
    if (l->length == 1) { ls[0] = *llist_copy(l); return; }

    // Kick out each element once
    for (i=0; i<l->length; i++) {
        m = llist_copy(l);
        x = llist_get(m, i);
        llist_remove(m, i);
        Nfac_new = Nfac/l->length;
        ms = (llist *)malloc(Nfac_new*sizeof(llist));
        perm(Nfac_new, m, ms);
        for (j=0; j<Nfac_new; j++) {
            llist_prepend(&ms[j], x);
            ls[i*Nfac_new+j] = *llist_copy(&ms[j]);
        }
        free(ms);
    }
}

// Print permutations of list [1, 2, ..., N]
void print_perm(LLIST_INT N) {
    LLIST_INT k, Nfac = (LLIST_INT)tgamma((double)(N+1));
    llist *l = llist_fromFunc(NULL, &f, N);
    llist *ls = (llist *)malloc(Nfac*sizeof(llist));
    perm(Nfac, l, ls);
    for (k=0; k<Nfac; llist_print(ls+k++));
    llist_destroy(l); free(ls);
}

// Comparer
bool cmp(LLIST_DTYPE x, LLIST_DTYPE y) {
    if (y < x) {
        return true;
    } else {
        return false;
    }
}
