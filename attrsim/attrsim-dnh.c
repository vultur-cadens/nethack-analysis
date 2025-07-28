/* Copyright 2022, 2025 vultur-cadens */

/* You may use, redistribute, or modify this file under the terms of
 * your choice of: NetHack General Public License; or GNU General
 * Public License, version 3 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "attr.h"

#define STR18(x) (18 + (x/5))  /* 18/xx */
#define STR19(x) (20 + (x)) /* For 19 and above */

struct race {
    char *name;
    unsigned char attrmin[A_MAX];
    unsigned char attrmax[A_MAX];
};

enum special_race {
    RACE_OTHER,
    RACE_INC,
    RACE_ELF,
};

struct role {
    char *name;
    unsigned char attrbase[A_MAX];
    unsigned char attrdist[A_MAX];
};

/* numbers from source file, src/role.c */
struct race races[] = {
    {
        "hum",
        { 3, 3, 3, 3, 3, 3 },
        { STR18(100), 18, 18, 18, 18, 18 },
    },
    {
        "clk",
        { 8, 8, 8, 8, 8, 8 },
        { STR18(100), 18, 18, 18, 18, 18 },
    },
    {
        "bat",
        { 3, 3, 3, 3, 3, 3 },
        { STR19(20), 16, 16, 20, 14, 16 },
    },
    {
        "elf",
        { 3, 3, 3, 3, 3, 3 },
        { 18, 20, 20, 18, 16, 18 },
    },
    {
        "dwa",
        { 3, 3, 3, 3, 3, 3 },
        { STR18(100), 16, 16, 20, 20, 16 },
    },
    {
        "dro",
        { 3, 3, 3, 3, 3, 3 },
        { 18, 20, 18, 20, 16, 20 },
    },
    {
        "gno",
        { 3, 3, 3, 3, 3, 3 },
        {STR18(50),19, 18, 18, 18, 18 },
    },
    {
        "hlf",
        { 3, 3, 3, 3, 3, 3 },
        { STR19(25),  20, 20, 10, 20, 20 },
    },
    {
        "inc",
        { 3, 3, 3, 3, 3, 3 },
        { STR18(100), 18, 18, 18, 18, 18 },
    },
    {
        "orc",
        { 3, 3, 3, 3, 3, 3 },
        { 18, 16, 16, 18, 18, 16 },
    },
    {
        "vam",
        { 3, 3, 3, 3, 3, 3 },
        { STR19(19), 18, 18, 20, 20, 20 },
    },
    {
        "swn",
        { 3, 3, 3, 3, 3, 3 },
        { 16, 18, 18, 20, 14, 20 },
    },
};

struct role roles[] = {
    {
        "arc",
        {   7, 10, 10,  7,  7,  7 },
        {  20, 20, 20, 10, 20, 10 },
    },
    {
        "ana",
        {  12, 10,  7, 10,  10,  7 },
        {  15, 17, 15, 12, 15, 15 },
    },
    {
        "bar",
        {  16,  7,  7, 15, 16,  6 },
        {  30,  6,  7, 20, 30,  7 },
    },
    {
        "bin",
        {  6,  6,  6,  6,  6,  6 },
        { 11,  9,  9, 11, 11,  9 },
    },
    {
        "cav",
        {  10,  7,  7,  7,  8,  6 },
        {  30,  6,  7, 20, 30,  7 },
    },
    {
        "con",
        {  10,  7,  7,  7, 13,  6 },
        {  20, 20, 10, 20, 20, 10 },
    },
    {
        "hea",
        {   7, 13, 11,  7, 11, 16 },
        {   5, 30, 20, 15, 25, 5 },
    },
    {
        "kni",
        {  13,  7, 14,  8, 10, 17 },
        {  30, 15, 15, 10, 20, 10 },
    },
    {
        "mon",
        {  10,  7,  8,  8,  7,  7 },
        {  25, 10, 20, 20, 15, 10 },
    },
    {
        "mad",
        {   7, 10, 3, 10,  7, 10 },
        {  10, 10, 3, 20, 20, 30 },
    },
    {
        "nob",
        {   10,10,  7, 10,  7,  7 },
        {  20, 18, 10, 20, 15, 17 },

    },
    {
        "pri",
        {   7,  7, 10,  7,  7,  7 },
        {  15, 10, 30, 15, 20, 10 },
    },
    {
        "pir",
        {  10,  7, 7,  10, 10,  7 },
        {  22, 15, 10, 22, 20, 10 },
    },
    {
        "rog",
        {   7,  7,  7, 10,  7,  6 },
        {  20, 10, 10, 30, 20, 10 },
    },
    {
        "ran",
        {  13, 13, 13,  9, 13,  7 },
        {  30, 10, 10, 20, 20, 10 },
    },
    {
        "sam",
        {  10,  8,  7, 10, 17,  6 },
        {  30, 10,  8, 30, 14,  8 },
    },
    {
        "tou",
        {   7, 10,  6,  7,  7, 10 },
        {  15, 10, 10, 15, 30, 20 },
    },
    {
        "brd",
        {   7,  7,  7, 10,  6, 10 },
        {  10, 10, 15, 25, 10, 30 },
    },
    {
        "hnt",
        {   7, 10, 10,  7,  7,  7 },
        {  18, 10, 10, 24, 18, 10 },
    },
    {
        "val",
        {  12,  10, 12, 10, 10, 12 },
        {  18,  14, 16, 18, 20, 14 },
    },
    {
        "wiz",
        {   7, 10,  7,  7,  7,  7 },
        {  10, 30, 10, 20, 20, 10 },
    },
};

