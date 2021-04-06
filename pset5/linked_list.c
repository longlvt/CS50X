#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    printf("SIZE OF NODE: %lu\n", sizeof(node));
    node *list = NULL;
    node *tmp = malloc(sizeof(node));
    if (tmp == NULL)
        return 1;

    tmp->number = 1;
    tmp->next = NULL;
    list = tmp;

    tmp = malloc(sizeof(node));
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }
    tmp->number = 2;
    tmp->next = NULL;
    list->next = tmp;

    tmp = malloc(sizeof(node));
    if (tmp == NULL)
    {
        free(list->next);
        free(list);
        return 1;
    }
    tmp->number = 3;
    tmp->next = NULL;
    list->next->next = tmp;

    // Insert to the beginning of Linked-List
    tmp = malloc(sizeof(node)); // Allocate memory for new node
    tmp->number = 20; // Assign value of new node
    tmp->next = list; // Point the new node to the first memory of the linked-list. That means there's 2 pointers to the first node of the linked-list.
    list = tmp; // Assgin address of the new node the to linked-list.

    for (node *temp = list; temp != NULL; temp = temp->next)
    // Start at the first node of the list, end the loop at the last node (pointer to next = NULL).
    // Updating to the next field.
    {
        printf("%i\n", temp->number);
    }

    // Free the whole Linked-List
    while (list != NULL)
    {
        // printf("START:::");
        // printf("CURRENT: %i, %p\n", list->number, list->next);
        node *temp = list->next;
        free(list);
        list = temp;
    }

    printf("SHOW L-L\n");
    for (node *temp = list; temp != NULL; temp = temp->next)
    // Start at the first node of the list, end the loop at the last node (pointer to next = NULL).
    // Updating to the next field.
    {
        if (temp != NULL)
            printf("%i\n", temp->number);
    }
}