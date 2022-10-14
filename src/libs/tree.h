#ifndef TREE_H
#define TREE_H

typedef struct tree
{
    char c;
    struct tree *l;
    struct tree *r;

    void (*init)(struct tree *self);
    void (*disp)(struct tree *self);
} tree;

void tree_init(tree *self, char c);
void tree_disp(tree *self);

#endif