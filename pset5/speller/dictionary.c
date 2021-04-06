// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

bool check_added(char *word);
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
#define N 26

// Hash table
node *table[N];

// Number of word added to the table
int counter = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash the word to obtain a hash value
    int location = hash(word);

    // printf("WORD TO COMPARE: %s, location: %i\n", word, location);

    // Access linked-list at the index of hash table
    node *startNode = table[location];

    // Look for the word in the linked-list
    // Use strcasecmp() to compare word with case sensitive.
    for (node *temp = startNode; temp != NULL; temp = temp->next)
    {
        if (strcasecmp(word, temp->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int hash_sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        hash_sum += tolower(word[i]);
    }
    return (hash_sum % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    // Read from dictionary and insert to the hash table
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    {
        if (!check(word)) // Can't find the current word in the table, continue to add it to the table.
        {
            // Increase the count of word in table.
            counter ++;

            // Hash word to get the location in hash table
            int location = hash(word);

            // printf("WORD TO BE ADDED: %s, at location: %i\n", word, location);

            // Create new node for each word
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return false;
            }
            // Copy the word into the node.
            strcpy(n->word, word);
            n->next = NULL;

            // Insert node into has table at location.
            if (table[location] == NULL) // If there's no any node at the location
            {
                table[location] = n;
            }
            else // If there's node at the location, then insert new node to the beginning of the linked-list.
            {
                n->next = table[location];
                table[location] = n;
            }
        }
    }

    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Free the whole hash table
    for (int id = 0; id < N; id++)
    {
        while (table[id] != NULL)
        {
            node *temp = table[id]->next;
            free(table[id]);
            table[id] = temp;
        }
    }
    return true;
}

// Find a word in the hash table
bool check_added(char *word)
{
    if (table[hash(word)] != NULL)
    {
        for (node *temp = table[hash(word)]; temp != NULL; temp = temp->next)
        {
            if (strcasecmp(word, temp->word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}
