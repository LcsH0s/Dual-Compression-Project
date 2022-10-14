#include <stdio.h>
#include <stdlib.h>

#include "libs/helper.h"
#include "libs/tree.h"

int main(int argc, char **argv)
{

    struct args args = arg_parse(argc, argv);
    // printf("The mode is %c\nThe filepath is : %s\nThe string is : %s\n", args.mode, args.filepath, args.str);

    tree huff_tree;
    huff_tree.init = &tree_init;
    huff_tree.init(&huff_tree);
}
