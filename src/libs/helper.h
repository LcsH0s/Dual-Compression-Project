#ifndef HELPER_H
#define HELPER_H

#include <uuid/uuid.h>

#define EXTRACT_MODE 'e'
#define COMPRESS_MODE 'c'
#define STR_MODE 's'
#define FILE_MODE 'f'
#define DEFAULT_DEST "archive.hca" // .hca = Huffmann Compressed Archive

typedef struct Object
{
    uuid_t uuid;
    int (*Object_init)(struct Object *self);
    int (*Object_clean)(struct Object *self);
} Object;

struct args
{
    char mode;
    char input_mode;
    char *filepath;
    char *str;
    char *dest;
};

struct input
{
    char *str;
    long int len;
};

// Objects methods
int Object_init(Object *self);
int Object_clean(Object *self);

// Helper functions
struct args arg_parse(int argc, char **argv);
struct input get_input(struct args args);
FILE *input_file_init(struct args args);
FILE *output_file_init(struct args args);
void disp_bin_form(unsigned short bitvalue, size_t s);

#endif