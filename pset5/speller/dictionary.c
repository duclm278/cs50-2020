// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 150000;

// Size of the selected dictionary;
unsigned int SIZE = 0;

// Make the file pointer global
FILE *file = NULL;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    for (node *tmp = table[hash(word)]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Adapted from http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        // Make sure that hash function is case-insensitive with tolower()
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    file = fopen(dictionary, "r");
    if (file != NULL)
    {
        node *n;
        char word[LENGTH + 1];
        unsigned int index;

        while (fscanf(file, "%s", word) != EOF)
        {
            // Create a new note for each word
            n = malloc(sizeof(node));
            if (n == NULL)
            {
                return false;
            }
            strcpy(n->word, word);
            n->next = NULL;

            // Insert node into hash table
            index = hash(word);
            n->next = table[index];
            table[index] = n;

            // Update the size of the selected dictionary
            SIZE++;
        }
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (SIZE != 0)
    {
        return SIZE;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int free_count = 0;
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;

            // Update the number of nodes that have been freed
            free_count++;
        }
    }
    fclose(file);

    if (SIZE == free_count)
    {
        return true;
    }
    return false;
}
