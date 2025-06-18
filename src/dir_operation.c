#include "dir_operations.h"

void copy_file(dir_t *dir, const file_t *file_original)
/**
 * @brief Creates an exact copy of file and adds the copy to dir
 * @param dir Directory to which we will copy the file
 * @param file_original File that we want to copy
 * @return None
 */
{
    if(dir_find_child(dir, file_original->base.name))    // cannot copy file if the name is taken
        return;
    
    char* copy_name = (char*)malloc(sizeof(file_original->base.name));
    memcpy(copy_name, file_original->base.name ,sizeof(file_original->base.name));
    file_t *copy = file_create(copy_name, dir, file_original->capacity);
    copy->base.mtime = file_original->base.mtime;
    char* data = (char *)malloc(file_original->size * sizeof(char));
    file_read(file_original, data, file_original->size, 0);
    file_write(copy, data, file_original->size);
    dir_append_child(dir, copy);
}

void copy_dir(dir_t *dir, const dir_t* dir_original)
{
    if(dir_find_child(dir, dir_original->base.name))    // cannot copy file if the name is taken
        return;
    
    char* copy_name = (char*)malloc(sizeof(dir_original->base.name));
    memcpy(copy_name, dir_original->base.name ,sizeof(dir_original->base.name));
    dir_t *copy = dir_create(copy_name, dir);
    copy->base.mtime = dir_original->base.mtime;
    for (const node_t *n = dir_original->first_child; n; n = n->next_sibling)
    {
        if(n->type == NODE_FILE)
            copy_file(copy, (file_t *)n);
        else
            copy_dir(copy, (dir_t *)n);
    }
    dir_append_child(dir, copy);
}



void import_dir(const dir_t *src, dir_t *dest)
{
    return;
}