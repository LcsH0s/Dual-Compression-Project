#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "helper.h"

struct args arg_parse(int argc, char **argv)
{
    int c;
    struct args args = {0, NULL, NULL};

    if ((c = getopt(argc, argv, "f:s:")) != -1)
    {
        switch (c)
        {
        case 'f':
            args.mode = FILE_MODE;
            args.filepath = optarg;
            break;
        case 's':
            args.mode = STR_MODE;
            args.str = optarg;
            break;
        default:
            abort();
        }
    }
    else
    {
        printf("No arguments specified");
        exit(-1);
    }
    return args;
}
