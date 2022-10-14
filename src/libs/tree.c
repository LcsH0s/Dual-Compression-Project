#include <stdio.h>

#include "tree.h"

void tree_init(tree *self, char c)
{
    self->disp = &tree_disp;
    self->r = NULL;
    self->l = NULL;

    self->c = c;
}

void tree_disp(tree *self)
{
    tree *c_tree = self;
    tree *bak_tree = self;

    printf("%c ", self->c);
    while (!(c_tree->l == NULL & c_tree->r == NULL))
    {
        if (c_tree->l == NULL)
        {
            c_tree = c_tree->r;
            printf("%c ", c_tree->c);
        }
        else if (c_tree->r != NULL)
        {
            bak_tree = c_tree;
            c_tree = c_tree->l;
            printf("%c ", c_tree->c);
        }
        else
        {
            c_tree = c_tree->r;
            printf("%c ", c_tree->c);
        }
        if (c_tree->l == NULL & c_tree->r == NULL)
        {
            c_tree = bak_tree;
        }
    }
}
