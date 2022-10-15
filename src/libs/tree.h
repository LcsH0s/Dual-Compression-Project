#ifndef TREE_H
#define TREE_H

#include "helper.h"

typedef struct tree // Huffman tree class
{
    char c;
    struct tree *l;
    struct tree *r;

    void (*init)(struct tree *self, char c);
    void (*disp)(struct tree *self);
} tree;

typedef struct vocc // Vector containing the occurences class
{
    unsigned int *n;
    char *chars;

    size_t len;

    void (*init)(struct vocc *self);
    void (*compute)(struct vocc *self, struct input input);
    int (*is_known)(const struct vocc *self, char c);
} vocc;

// tree class methods
void tree_init(tree *self, char c);
void tree_disp(tree *self);

// vector of occurences class methods
void vocc_init(vocc *self);
void vocc_compute(vocc *self, struct input input);
int vocc_is_known(const vocc *self, char c);

#endif