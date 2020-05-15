#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct list_node list_node;
typedef list_node *linked_list;

struct list_node {
    int       data;
    list_node *next;
};

/*
 * create a list_node and place the specified values in the fields
 */
linked_list create_node(int data, linked_list next) {
    list_node *n;

    n = malloc(sizeof (list_node));
    if (n == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    n->data = data;
    n->next = next;
    return n;
}

/*
 * insert integer at front of list
 */
linked_list insert(int value, linked_list list) {
    return create_node(value, list);
}

/*
 * return pointer to last node in list
 * NULL is returned if list is empty
 */
list_node *last(linked_list list) {
    list_node *n = list;
    if (n == NULL)
        return NULL;
    while (n->next != NULL)
        n = n->next;
    return n;
}


/*
 * append integer to end of list
 */
linked_list append(int value, linked_list list) {
    list_node *n;

    n =  create_node(value, NULL); /* will be last node in list */

    if (list == NULL) {
       return n;                  /* new node is now  head of the list */
    } else {
        last(list)->next = n;  /* append node to list */
        return list;
    }
}

/*
 * print contents of list in Python syntax
 */
void print_list(linked_list list) {
    list_node *n;

    printf("[");
    for (n = list; n != NULL; n = n->next) {
        printf("%d", n->data);
        if (n->next != NULL)
            printf(", ");
    }
    printf("]");
}



/*
 * delete first node containing specified int
 */
linked_list delete_first(linked_list list) {
    linked_list tmp = list->next;
    free(list);

    return tmp;
}

/*
 * delete first node containing specified int
 */
linked_list delete_last(linked_list list) {
    linked_list node = list;

    if (node == NULL) {
        return NULL;

    } else if (node->next == NULL) {
        free(node);
        return NULL;

    } else {
        while (node->next->next != NULL) {
            node = node->next;
        }

        free(node->next);
        node->next = NULL;
    }

    return list;
}

/*
 * delete first node containing specified int
 */
linked_list delete(int i, linked_list list) {
    linked_list node = list;

    if (list == NULL) {
        return NULL;
    }

    if (node->next == NULL) {
        if (node->data == i) {
            free(node);
            return NULL;
        } else {
            return list;
        }
    }

    while (node->next != NULL && node->next->data != i) {
        node = node->next;
    }

    if (node->next != NULL) {
        linked_list tmp = node->next;
        node->next = node->next->next;
        free(tmp);
    }

    return list;
}

/*
 * reverse the nodes in list
 */
linked_list reverse(linked_list list) {
    linked_list newStart = NULL;

    while (list != NULL) {
        newStart = append(last(list)->data, newStart);
        list = delete_last(list);
    }

    return newStart;
}
/*
linked_list reverse_recursive(linked_list list) {
    linked_list newStart = list;

    if (is_empty(list)) {
    } else if (is_length(list, 1)) {
    } else {
        linked_list newLast = list->next;
        
    }

    return newStart;
}
*/
#define MAX_LINE 4096

/*
 * test the above functions
 */
int
main(int argc, char *argv[]) {
    linked_list list;
    int argument;
    char *s, *t;
    char line[MAX_LINE];
    char action[MAX_LINE];

    list = NULL;
    while (1) {
        printf("list = ");
        print_list(list);
        printf("\n");
        printf("> ");
        if (fgets(line, MAX_LINE, stdin) == NULL)
            break;

        for (s = line; isspace(*s); s++)
            ;

        t = action;
        while (isalpha(*s) || *s == '_')
            *t++ = *s++;
        *t = '\0';

        argument = strtol(s, &s, 10);

        if (strcmp(action, "quit") == 0)
            break;
        else if (strcmp(action, "") == 0)
            continue;
        else if (strcmp(action, "insert") == 0)
            list = insert(argument, list);
        else if (strcmp(action, "append") == 0)
            list = append(argument, list);
        else if (strcmp(action, "delete_first") == 0)
            list = delete_first(list);
        else if (strcmp(action, "delete_last") == 0)
            list = delete_last(list);
        else if (strcmp(action, "delete") == 0)
            list = delete(argument, list);
        else if (strcmp(action, "reverse") == 0)
            list = reverse(list);
        else
            printf("Unknown command: '%s'\n", action);
    }
    return 0;
}
