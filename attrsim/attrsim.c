/* Copyright 2022, 2025 vultur-cadens */

/* You may use, redistribute, or modify this file under the terms of
 * your choice of: NetHack General Public License; or GNU General
 * Public License, version 3 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "attr.h"

#define STR18(x) (18 + (x))  /* 18/xx */
#define STR19(x) (20 + (x)) /* For 19 and above */

struct race {
    char *name;
    unsigned char attrmin[A_MAX];
    unsigned char attrmax[A_MAX];
};

struct role {
    char *name;
    unsigned char attrbase[A_MAX];
    unsigned char attrdist[A_MAX];
};

struct race races[] = {
    {
        "hum",
        { 3, 3, 3, 3, 3, 3 },
        { STR18(100), 18, 18, 18, 18, 18 },
    },
    {
        "dwa",
        { 3, 3, 3, 3, 3, 3 },
        { STR18(100), 16, 16, 20, 20, 16 },
    },
    {
        "elf",
        { 3, 3, 3, 3, 3, 3 },
        { 18, 20, 20, 18, 16, 18 },
    },
    {
        "gno",
        { 3, 3, 3, 3, 3, 3 },
        {STR18(50), 19, 18, 18, 18, 18 },
    },
    {
        "orc",
        { 3, 3, 3, 3, 3, 3 },
        { STR18(50), 16, 16, 18, 18, 16 },
    },
};

/* numbers from NetHack source file, role.c */
struct role roles[] = {
    {
        "arc",
        { 7, 10, 10, 7, 7, 7 },
        { 20, 20, 20, 10, 20, 10 },
    },
    {
        "bar",
        { 16, 7, 7, 15, 16, 6 },
        { 30, 6, 7, 20, 30, 7 },
    },
    {
        "cav",
        { 10, 7, 7, 7, 8, 6 },
        { 30, 6, 7, 20, 30, 7 },
    },
    {
        "hea",
        { 7, 7, 13, 7, 11, 16 },
        { 15, 20, 20, 15, 25, 5 },
    },
    {
        "kni",
        { 13, 7, 14, 8, 10, 17 },
        { 30, 15, 15, 10, 20, 10 },
    },
    {
        "mon",
        { 10, 7, 8, 8, 7, 7 },
        { 25, 10, 20, 20, 15, 10 },
    },
    {
        "pri",
        { 7, 7, 10, 7, 7, 7 },
        { 15, 10, 30, 15, 20, 10 },
    },
    {
        "rog",
        { 7, 7, 7, 10, 7, 6 },
        { 20, 10, 10, 30, 20, 10 },
    },
    {
        "ran",
        { 13, 13, 13, 9, 13, 7 },
        { 30, 10, 10, 20, 20, 10 },
    },
    {
        "sam",
        { 10, 8, 7, 10, 17, 6 },
        { 30, 10, 8, 30, 14, 8 },
    },
    {
        "tou",
        { 7, 10, 6, 7, 7, 10 },
        { 15, 10, 10, 15, 30, 20 },
    },
    {
        "val",
        { 10, 7, 7, 7, 10, 7 },
        { 30, 6, 7, 20, 30, 7 },
    },
    {
        "wiz",
        { 7, 10, 7, 7, 7, 7 },
        { 10, 30, 10, 20, 20, 10 },
    },
};

void
do_sim(double mean[A_MAX+1], double stdev[A_MAX+1], struct role *role,
       const unsigned char *attrmax, const unsigned char *attrmin, int n)
{
    int i;

    unsigned char (*result)[A_MAX+1] = malloc(n * sizeof *result);
    double sum[A_MAX+1] = {0};
    for (i = 0; i < n; i++) {
        init_attr(result[i], role->attrbase, role->attrdist,
                  attrmax, attrmin, 75);
        vary_init_attr(result[i], attrmax, attrmin);
        result[i][A_MAX] = 0;
        int j;
        for (j=0; j<A_MAX; j++) {
            sum[j] += result[i][j];
            result[i][A_MAX] += result[i][j];
        }
        sum[A_MAX] += result[i][A_MAX];
    }
    for (i = 0; i < A_MAX+1; i++) {
        mean[i] = sum[i] / n;
    }
    double sqsum[A_MAX+1] = {0};
    for (i = 0; i < n; i++) {
        int j;
        for (j = 0; j < A_MAX+1; j++) {
            double dev = result[i][j] - mean[j];
            sqsum[j] += dev * dev;
        }
    }
    for (i = 0; i < A_MAX+1; i++) {
        stdev[i] = sqrt(sqsum[i] / (n - 1));
    }
    free(result);
}

/* Example usage: attrsim wiz hum 10000000 */
int
main(int argc, char *argv[])
{
    size_t i;
    if (argc != 4) {
        fprintf(stderr, "usage: %s role race n\n", argv[0]);
        fprintf(stderr, "roles are:");
        for (i = 0; i < (sizeof roles / sizeof *roles); i++) {
            fprintf(stderr, " %s", roles[i].name);
        }
        fprintf(stderr, "\n");
        fprintf(stderr, "races are:");
        for (i = 0; i < (sizeof races / sizeof *races); i++) {
            fprintf(stderr, " %s", races[i].name);
        }
        fprintf(stderr, "\n");
        return EXIT_FAILURE;
    }
    int n = atoi(argv[3]);
    struct role *role = NULL;
    struct race *race = NULL;
    for (i = 0; i < (sizeof roles / sizeof *roles); i++) {
        if (!strcmp(argv[1], roles[i].name)) {
            role = &roles[i];
        }
    }
    if (!role) {
        fprintf(stderr, "invalid role %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    for (i = 0; i < (sizeof races / sizeof *races); i++) {
        if (!strcmp(argv[2], races[i].name)) {
            race = &races[i];
        }
    }
    if (!race) {
        fprintf(stderr, "invalid race %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    const unsigned char *attrmax, *attrmin;
    attrmax = race->attrmax;
    attrmin = race->attrmin;

    srand(time(NULL));

    double mean[A_MAX+1];
    double stdev[A_MAX+1];
    do_sim(mean, stdev, role, attrmax, attrmin, n);

    printf("Str: %.2f±%.2f\n"
           "Dex: %.2f±%.2f\n"
           "Con: %.2f±%.2f\n"
           "Int: %.2f±%.2f\n"
           "Wis: %.2f±%.2f\n"
           "Cha: %.2f±%.2f\n"
           "Sum: %.2f±%.2f\n",
           mean[A_STR], stdev[A_STR],
           mean[A_DEX], stdev[A_DEX],
           mean[A_CON], stdev[A_CON],
           mean[A_INT], stdev[A_INT],
           mean[A_WIS], stdev[A_WIS],
           mean[A_CHA], stdev[A_CHA],
           mean[A_MAX], stdev[A_MAX]);

    return EXIT_SUCCESS;
}
