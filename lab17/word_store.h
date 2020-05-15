typedef struct word_counter  word_counter;

word_counter *create_word_counter(void);                   // create a word counter
void increment_word_count(word_counter *wc, char *word);   // increment the count for a word
int get_word_count(word_counter *wc, char *word);          // get the count for a word
char **get_word_array(word_counter *wc, int *n_words);     // get the words for which counts are stored
void free_word_counter(word_counter *wc);                  // free word counter
