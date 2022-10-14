#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "helper.h"

void show_help()
{
    printf("usage: huffmaninator [-cx] [-s \"string\"] [-f filepath]\n");
}

struct args arg_parse(int argc, char **argv)
{
    int c;
    struct args args = {0, NULL, NULL};

    while ((c = getopt(argc, argv, "edf:s:")) != -1)
    {
        switch (c)
        {
        case 'x':
            args.mode = EXTRACT_MODE;
            break;
        case 'c':
            args.mode = COMPRESS_MODE;
            break;
        case 'f':
            args.input_mode = FILE_MODE;
            args.filepath = optarg;
            break;
        case 's':
            args.input_mode = STR_MODE;
            args.str = optarg;
            break;
        case 'h':
            show_help();
            exit(0);
        default:
            abort();
        }
    }

    return args;
}
