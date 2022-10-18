#ifndef COMPACTOR_H
#define COMPACTOR_H

#include <stdio.h>

#include "tree.h"

#define MAX_BIT_SIZE 16

typedef struct dict
{
    size_t len;
    char *chars;
    int *bitsizes;
    unsigned *bitfield;

    void (*init)(struct dict *self, const vtree _vtree, const vocc _vocc);
    void (*disp)(const struct dict *self);
} dict;

void dict_init(dict *self, const vtree _vtree, const vocc _vocc);
void dict_disp(const dict *self);

#endif