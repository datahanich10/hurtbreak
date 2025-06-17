#ifndef MEMFSEXTENDED_H
#define MEMFSEXTENDED_H

#include "memfs.h"

void copy_file(dir_t* dir, const file_t* file);
void copy_dir(dir_t* dir, const dir_t* dir_to_copy);

#endif