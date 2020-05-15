#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct list_node list_node;

struct list_node {
    int       data;
    list_node *next;
};

/*
 * return 1 iff list contains no elements, 0 otherwise
 */
int is_empty(list_node *list) {
    return (list == NULL);
}

/*
 * create a list_node and place the specified values in the fields
 */
list_node *create_node(int data, list_node *next) {
    list_node *newNode = (list_node *) malloc(sizeof(list_node));

    newNode->data = data;
    newNode->next = next;

    return newNode;
}

/*
 * insert integer at front of list
 */
list_node *insert(int value, list_node *list) {
    list_node *newNode = create_node(value, list);

    return newNode;
}

/*
 * return pointer to first node in list
 * NULL is returned if list is empty
 */
list_node *first(list_node *list) {
    return list;
}

/*
 * return pointer to last node in list
 * NULL is returned if list is empty
 */
list_node *last(list_node *list) {
    if (list == NULL) {
        return NULL;
    }

    list_node *head = list;
    while (head->next != NULL) {
        head = head->next;
    }
    
    return head;
}

/*
 * append integer to end of list
 */
list_node *append(int value, list_node *list) {
    list_node *newNode = create_node(value, NULL);
    if (is_empty(list) == 0) {
        (last(list))->next = newNode;
    } else {
        list = newNode;
    }

    return list;
}

/*
 * print contents of list Python syntax
 * e.g: [11, 12, 13, 42, 24]
 */
void print_list(list_node *list) {
    printf("[");

    list_node *head = list;
    while (head != NULL) {
        printf("%d", head->data);

        if (head->next != NULL) {
            printf(", ");
        }

        head = head->next;
    }
    
    printf("]");
}

/*
 * return number of nodes in list
 */
int length(list_node *list) {
    int count = 0;
    list_node *head = list;

    while (head != NULL) {
        count++;
        head = head->next;
    }

    return count;
}

/*
 * return cumulative sum of nodes in list (e.g. sum = node = node->next + node->next->next etc)
 */
int sum(list_node *list) {
    int sum = 0;
    list_node *head = list;

    while (head != NULL) {
        sum += head->data;
        head = head->next;
    }

    return sum;
}

/*
 * return pointer to nth node in list, counting from 0
 */
list_node *nth(int index, list_node *list) {
    list_node *head = list;

    for (int i = 0; i < index; i++) {
        head = head->next;
    }

    return head;
}

/*
 * return pointer to middle node in list
 */
list_node *middle(list_node *list) {
    int middle = length(list) / 2;
    return nth(middle, list);
}

/*
 * return 1 iff the list is in ascending order, 0 otherwise
 */
int is_ascending(list_node *list) {
    int ascending = 1;

    list_node *head = list;
    int previous = head->data;
    head = head->next;

    while (head != NULL) {
        if (previous > head->data) {
            ascending = 0;
        }

        previous = head->data;
        head = head->next;
    }
    return ascending;
}

/*
 * test the above functions
 */
int main(int argc, char *argv[]) {
    list_node *list = NULL;
    int number;

    printf("Enter a number: ");
    while (scanf("%d", &number) == 1) {
        list =  append(number, list);
        printf("Enter a number: ");
    }
    if (is_empty(list)) {
        printf("List is empty.\n");
        return 0;
    }
    printf("\nList entered was: ");
    print_list(list);
    printf("\nFirst element in list is: %d.\n", first(list)->data);
    printf("Middle element in list is: %d.\n", middle(list)->data);
    printf("Last element in list is: %d.\n", last(list)->data);
    printf("Length of list is: %d.\n", length(list));
    printf("Sum of the list is: %d.\n", sum(list));
    if (is_ascending(list)) {
        printf("List is in ascending order.");
    } else {
        printf("List is not in ascending order.");
    }
    return 0;
}


