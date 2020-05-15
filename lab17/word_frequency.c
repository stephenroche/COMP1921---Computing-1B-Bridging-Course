#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "word_store.h"

char *get_word(FILE *stream);
word_counter *read_words(FILE *stream);
int frequency_cmp(const void *p1, const void *p2);
int pstrcmp(const void *p1, const void *p2);

// a global variable used so word_count available
// in frequency_cmp function
// Unfortunately C doesn't have closures

word_counter *wc;

int
main(int argc, char *argv[]) {
    int i, n_words;
    wc = read_words(stdin);
    char **word_array = (char **)get_word_array(wc, &n_words);
    if (argc > 1) {
        qsort(word_array, n_words, sizeof *word_array, frequency_cmp);
    } else {
        qsort(word_array, n_words, sizeof *word_array, pstrcmp);
    }
    for (i = 0; i < n_words; i++) {
        char *word = word_array[i];
        int count = get_word_count(wc, word);
        printf("%5d %s\n", count, word);
    }
    return 0;
}

/*
 * read the words from a stream
 * and return a data structure containing
 * the number of time each word occurred
 */
word_counter *read_words(FILE *stream) {
    word_counter *wc;

    wc = create_word_counter();
    while (1) {
        char *word = get_word(stdin);
        if (word == NULL)
            return wc;
        increment_word_count(wc, word);
        free(word);
    }
}

/*
 * returns the next word from the stream
 * a word is a non-zero length sequence of
 * alphabetic characters
 *
 * NULL is returned if there are no more words to be read
 */
char *get_word(FILE *stream) {
    int i, c;
    char *w;
    static char *buffer = NULL;
    static int buffer_length = 0;

    i = 0;
    while ((c = fgetc(stream)) != EOF) {
        if (!isalpha(c) && i == 0)
            continue;
        if (!isalpha(c))
            break;
        if (i >= buffer_length - 1) {
            buffer_length += 16;
            buffer = realloc(buffer, buffer_length*sizeof (char));
            if (buffer == NULL) {
                fprintf(stderr, "out of memory\n");
                exit(1);
            }
        }
        buffer[i++] = c;
    }

    if (i == 0)
        return NULL;

    buffer[i] = '\0';

    w = malloc(strlen(buffer) + 1);
    if (w == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strcpy(w, buffer);
    return w;
}

/*
 * stub to call strcmp as a comparison function for qsort
 */
int pstrcmp(const void *p1, const void *p2) {
    return strcmp(*(char * const *)p1, *(char * const *)p2);
}

/*
 * comparison function for qsort using word frequency and then alphabetic order
 */
int frequency_cmp(const void *p1, const void *p2) {
    char *word1 = *(char * const *)p1;
    char *word2 = *(char * const *)p2;
    int count1 = get_word_count(wc, word1);
    int count2 = get_word_count(wc, word2);
    int diff = count1 - count2;
    if (diff != 0) {
        return diff;
    } else {
        return strcmp(word1, word2);
    }
}

