#include <stdio.h>
#include <stdlib.h>

#include "helper.h"
#include "dict.h"

void compress(const dict d, const struct input input, FILE *f)
{
    fwrite(&input.len, sizeof(input.len), 1, f);

    char buffer = 0;
    char b_count = 0;
    int dict_index;

    for (int i = 0; i < input.len; i++)
    {
        dict_index = d.get_index(&d, input.str[i]);
        // printf("Char n°%d with code : ", i);
        // disp_bin_form(d.bitfield[dict_index], d.bitsizes[dict_index]);

        for (int b = d.bitsizes[dict_index] - 1; b >= 0; b--)
        {
            buffer <<= 1;
            if ((d.bitfield[dict_index]) & (1u << b))
                buffer++;
            b_count++;
            if (b_count == 8)
            {
                printf("Buffer biform is :");
                for (int x = 7; x >= 0; x--)
                    printf("%d ", !!(buffer & (1u << x)));
                printf("\n");

                fwrite(&buffer, sizeof(buffer), 1, f);
                b_count = 0;
                buffer = 0;
            }
        }
        fwrite(&buffer, sizeof(buffer), 1, f);
    }
    fclose(f);
}

void decompress(const dict *d, FILE *f)
{
    unsigned short bitvalue = 0;
    long int char_count = 0;
    char buffer;
    char c;
    long len;
    int count = 2;

    fread(&len, sizeof(len), 1, f);

    while (fread(&buffer, 1, 1, f) == 1)
    {

        if (count % 5 == 0)
        {
            printf("Buffer biform is :");
            for (int x = 7; x >= 0; x--)
                printf("%d ", !!(buffer & (1u << x)));
            printf("\n");

            for (int i = 0; i < 8; i++)
            {
                bitvalue <<= 1;
                if (buffer & (1u << i))
                    bitvalue++;

                c = d->get_char_with_code(d, bitvalue);
                if (c != INVALID_CHAR_CODE)
                {
                    printf("%c\n", c);
                    bitvalue = 0;
                    char_count++;
                }
            }
            count++;
        }
        else
        {
            count++;
        }
    }
}
