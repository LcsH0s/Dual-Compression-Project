#include <stdio.h>
#include <stdlib.h>

#include "dict.h"

void dict_init(dict *self, const vtree _vtree, const vocc _vocc)
{
    self->disp = &dict_disp;
    self->save = &dict_save;

    self->len = (short)_vocc.len;
    self->chars = _vocc.chars;
    self->bitsizes = malloc(sizeof(short) * self->len);
    self->bitfield = malloc(sizeof(unsigned short) * self->len);

    tree *head = _vtree.list[0];
    tree *current = _vtree.list[0];
    tree *prev_tree = _vtree.list[0];

    int i = 0;
    unsigned short bit_value = 0;
    int depth = 0;

    while (i < self->len)
    {
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
                    bit_value = bit_value >> 1;
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
                bit_value = bit_value >> 1;
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
            self->bitsizes[self->len - i - 1] = depth;
            self->bitfield[self->len - i - 1] = bit_value;
            depth--;
            bit_value = bit_value >> 1;
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
    for (int i = self->len - 1; i >= 0; i--)
    {
        if (self->chars[i] != '\n')
        {
            printf("Char '%c' uses %d bits and has code : ", self->chars[i], self->bitsizes[i]);
        }
        else
        {
            printf("Char '\\n' uses %d bits and has code : ", self->bitsizes[i]);
        }
        for (int j = self->bitsizes[i] - 1; j >= 0; j--)
        {
            printf("%d", !!(self->bitfield[i] & (1u << j)));
        }
        printf("\n");
    }
}

void dict_save(const dict *self, FILE *f)
{
    fwrite(&self->len, sizeof(self->len), 1, f);

    for (int i = 0; i < self->len; i++)
        fwrite(&(self->bitsizes[i]), sizeof(short), 1, f);

    for (int i = 0; i < self->len; i++)
    {
        fwrite(&(self->chars[i]), sizeof(char), 1, f);
        fwrite(&(self->bitfield[i]), sizeof(unsigned short), 1, f);
    }
}

void dict_load(dict *self, FILE *f)
{
    short len;
    char *chars;
    short *bitsizes;
    unsigned short *bitfield;

    fread(&len, sizeof(len), 1, f);

    chars = malloc(sizeof(char) * len);
    bitsizes = malloc(sizeof(short) * len);
    bitfield = malloc(sizeof(unsigned short) * len);

    for (int i = 0; i < len; i++)
        fread(&(bitsizes[i]), sizeof(short), 1, f);

    for (int i = 0; i < len; i++)
    {
        fread(&(chars[i]), sizeof(char), 1, f);
        fread(&(bitfield[i]), sizeof(unsigned short), 1, f);
    }

    self->len = len;
    self->chars = chars;
    self->bitsizes = bitsizes;
    self->bitfield = bitfield;

    /*
        printf("Dict len: %d\n", len);
        printf("Dict total size: %d\n", len);

        for (int i = 0; i < len; i++)
        {
            printf("Char %c uses %d bits with code : ", chars[i], bitsizes[i]);
            for (int j = bitsizes[i] - 1; j >= 0; j--)
            {
                printf("%d", !!(bitfield[i] & (1u << j)));
            }
            printf("\n");
        }
    */
}