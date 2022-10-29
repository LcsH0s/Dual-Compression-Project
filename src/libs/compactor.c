#include <stdio.h>
#include <stdlib.h>

#include "helper.h"
#include "dict.h"

void compress(const dict d, const struct input input, FILE *f)
{
    char buffer;
    int b_count = 0;
    int dict_index;

    fwrite(&input.len, sizeof(input.len), 1, f);

    for (int i = 0; i < input.len; i++)
    {
        dict_index = d.get_index(&d, input.str[i]);
        for (int j = d.bitsizes[dict_index] - 1; j >= 0; j--)
        {
            buffer <<= 1;
            if (!!(d.bitfield[dict_index] & (1u << j)))
            {
                buffer++;
            }
            b_count++;

            if (b_count == 8)
            {
                b_count = 0;
                fputc(buffer, f);
                buffer = 0;
            }
        }
    }
    fputc(buffer, f);
    fclose(f);
}

void decompress(const dict *d, FILE *f_in, FILE *f_out)
{
    char buffer;
    char c;
    unsigned int bitvalue = 0;
    long len;
    int char_count = 0;

    fread(&len, sizeof(len), 1, f_in);

    while (1)
    {
        fread(&buffer, sizeof(buffer), 1, f_in);

        for (int i = 7; i >= 0; i--)
        {
            bitvalue <<= 1;
            if (!!(buffer & (1u << i)))
            {
                bitvalue++;
            }

            c = d->get_char_with_code(d, bitvalue);

            if (c != INVALID_CHAR_CODE)
            {
                printf("%c ", c);
                fputc(c, f_out);
                char_count++;
                if (char_count >= len)
                    return;
                bitvalue = 0;
            }
        }
    }
}
