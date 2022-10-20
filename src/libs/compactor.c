#include <stdio.h>
#include <stdlib.h>

#include "helper.h"
#include "dict.h"

void compress(const dict d, const struct input input, FILE *f)
{
    int dict_index = -1, b_count = 0;
    char bitvalue = 0;

    for (int i = 0; i < input.len; i++)
    {
        if (d.get_index(&d, input.str[i]) != -1)
        {
            dict_index = d.get_index(&d, input.str[i]);
            for (int j = 0; j < d.bitsizes[dict_index]; j++)
            {
                bitvalue <<= 1;
                if (d.bitfield[i] & (1 << j))
                    bitvalue++;

                b_count++;
                if (b_count == 8)
                {
                    b_count = 0;
                    fwrite(&bitvalue, sizeof(char), 1, f);
                    bitvalue = 0;
                }
            }
        }
        else
        {
            printf("An error occured while compressing the data. Aborting.\n");
            exit(1);
        }
    }
    fwrite(&bitvalue, sizeof(char), 1, f);
    fclose(f);
}

void decompress(const dict d, FILE *f)
{
}