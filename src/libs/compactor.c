#include <stdio.h>
#include <stdlib.h>

#include "compactor.h"

void dict_init(dict *self, const vtree _vtree, const vocc _vocc)
{
    // printf("bit 2 = %d\n", !!(a & (1u << 1)));
    self->disp = &dict_disp;

    self->len = _vocc.len;
    self->chars = _vocc.chars;
    self->bitsizes = malloc(sizeof(size_t) * self->len);
    self->bitfield = malloc(sizeof(unsigned) * self->len);

    tree *head = _vtree.list[0];
    tree *current = _vtree.list[0];
    tree *prev_tree = _vtree.list[0];

    int i = 0;
    unsigned bit_value = 0;
    int depth = 0;

    while (i < self->len)
    {
        /*
                printf("depth : %d\n", depth);
                printf("i : %d\n", i);
                printf("len : %lu\n", self->len);

                printf("(current->ltree == NULL) = %d\n", (current->ltree == NULL));
                printf("(current->rtree == NULL) = %d\n", (current->rtree == NULL));
                printf("(current == head) = %d\n", (current == head));
                printf("(current->c == TREE_NO_CHAR) = %d\n", (current->c == TREE_NO_CHAR));
                printf("(current->ltree->in_dict) = %d\n", (current->ltree->in_dict));
                printf("(current->rtree->in_dict) = %d\n", (current->rtree->in_dict));
        */
        if (current->ltree != NULL)
        {
            if (current->ltree->in_dict == 0)
            {
                prev_tree = current;
                current = current->ltree;
                depth++;
                bit_value = bit_value << 1;
            }
            else if (current->rtree != NULL)
            {
                if (current->rtree->in_dict == 0)
                {
                    prev_tree = current;
                    current = current->rtree;
                    depth++;
                    bit_value = bit_value << 1;
                    bit_value = bit_value + 0b1;
                }
                else if (depth > 0)
                {
                    current->in_dict = 1;
                    current = prev_tree;
                    depth--;
                    bit_value >> 1;
                }
                else
                {
                    current->in_dict = 1;
                    current = head;
                    depth = 0;
                    bit_value = 0;
                }
            }
        }

        else if (current->rtree != NULL)
        {
            if (current->rtree->in_dict == 0)
            {
                prev_tree = current;
                current = current->rtree;
                depth++;
                bit_value = bit_value << 1;
                bit_value = bit_value + 0b1;
            }
            else if (depth > 0)
            {
                current->in_dict = 1;
                current = prev_tree;
                bit_value >> 1;
                depth--;
            }
            else
            {
                current->in_dict = 1;
                current = head;
                depth = 0;
                bit_value = 0;
            }
        }
        if ((current->c != TREE_NO_CHAR) & (current->in_dict == 0))
        {
            current->in_dict = 1;
            self->bitsizes[i] = depth;
            self->bitfield[i] = bit_value;
            depth--;
            bit_value >> 1;
            current = prev_tree;
            i++;
        }
        if ((current->rtree == NULL) & (current->ltree == NULL))
        {
            current->in_dict = 0;
            current = prev_tree;
            depth--;
            bit_value = bit_value >> 1;
        }
    }
    dict_disp(self);
}

void dict_disp(const dict *self)
{
    for (int i = 0; i < self->len; i++)
    {
        if (self->chars[i] != '\n')
        {
            printf("Char '%c' uses %d bits and has code : ", self->chars[i], self->bitsizes[self->len - i - 1]);
        }
        else
        {
            printf("Char '\\n' uses %d bits and has code : ", self->bitsizes[self->len - i - 1]);
        }
        for (int j = self->bitsizes[self->len - i - 1] - 1; j >= 0; j--)
        {
            printf("%d", !!(self->bitfield[self->len - i - 1] & (1u << j)));
        }
        printf("\n");
    }
}