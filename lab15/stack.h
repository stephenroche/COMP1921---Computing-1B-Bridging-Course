typedef struct stack *stack_t;

stack_t create(void);                   // create a new stack
void destroy(stack_t stack);            // free a stack
void push(stack_t stack, int item);     // add new item to stack
int pop(stack_t stack);                 // remove top item from stack and return it
int is_empty(stack_t stack);            // return true if stack is empty
int top(stack_t stack);                 // return top item from stack but don't remove it
int size(stack_t stack);                // return number elements in stack
