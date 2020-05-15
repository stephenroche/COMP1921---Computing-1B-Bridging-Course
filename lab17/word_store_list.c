#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word_store.h"

struct word_counter {
    int                 n_words;   // number of words stored
    struct list_node    *list;     // list containing word counts
};

struct list_node {
    char                *word;
    int                 count;
    struct list_node    *next;
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
    wc->list = NULL;
    return wc;
}

/*
 * search a linked list for a word
 * return NULL if not in list
 */
struct list_node *find_word(struct list_node *list, char *word) {
    struct list_node *v;
    for (v = list; v != NULL; v = v->next) {
        if (strcmp(word, v->word) == 0) {
            return v;
        }
    }
    return NULL;
}

/*
 * increment the count for a word
 */
void increment_word_count(word_counter *wc, char *word) {
    struct list_node *v = find_word(wc->list, word);
    if (v != NULL) {
        // increment count of existing word
        v->count++;
        return;
    }
    // new word
    v = salloc(sizeof *v);
    v->word = strdup(word);
    if (v->word == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    v->count = 1;
    v->next = wc->list;
    wc->list = v;
    wc->n_words++;
}

/*
 * get the count for a word
 */
int get_word_count(word_counter *wc, char *word) {
    struct list_node *v = find_word(wc->list, word);
    if (v == NULL) {
        return 0;
    }
    return v->count;
}

/*
 * get a malloc'ed array containing
 * all the words for which counts are stored
 * n_words set to size of array
 */
char **get_word_array(word_counter *wc, int *n_words) {
    struct list_node *v;
    int  i;
    char **word_array = salloc(wc->n_words*sizeof *word_array);
    for (v = wc->list, i=0; v != NULL; v = v->next,i++)
        word_array[i] = v->word;
    *n_words = wc->n_words;
    return word_array;
}

/*
 * free a linked list
 */
void free_list_nodes(struct list_node  *list) {
    if (list == NULL)
        return;
    free_list_nodes(list->next);
    free(list);
}

/*
 * free a word counter data structure
 */
void free_word_counter(word_counter *wc) {
    free_list_nodes(wc->list);
    free(wc);
}

