#include "treegen.h"
#include <string.h>

dir_t *create_source_tree(void)
{
    dir_t *root = dir_create("ex_girlfriend_texts", NULL);

    dir_t *screenshots = dir_create("screenshots", root);
    dir_t *voice_notes = dir_create("voice_notes", root);
    dir_t *memes = dir_create("memes", root);

    dir_append_child(root, (node_t *)screenshots);
    dir_append_child(root, (node_t *)voice_notes);
    dir_append_child(root, (node_t *)memes);

    file_t *chat_png = file_create("chat_2020‑02‑14.png", screenshots, 64);
    dir_append_child(screenshots, (node_t *)chat_png);
    file_write(chat_png,
               "BinaryStuff…(pretend PNG data of an awkward chat)\n",
               46);

    file_t *voicenote = file_create("drunk_apology.wav", voice_notes, 128);
    dir_append_child(voice_notes, (node_t *)voicenote);
    file_write(voicenote,
               "WAVDATA…(slurred apology: \"I miss uuu\")\n",
               43);

    file_t *meme_txt = file_create("breakup_meme.txt", memes, 128);
    dir_append_child(memes, (node_t *)meme_txt);
    file_write(meme_txt,
               "Top text: IT'S FINE\nBottom text: I'M FINE (everything's on "
               "fire)\n",
               72);

    file_t *poem = file_create("cringe_poem.txt", root, 64);
    file_t *todo = file_create("todo.txt", root, 32);
    dir_append_child(root, (node_t *)poem);
    dir_append_child(root, (node_t *)todo);

    file_write(poem,
               "Roses are red, violets are blue,\nWhy'd you unmatch me, what "
               "did I do?\n",
               86);
    file_write(todo,
               "- Delete poem before anyone sees it\n- Actually maybe keep "
               "it for character growth\n",
               100);

    return root;
}

dir_t *create_dest_tree(void)
{
    dir_t *root = dir_create("emotional_backup", NULL);

    /* Only a subset exists here (simulates stale backup) */
    dir_t *memes = dir_create("memes", root);
    dir_append_child(root, (node_t *)memes);

    file_t *old_meme = file_create("breakup_meme.txt", memes, 64);
    dir_append_child(memes, (node_t *)old_meme);
    file_write(old_meme,
               "Top text: I MOVED ON\nBottom text: (lol jk send help)\n",
               53);

    file_t *poem_old = file_create("cringe_poem.txt", root, 64);
    dir_append_child(root, (node_t *)poem_old);
    file_write(poem_old,
               "Original 2019 edition: still bad poetry.\n",
               43);

    return root;
}
