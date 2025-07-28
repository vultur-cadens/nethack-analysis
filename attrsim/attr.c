/* This file contains code copied from NetHack and is licensed under
 * the NetHack General Public License.  The original copyright notice
 * follows: */

/*      Copyright 1988, 1989, 1990, 1992, M. Stephenson           */
/* NetHack may be freely redistributed.  See license for details. */

/* vultur-cadens has made modifications in 2022, 2025. */

#include <stdlib.h> /* for rand() */

#include "attr.h"

static int
rn2(int x)
{
#ifdef BIASED_RN2
    /* equivalent to the original nethack version, but this may result
     * in noticeably different results when RAND_MAX is small */
    return rand() % x;
#else
    /* unbiased version so that results are similar regardless of
     * system as long rand() itself is acceptable, though it doesn't
     * quite match the original nethack implementation */
    int rnd;
    do {
        rnd = rand();
    } while (rnd >= (RAND_MAX - RAND_MAX % x));
    return rnd % x;
#endif
}

#ifdef NH_36 /* NetHack 3.6.7 and prior */
/* based on init_attr() in attrib.c */
void
init_attr(unsigned char result[A_MAX],
          const unsigned char attrbase[A_MAX],
          const unsigned char attrdist[A_MAX],
          const unsigned char attrmax[A_MAX],
          const unsigned char attrmin[A_MAX],
          int np)
{
    int i, x, tryct;

    for (i = 0; i < A_MAX; i++) {
        result[i] = attrbase[i];
        np -= attrbase[i];
    }
    tryct = 0;
    while (np > 0 && tryct < 100) {
        x = rn2(100);
        for (i = 0; (i < A_MAX) && ((x -= attrdist[i]) > 0); i++)
            ;
        if (i >= A_MAX)
            continue; /* impossible */

        if (result[i] >= attrmax[i]) {
            tryct++;
            continue;
        }
        tryct = 0;
        result[i]++;
        np--;
    }

    tryct = 0;
    while (np < 0 && tryct < 100) {
        x = rn2(100);
        for (i = 0; (i < A_MAX) && ((x -= attrdist[i]) > 0); i++)
            ;
        if (i >= A_MAX)
            continue; /* impossible */

        if (result[i] <= attrmin[i]) {
            tryct++;
            continue;
        }
        tryct = 0;
        result[i]--;
        np++;
    }
}
#endif /* NH_36 */

#ifdef NH_37 /* NetHack 3.7 */
/* based on init_attr() in attrib.c */
void
init_attr(unsigned char result[A_MAX],
          const unsigned char attrbase[A_MAX],
          const unsigned char attrdist[A_MAX],
          const unsigned char attrmax[A_MAX],
          const unsigned char attrmin[A_MAX],
          int np)
{
    int i, x, tryct;

    for (i = 0; i < A_MAX; i++) {
        result[i] = attrbase[i];
        np -= attrbase[i];
    }
    tryct = 0;
    while (np > 0 && tryct < 100) {
        x = rn2(100);
        for (i = 0; i < A_MAX; ++i)
            if ((x -= attrdist[i]) < 0)
                break;
        if (i >= A_MAX || result[i] >= attrmax[i]) {
            tryct++;
            continue;
        }
        tryct = 0;
        result[i]++;
        np--;
    }

    tryct = 0;
    while (np < 0 && tryct < 100) {
        x = rn2(100);
        for (i = 0; i < A_MAX; ++i)
            if ((x -= attrdist[i]) < 0)
                break;
        if (i >= A_MAX || result[i] <= attrmin[i]) {
            tryct++;
            continue;
        }
        tryct = 0;
        result[i]--;
        np++;
    }
}
#endif /* NH_37 */

/* apply minor variation to attributes */
void
vary_init_attr(unsigned char result[A_MAX],
               const unsigned char attrmax[A_MAX],
               const unsigned char attrmin[A_MAX])
{
    int i;

    for (i = 0; i < A_MAX; i++) {
        if (!rn2(20)) {
            int xd = rn2(7) - 2; /* biased variation */
            result[i] += xd;
            if (result[i] < attrmin[i]) {
                result[i] = attrmin[i];
            }
            if (result[i] > attrmax[i]) {
                result[i] = attrmax[i];
            }
        }
    }
}

