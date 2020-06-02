// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 62000;

bool dict = false;
// Hash table
node *table[N];

void delete_list(node* head);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int key;
    
    node *p;
    key = hash(word);
    
    for(p = table[key]; p != NULL; p = p->next)
    {
        if(strcasecmp((p->word), word) == 0)
            return true;
  
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    const char *p = word;
    unsigned int num = 1, sum = 0;
    
    while(*p)
    {
        sum += (tolower(*p) * 10 + num*10);
        ++num;
        p++;
    }
    
    return (sum % 62000);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *fp;
    char c[LENGTH + 1];
    int key;
    node *new_node;
    
    if((fp = fopen(dictionary, "r")) == NULL)
        return false;
    
    while((fscanf(fp, "%s", c)) != EOF)
    {
        new_node = malloc(sizeof(node));
            
        if(new_node == NULL)
        {
            printf("Error: malloc failed in load.");
            return false;
        } 
        new_node->next = NULL;
        strcpy(new_node->word, c);
        
        key = hash(c);
        
        new_node->next = table[key];
        table[key] = new_node;
        
        dict = true;
        size();
        dict = false;
    }
    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    static int i = 0;
    
    if(dict)
        ++i;
        
    return i;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int i;
    node *temp;
    
    for(i = 0; i < N; i++)
        if(table[i] != NULL)
            delete_list(table[i]);
    
    return true;
}

void delete_list(node* head)
{
    if(head == NULL)
        return;
    
    delete_list(head->next);
    free(head);
}