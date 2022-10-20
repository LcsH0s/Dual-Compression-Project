#ifndef TREE_H
#define TREE_H

#include "helper.h"

#define TREE_NO_CHAR -1

typedef struct vocc // Vector containing the occurences class
{
    unsigned int *n;
    char *chars;
    size_t len;

    void (*init)(struct vocc *self);
    void (*compute)(struct vocc *self, struct input input);
    void (*append)(struct vocc *self, char c);
    void (*sort)(struct vocc *self);

    int (*get_index)(const struct vocc *self, char c);
} vocc;

typedef struct tree // Huffman tree class
{
    char c;
    int weight;
    char in_dict;
    struct tree *ltree;
    struct tree *rtree;
} tree;

typedef struct vtree
{
    tree **list;
    size_t len;

    void (*init)(struct vtree *self, const vocc *occurences);
    void (*sort)(struct vtree *self);
    void (*compute)(struct vtree *self);
} vtree;

// vector of occurences class methods
void vocc_init(vocc *self);
void vocc_append(vocc *self, char c);
void vocc_sort(vocc *self);
void vocc_disp(vocc *self);
void vocc_compute(vocc *self, struct input input);
int vocc_get_index_of_char(const vocc *self, char c);

// vtree class methods
void vtree_init(vtree *self, const vocc *occurences);
void vtree_sort(vtree *self);
void vtree_compute(vtree *self);

#endif