#define min(a,b) (((a)<(b)) ? (a) : (b))

void
do_sim(double mean[A_MAX+1], double stdev[A_MAX+1], struct role *role,
       const unsigned char *attrmax, const unsigned char *attrmin,
       int points, int n, int special)
{
    int i;

    unsigned char (*result)[A_MAX+1] = malloc(n * sizeof *result);
    double sum[A_MAX+1] = {0};
    for (i = 0; i < n; i++) {
        init_attr(result[i], role->attrbase, role->attrdist,
                  attrmax, attrmin, points);
        /* special adjustment in dnh's init_attr() */
        switch (special) {
        case RACE_INC:
            int j;
            for (j = 0; j < A_MAX; j++) {
                if (result[i][A_INT] < result[i][j]) {
                    result[i][A_INT] = min(18, result[i][j]);
                }
            }
            break;
        case RACE_ELF:
            if (result[i][A_DEX] < result[i][A_STR]) {
                int d = result[i][A_DEX];
                result[i][A_DEX] = result[i][A_STR];
                result[i][A_STR] = d;
            }
            break;
        default:
            break;
        }
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

/* Example usage: attrsim-dnh -d wiz hum 10000000 */
int
main(int argc, char *argv[])
{
    size_t i;
    int descendant = 0;

    int opt;
    while ((opt = getopt(argc, argv, "d")) != -1) {
        switch (opt) {
        case 'd':
            descendant = 1;
            break;
        default:
            break;
        }
    }
    if (argc - optind != 3) {
        fprintf(stderr, "usage: %s [-d] role race n\n", argv[0]);
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
        fprintf(stderr, "option -d specifies descendant\n");
        return EXIT_FAILURE;
    }
    int n = atoi(argv[optind+2]);
    struct role *role = NULL;
    struct race *race = NULL;
    for (i = 0; i < (sizeof roles / sizeof *roles); i++) {
        if (!strcmp(argv[optind+0], roles[i].name)) {
            role = &roles[i];
        }
    }
    if (!role) {
        fprintf(stderr, "invalid role %s\n", argv[optind+0]);
        return EXIT_FAILURE;
    }
    for (i = 0; i < (sizeof races / sizeof *races); i++) {
        if (!strcmp(argv[optind+1], races[i].name)) {
            race = &races[i];
        }
    }
    if (!race) {
        fprintf(stderr, "invalid race %s\n", argv[optind+1]);
        return EXIT_FAILURE;
    }

    const unsigned char *attrmax, *attrmin;
    attrmax = race->attrmax;
    attrmin = race->attrmin;

    int points = 75;
    /* points adjustment from dnh u_init.c */
    if (!strcmp(role->name, "bin")) {
        points = (!strcmp(race->name, "elf")) ? 60 : 55;
    } else if (!strcmp(race->name, "orc")) {
        points = descendant ? 50 : 55;
    } else if (!strcmp(role->name, "val")) {
        points = descendant ? 75 : 85;
    } else if (!strcmp(race->name, "elf")) {
        points = descendant ? 70 : 80;
    } else {
        points = descendant ? 65 : 75;
    }

    /* special handling for some races in init_attr() */
    int special;
    if (!strcmp(race->name, "inc")) {
        special = RACE_INC;
    }
    if (!strcmp(race->name, "elf")) {
        special = RACE_ELF;
    }

    srand(time(NULL));

    double mean[A_MAX+1];
    double stdev[A_MAX+1];
    do_sim(mean, stdev, role, attrmax, attrmin, points, n, special);

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
