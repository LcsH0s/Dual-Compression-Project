#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "helper.h"

void show_help()
{
    printf("usage: huffmaninator [-cx] [-s \"string\"] [-f filepath]\n");
    printf("Mode :\n"
           "    -c                     compresser\n"
           "    -x                     extraire\n"
           "\nInput :\n"
           "    -f [filepath]          utiliser le fichier de configuration du dépôt\n"
           "    -s \"[string]\"        utiliser un fichier de configuration par arbre de travail\n");
}

struct args arg_parse(int argc, char **argv)
{
    int c;
    struct args args = {COMPRESS_MODE, 0, NULL, NULL};

    if (argc == 1)
    {
        printf("usage: huffmaninator [-cx] [-s \"string\"] [-f filepath] -> Use -h for help\n");
        exit(0);
    }

    while ((c = getopt(argc, argv, "cxhf:s:")) != -1)
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
    if (args.input_mode == 0)
    {
        printf("No input specified. Use -h for help.\n");
        printf("usage: huffmaninator [-cx] [-s \"string\"] [-f filepath]\n");
        exit(0);
    }
    return args;
}

struct input get_input(struct args args)
{
    struct input r;
    if (args.input_mode == STR_MODE)
    {
        r.len = strlen(args.str);
        r.str = malloc(sizeof(char) * r.len);
        strcpy(r.str, args.str);
        return r;
    }
    else if (access(args.filepath, F_OK) == 0)
    {
        FILE *input_file = fopen(args.filepath, "rb");
        if (input_file)
        {
            fseek(input_file, 0, SEEK_END);
            r.len = ftell(input_file);
            fseek(input_file, 0, SEEK_SET);
            r.str = malloc(r.len);
            if (r.str)
            {
                fread(r.str, 1, r.len, input_file);
            }
            fclose(input_file);
            return r;
        }
    }
    else
    {
        printf("ERROR: Unable to access file: %s\n", args.filepath);
        exit(-1);
    }
}
