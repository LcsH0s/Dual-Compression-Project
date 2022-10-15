#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "helper.h"

void tree_init(tree *self, char c)
{
    self->disp = &tree_disp;
    self->r = NULL;
    self->l = NULL;

    self->c = c;
}

void tree_disp(tree *self) // WIP : Not currently working
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

void vocc_init(vocc *self)
{
    self->chars = malloc(sizeof(char) * 100);
    self->n = malloc(sizeof(char) * 100);

    self->len = 0;

    self->compute = &vocc_compute;
    self->is_known = &vocc_is_known;
}

void vocc_append(vocc *self, char c)
{
    self->len = self->len + 1;
    char *tmp_chars = malloc(sizeof(char) * self->len);
    unsigned int *tmp_n = malloc(sizeof(unsigned int) * self->len);

    for (int i = 0; i < self->len - 1; i++)
    {
        tmp_chars[i] = self->chars[i];
        tmp_n[i] = self->n[i];
    }
    tmp_chars[self->len - 1] = c;
    tmp_n[self->len - 1] = 1;

    free(self->chars);
    free(self->n);

    self->chars = tmp_chars;
    self->n = tmp_n;
}

void vocc_compute(vocc *self, struct input input)
{
    for (int i = 0; i < input.len; i++)
    {
        printf("%c", input.str[i]);
    }
    printf("\nTest\n");
}

int vocc_is_known(const vocc *self, char c)
{
    for (int i = 0; i < self->len; i++)
    {
        if (self->chars[i] == c)
            return 1;
    }
    return 0;
}