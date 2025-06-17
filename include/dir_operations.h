#ifndef DIROPERATION_H
#define DIROPERATION_H

#include "memfs.h"

void import_dir(const dir_t *src, dir_t *dest);
void hard_copy_dir(const dir_t *src, dir_t *dest);
void print_diff_dir(const dir_t *src, dir_t *dest, int depth);

#endif