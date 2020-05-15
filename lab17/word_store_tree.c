#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word_store.h"

struct word_counter {
    int                 n_words;   // number of words stored
    struct tree_node    *tree;     // tree containing word counts
};

struct tree_node {
    char                *word;
    int                 count;
    struct tree_node    *left;
    struct tree_node    *right;
};

/*
 * call malloc, exit if it fails
 */
void *salloc(size_t n) {
    void *p = malloc(n);
    if (p == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    return p;
}

/*
 * create a word counter data structure
 */
word_counter *create_word_counter(void) {
    struct word_counter *wc;
    wc = salloc(sizeof *wc);
    wc->n_words = 0;
    wc->tree = NULL;
    return wc;
}

/*
 * search a tree for a word
 * return NULL if not in tree
 */
struct tree_node *find_word(struct tree_node *t, char *word) {
    struct tree_node *foundWord = NULL;

    if (t == NULL) {

    } else if (strcmp(t->word, word) == 0) {
        foundWord = t;

    } else if (strcmp(word, t->word) < 0) {
        foundWord = find_word(t->left, word);

    } else if (strcmp(word, t->word) > 0) {
        foundWord = find_word(t->right, word);
    }

    return foundWord;
}

/*
 * insert a new node into a tree
 */
void insert_tree_node(struct tree_node *t, struct tree_node *new) {
    if (strcmp(new->word, t->word) < 0) {
        if (t->left == NULL) {
            t->left = new;
        } else {
            insert_tree_node(t->left, new);
        }
    } else {
        if (t->right == NULL) {
            t->right = new;
        } else {
            insert_tree_node(t->right, new);
        }
    }
}

/*
 * increment the count for a word
 */
void increment_word_count(word_counter *wc, char *word) {
    struct tree_node *t = find_word(wc->tree, word);
    if (t != NULL) {
        // increment count of existing word
        t->count++;
    } else {
        // new word
        struct tree_node *new = salloc(sizeof *t);
        new->word = strdup(word);
        new->count = 1;
        new->left = NULL;
        new->right = NULL;
        if (wc->tree == NULL) {
            wc->tree = new;
        } else {
            insert_tree_node(wc->tree, new);
        }
        wc->n_words++;
    }
}

/*
 * get the count for a word
 */
int get_word_count(word_counter *wc, char *word) {
    struct tree_node *t = find_word(wc->tree, word);
    if (t == NULL) {
        return 0;
    }
    return t->count;
}

// copy pointers to words in tree t
// into array word_array
// starting at index
// return last index used
int tree_to_array(struct tree_node *t, char **word_array, int index) {
    int lastIndex;

    if (t == NULL) {
        lastIndex = index-1;
    } else {
        word_array[index] = strdup(t->word);

        lastIndex = tree_to_array(t->left, word_array, index+1);
        lastIndex = tree_to_array(t->right, word_array, lastIndex+1);
    }
    return lastIndex;
}
/*
 * get a malloc'ed array containing
 * all the words for which counts are stored
 * n_words set to size of array
 */
char **get_word_array(word_counter *wc, int *n_words) {
    char **word_array = salloc(wc->n_words*sizeof *word_array);
    tree_to_array(wc->tree, word_array, 0);
    *n_words = wc->n_words;
    return word_array;
}

/*
 * free a binary tree
 */
void free_tree_nodes(struct tree_node  *tree) {
    if (tree != NULL) {
        free_tree_nodes(tree->left);
        free_tree_nodes(tree->right);
        free(tree);
    }
}

/*
 * free a word counter data structure
 */
void free_word_counter(word_counter *wc) {
    free_tree_nodes(wc->tree);
    free(wc);
}

