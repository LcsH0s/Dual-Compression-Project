#ifndef DICT_H
#define DICT_H

#include <stdio.h>

#include "tree.h"

#define INVALID_CHAR_CODE -1

typedef struct dict
{
    short len;
    char *chars;
    short *bitsizes;
    short unsigned *bitfield;

    void (*init)(struct dict *self, const vtree _vtree, const vocc _vocc);
    void (*disp)(const struct dict *self);
    void (*save)(const struct dict *self, FILE *f);
    void (*load)(struct dict *self, FILE *f);
    int (*get_index)(const struct dict *self, char c);
    char (*get_char_with_code)(const struct dict *self, unsigned short bitvalue);
} dict;

void dict_init(dict *self, const vtree _vtree, const vocc _vocc);
void dict_disp(const dict *self);
void dict_save(const dict *self, FILE *f);
void dict_load(dict *self, FILE *f);
int get_index_of_char(const dict *self, char c);
char get_char_with_code(const dict *self, unsigned short bitvalue);

#endif