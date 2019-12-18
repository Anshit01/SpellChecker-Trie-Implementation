// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

//prototypes
void add(char *word);
int indexof(char a);
unsigned int sizer(node *node1);
void unloadr(node *node1);

// Represents a trie
node *root;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        add(word);
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

void add(char *word)
{
    node *node1 = root;
    int i;
    for(i = 0; word[i] != '\0'; i++)
    {
        int index = indexof(word[i]);
        if(node1 -> children[index] == NULL)
        {
            node1 -> children[index] = malloc(sizeof(node));
            node1 = node1 -> children[index];
            for(int j = 0; j < N; j++)
            {
                node1 -> children[j] = NULL;
            }
            node1 -> is_word = false;
        }
        else
        {
            node1 = node1 -> children[index];
        }
    }
    node1 -> is_word = true;
}

int indexof(char a)
{
    int i = 0;
    if(a >= 'a' && a <= 'z')
    {
        i = (int) a - 'a';
    }
    else if(a >= 'A' && a <= 'Z')
    {
        i = (int) a - 'A';
    }
    else if(a == '\'')
    {
        i = 26;
    }
    return i;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    node *node1 = root;
    unsigned int s = 0;
    s = sizer(node1);
    return s;
}

unsigned int sizer(node *node1)
{
    unsigned int s = 0;
    for(int i = 0; i < N; i++)
    {
        if(node1 -> is_word)
        {
            s++;
        }
        if(node1 -> children[i] != NULL)
        {
            s += sizer(node1 -> children[i]);
        }
    }
    return s;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *node1 = root;
    for(int i = 0; word[i] != '\0'; i++)
    {
        if(node1 -> children[indexof(word[i])] == NULL)
        {
            return false;
        }
        node1 = node1 -> children[indexof(word[i])];
    }
    if(node1 -> is_word)
    {
        return true;
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    unloadr(root);
    return true;
}

void unloadr(node *node1)
{
    bool last = false;
    for(int i = 0; i < N; i++)
    {
        if(node1 -> children[i] != NULL)
        {
            unloadr(node1 -> children[i]);
        }
    }
    free(node1);
}
