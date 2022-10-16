#include <stdio.h>
#include <stdlib.h>

#include "libs/helper.h"
#include "libs/tree.h"

int main(int argc, char **argv)
{
    struct args args = arg_parse(argc, argv);
    struct input input = get_input(args);

    if (args.mode == COMPRESS_MODE)
    {
        vocc occurences;
        occurences.init = &vocc_init;
        occurences.init(&occurences);

        occurences.compute(&occurences, input);

        vtree huff_tree;
        huff_tree.init = &vtree_init;
        huff_tree.init(&huff_tree, &occurences);
        huff_tree.compute(&huff_tree);
    }
    else
    {
        printf("EXTRACT_MODE still a WIP\n");
    }
}