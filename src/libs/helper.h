#ifndef HELPER_H
#define HELPER_H

#define EXTRACT_MODE 'e'
#define COMPRESS_MODE 'c'
#define STR_MODE 's'
#define FILE_MODE 'f'

struct args
{
    char mode;
    char input_mode;
    char *filepath;
    char *str;
};

struct args arg_parse(int argc, char **argv);

#endif