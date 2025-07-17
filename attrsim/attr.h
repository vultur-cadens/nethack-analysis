/* This file contains code copied from NetHack and is licensed under
 * the NetHack General Public License.  The original copyright notice
 * follows: */

/*      Copyright 1988, 1989, 1990, 1992, M. Stephenson           */
/* NetHack may be freely redistributed.  See license for details. */

/* vultur-cadens has made modifications in 2022, 2025. */

#ifndef ATTR_H
#define ATTR_H

#include <stdlib.h> /* for rand() */

enum attrib_types {
    A_STR = 0,
    A_INT,
    A_WIS,
    A_DEX,
    A_CON,
    A_CHA,

    A_MAX
};

static int
rn2(int x)
{
    return rand() % x;
}

#ifdef NH_36 /* NetHack 3.6.7 */
/* based on init_attr() in attrib.c */
static void
init_attr(unsigned char result[A_MAX],
             const unsigned char attrbase[A_MAX],
             const unsigned char attrdist[A_MAX],
             const unsigned char attrmax[A_MAX],
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

    /* additional adjustment from u_init.c */
    /* None of the base starting attributes are less than 5, so
       this won't make any attribute less than the minimum of 3 */
    for (i = 0; i < A_MAX; i++) {
        if (!rn2(20)) {
            int xd = rn2(7) - 2;
            result[i] += xd;
            if (result[i] > attrmax[i]) {
                result[i] = attrmax[i];
            }
        }
    }
}
#endif /* NH_36 */

#ifdef NH_37 /* NetHack 3.7 */
/* based on init_attr() in attrib.c */
static void
init_attr(unsigned char result[A_MAX],
             const unsigned char attrbase[A_MAX],
             const unsigned char attrdist[A_MAX],
             const unsigned char attrmax[A_MAX],
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

    /* additional adjustment from u_init.c */
    /* None of the base starting attributes are less than 5, so
       this won't make any attribute less than the minimum of 3 */
    for (i = 0; i < A_MAX; i++) {
        if (!rn2(20)) {
            int xd = rn2(7) - 2;
            result[i] += xd;
            if (result[i] > attrmax[i]) {
                result[i] = attrmax[i];
            }
        }
    }
}
#endif /* NH_37 */

#endif /* ATTR_H */
