#ifndef TREEGEN_H
#define TREEGEN_H

#include "memfs.h"

/* Create a fake source directory tree */
dir_t *create_source_tree(void);

/* Create a fake destination directory tree */
dir_t *create_dest_tree(void);

#endif
