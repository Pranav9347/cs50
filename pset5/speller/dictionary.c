// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node; // each node should contain a word & a pointer to the next node

// TODO: Choose number of buckets in hash table
const unsigned int N = 1171;//45*26 pointers:each pointer pointing to an array containing words havin same no. of letters and starting letter

// Hash table
node *table[1171] = {NULL};

// compares the spelling of two words(basically a case insensitive strcmp())
int spellcmp(const char *word1, const char *word2)
{
    // as both are mapped to the same index, their strlen's are the same:
    for (int i = 0; i < strlen(word1); i++)
    {
        if (tolower(word1[i]) != word2[i])
            return 0;
    }
    return 1;
}

// Returns true if word is in dictionary, else false
bool check(const char *word) //#4
{
    if (strlen(word) > LENGTH || !isalpha(word[0]))
        return false;
    unsigned int index = hash(word);
    node* temp = table[index];
    while (temp != NULL)
    {
        if (spellcmp(word, temp->word) == 1)
            return true;
        temp = temp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) //#2
{
    // considering both starting letter and number of letters (to decrease search time/increase number of buckets)
    return LENGTH*(toupper(word[0]) - 'A') + strlen(word);
    // starting_letter = index/45, number_of_letters = index % 45.
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) //#1
{
    // TODO
    /*1. takes file_name as input: default: "dictionaries/large"
    wordbook is pointer to the dictionary being used*/
    FILE* wordbook = fopen(dictionary, "r");
    if (wordbook == NULL)
        return false;
    char word[LENGTH];
    unsigned int i = 0;
    while (!feof(wordbook))
    {
        fscanf(wordbook, "%s\n", word);
        i = hash(word);
        if (table[i] == NULL)
        {
            table[i] = (node*) malloc(sizeof(node));
            for (int j = 0; j < strlen(word) + 1; j++)
                table[i]->word[j] = word[j];
            table[i]->next = NULL;
        }
        else // collision: handled using separate chaining technique
        {
            // insert at end:
            // node* temp = table[i];
            //  while(temp->next != NULL)
            //      temp = temp->next;
            //  temp->next = (node*)malloc(sizeof(node));
            //  temp->next->next = NULL;
            //  for(int j = 0; j < strlen(word)+1; j++)
            //      temp->next->word[j] = word[j];

            // new_node inserted at the beginning to reduce time:
            node* new_node = (node*) malloc(sizeof(node));
            new_node->next = table[i];
            for (int j = 0; j < strlen(word) + 1; j++)
                new_node->word[j] = word[j];
            table[i] = new_node;
        }
    }
    fclose(wordbook);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) //#3
{
    int k = 0;
    node* temp = NULL;
    for (int i = 1; i < 1171; i++) // next 45 to 90: b
    {
        temp = table[i];
        while (temp != NULL)
        {
            k++;
            temp = temp->next;
        }
    }

    return k;
}

// recursive function to free allocated memory
void delete_hash_row(node* temp)
{
    if (temp == NULL)
        return;
    else
    {
        delete_hash_row(temp->next);
        free(temp);
        return;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) //#5
{
    for (int i = 1; i < 1171; i++)
        delete_hash_row(table[i]);
    return true;
}
