#include <stdio.h>
#include <stdlib.h>

#include "libs/helper.h"
#include "libs/tree.h"

int main(int argc, char **argv)
{

    struct args args = arg_parse(argc, argv);
    struct input input = get_input(args);

    vocc occurences;
    occurences.init = &vocc_init;
    occurences.init(&occurences);

    occurences.compute(&occurences, input);

    tree huff_tree;
    huff_tree.init = &tree_init;
    huff_tree.init(&huff_tree, 'a');
}
