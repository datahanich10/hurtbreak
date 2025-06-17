#ifndef MEMFS_H
#define MEMFS_H

#include <stddef.h>
#include <time.h>

typedef enum
{
    NODE_DIR,
    NODE_FILE
} node_type_t;

typedef struct node
{
    node_type_t type;
    char *name;
    time_t mtime;
    struct node *next_sibling;
    struct node *parent;
} node_t;

typedef struct
{
    node_t base;
    size_t size;
    size_t capacity;
    unsigned char *buf;
} file_t;

typedef struct
{
    node_t base;
    node_t *first_child;
} dir_t;

dir_t *dir_create(const char *name, dir_t *parent);
file_t *file_create(const char *name, dir_t *parent, size_t initial_cap);
void node_destroy(node_t *node);
void dir_append_child(dir_t *dir, node_t *child);
size_t file_write(file_t *file, const void *src, size_t n);
size_t file_read(const file_t *file, void *dst, size_t n, size_t offset);
node_t *dir_find_child(const dir_t *dir, const char *name);

#endif
