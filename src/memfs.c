#include "memfs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

dir_t *dir_create(const char *name, dir_t *parent)
{
    dir_t *dir = malloc(sizeof(dir_t));
    if (!dir)
        return NULL;
    dir->base.type = NODE_DIR;
    dir->base.name = strdup(name);
    dir->base.mtime = time(NULL);
    dir->base.parent = (node_t *)parent;
    dir->base.next_sibling = NULL;
    dir->first_child = NULL;
    return dir;
}

file_t *file_create(const char *name, dir_t *parent, size_t initial_cap)
{
    file_t *file = malloc(sizeof(file_t));
    if (!file)
        return NULL;
    file->base.type = NODE_FILE;
    file->base.name = strdup(name);
    file->base.mtime = time(NULL);
    file->base.parent = (node_t *)parent;
    file->base.next_sibling = NULL;
    file->size = 0;
    file->capacity = initial_cap;
    file->buf = malloc(initial_cap);
    return file;
}

void node_destroy(node_t *node)
{
    if (!node)
        return;

    if (node->type == NODE_DIR)
    {
        dir_t *dir = (dir_t *)node;
        node_t *child = dir->first_child;
        while (child)
        {
            node_t *next = child->next_sibling;
            node_destroy(child);
            child = next;
        }
    }
    else if (node->type == NODE_FILE)
    {
        file_t *file = (file_t *)node;
        free(file->buf);
    }

    free(node->name);
    free(node);
}

void dir_append_child(dir_t *dir, node_t *child)
{
    if (!dir->first_child)
    {
        dir->first_child = child;
    }
    else
    {
        node_t *curr = dir->first_child;
        while (curr->next_sibling)
            curr = curr->next_sibling;
        curr->next_sibling = child;
    }
    child->parent = (node_t *)dir;
}

size_t file_write(file_t *file, const void *src, size_t n)
{
    if (file->size + n > file->capacity)
    {
        size_t new_cap = file->capacity * 2;
        while (new_cap < file->size + n)
            new_cap *= 2;
        unsigned char *new_buf = realloc(file->buf, new_cap);
        if (!new_buf)
            return 0;
        file->buf = new_buf;
        file->capacity = new_cap;
    }

    memcpy(file->buf + file->size, src, n);
    file->size += n;
    file->base.mtime = time(NULL);
    return n;
}

size_t file_read(const file_t *file, void *dst, size_t n, size_t offset)
{
    if (offset >= file->size)
        return 0;
    size_t to_read = (offset + n > file->size) ? (file->size - offset) : n;
    memcpy(dst, file->buf + offset, to_read);
    return to_read;
}

node_t * dir_find_child(const dir_t *dir, const char *name)
{
    node_t *curr = dir->first_child;
    while (curr)
    {
        if (strcmp(curr->name, name) == 0)
            return curr;
        curr = curr->next_sibling;
    }
    return NULL;
}
