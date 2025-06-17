#include <stdio.h>
#include <assert.h>
#include "memfs.h"
#include "treegen.h"

void print_tree(const dir_t *dir, int depth)
{
    for (const node_t *n = dir->first_child; n; n = n->next_sibling)
    {
        for (int i = 0; i < depth; i++)
            printf("  ");
        printf("• %s", n->name);
        if (n->type == NODE_FILE)
            printf(" [file]");
        else
            printf(" [dir]");
        printf("\n");

        if (n->type == NODE_DIR)
            print_tree((const dir_t *)n, depth + 1);
    }
}

int main(void)
{
    dir_t *src = create_source_tree();
    dir_t *dst = create_dest_tree();

    printf("=== ex_girlfriend_texts (source) ===\n");
    print_tree(src, 0);

    printf("\n=== emotional_backup (dest) ===\n");
    print_tree(dst, 0);

    node_destroy((node_t *)src);
    node_destroy((node_t *)dst);

    return 0;
}
