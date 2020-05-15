#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(void) {
    struct stack *stack = create();
    char ch;
    int balanced = 1;

    while ((ch = getchar()) != EOF && balanced == 1) {
        if (ch == '{' || ch == '[' || ch == '(') {
            push(stack, ch);
        } else if (ch == '}' || ch == ']' || ch == '}') {

        }
    }

    printf("%d\n", size(stack));

    return 0;
}
