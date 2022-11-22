#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "helper.h"

#pragma region VOcc // Occurences vector region

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
            self->append(self, input.str[i]);
        }
        else
        {
            self->n[self->get_index(self, input.str[i])]++;
        }
    }
    self->sort(self);
}

void vocc_disp(vocc *self)
{
    for (int i = 0; i < self->len; i++)
    {
        if (self->chars[i] == '\n')
        {
            printf("\\n appears %d times\n", self->n[i]);
        }
        else if (self->chars[i] == ' ')
        {
            printf("' ' appears %d times\n", self->n[i]);
        }
        else
        {
            printf("%c appears %d times\n", self->chars[i], self->n[i]);
        }
    }
}

#pragma endregion VOcc

#pragma region VTree // Tree vector region

void vtree_init(vtree *self, const vocc *occurences)
{
    self->list = malloc(sizeof(tree *) * occurences->len);
    self->len = occurences->len;
    self->sort = &vtree_sort;
    self->compute = &vtree_compute;

    for (int i = 0; i < occurences->len; i++)
    {
        self->list[i] = malloc(sizeof(tree));
        self->list[i]->c = occurences->chars[i];
        self->list[i]->in_dict = 0;
        self->list[i]->ltree = NULL;
        self->list[i]->rtree = NULL;
        self->list[i]->weight = occurences->n[i];
    }
}

void vtree_sort(vtree *self)
{
    tree *tmp;
    for (int i = 0; i < self->len - 1; i++)
    {
        for (int j = 0; j < self->len - 1 - i; j++)
        {
            if (self->list[j]->weight > self->list[j + 1]->weight)
            {
                tmp = self->list[j];
                self->list[j] = self->list[j + 1];
                self->list[j + 1] = tmp;
            }
        }
    }
}

void __tree_disp(tree *t)
{
    if (t->c != TREE_NO_CHAR)
    {
        if (t->c == '\n')
        {
            printf("\\n ");
        }
        else if (t->c == ' ')
        {
            printf("' ' ");
        }
        else
        {
            printf("%c ", t->c);
        }
        return;
    }
    else
    {
        __tree_disp(t->ltree);
        __tree_disp(t->rtree);
    }
}

void vtree_disp(const vtree *self)
{
    __tree_disp(self->list[0]);
    printf("\n");
}

void vtree_compute(vtree *self)
{
    while (self->len > 1)
    {
        tree *new_tree = malloc(sizeof(tree));

        new_tree->c = TREE_NO_CHAR;
        new_tree->in_dict = 0;
        new_tree->ltree = self->list[0];
        new_tree->rtree = self->list[1];
        new_tree->weight = self->list[0]->weight + self->list[1]->weight;

        for (int i = 1; i < self->len; i++)
        {
            self->list[i - 1] = self->list[i];
        }

        self->len--;
        self->list[0] = new_tree;
        self->sort(self);
    }
}

#pragma endregion VTree
