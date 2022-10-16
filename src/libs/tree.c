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
    self->get_index = &vocc_get_index_of_char;
    self->sort = &vocc_sort;
    self->append = &vocc_append;
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

int vocc_get_index_of_char(const vocc *self, char c)
{
    for (int i = 0; i < self->len; i++)
    {
        if (self->chars[i] == c)
            return i;
    }
    return -1;
}

void vocc_sort(vocc *self)
{
    int n_tmp;
    char c_tmp;
    for (int i = 0; i < self->len - 1; i++)
    {
        for (int j = 0; j < self->len - 1 - i; j++)
        {
            if (self->n[j] > self->n[j + 1])
            {
                n_tmp = self->n[j];
                self->n[j] = self->n[j + 1];
                self->n[j + 1] = n_tmp;

                c_tmp = self->chars[j];
                self->chars[j] = self->chars[j + 1];
                self->chars[j + 1] = c_tmp;
            }
        }
    }
}

void vocc_compute(vocc *self, struct input input)
{
    for (int i = 0; i < input.len; i++)
    {
        if (self->get_index(self, input.str[i]) == -1)
        {
            printf("Char '%c'is not known yet. Adding it to occurences array\n", input.str[i]);
            self->append(self, input.str[i]);
        }
        else
        {
            printf("'%c' already known\n", input.str[i]);
            self->n[self->get_index(self, input.str[i])]++;
        }
    }
    self->sort(self);

    printf("\nOccurences are : \n");

    for (int i = 0; i < self->len; i++)
    {
        printf("'%c' appeared %d times\n", self->chars[i], self->n[i]);
    }
}