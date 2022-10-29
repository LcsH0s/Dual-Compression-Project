#ifndef COMPACTOR_H
#define COMPACTOR_H

void compress(const dict d, const struct input i, FILE *f);
void decompress(const dict *d, FILE *f_in, FILE *f_out);

#endif