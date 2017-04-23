/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

/*** Trie.h ***/
typedef struct node {
    bool is_word;
    struct node *next_char[27];
}node;
struct node *head;
int trie_size = 0;

void insert(struct node *head, char str[]);
void free_node(struct node *head);
bool search(struct node *head, const char *str);
/*** End Trie.h ***/

/* See if word is in dictionary*/
bool check(const char* word)
{
    return search(head, word);
}

/* Loads dictionary into memory */
bool load(const char* dictionary)
{
    // init head
    head = (struct node *) malloc(sizeof(struct node));
    for(int i = 0; i < 27; i++)
        head->next_char[i] = NULL;
    head->is_word = false;
    
    // try to open dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Couldn't open %s.\n", dictionary);
        return false;
    }
    
    // read each word in dictionary
    while(fgets(str, LENGTH + 2, fp) != NULL)
    {
        insert(head, str);
        trie_size++;
    }
    return true;
}

/* Returns number of words in dictionary if loaded else 0 if not yet loaded */
unsigned int size(void)
{
    return trie_size;
}

/* Unloads dictionary from memory */
bool unload(void)
{
    free_node(head);
    return true;
}

/*** Trie.c ***/
void insert(struct node *head, char str[]) {
    struct node *crawler = head;

    for(int i = 0, len = strlen(str) - 1; i < len; i++) 
    {
        int idx;
        (str[i] == '\'') ? (idx = 26) : (idx = str[i] - 'a');
        
        if(crawler->next_char[idx] == NULL)
        {
            struct node *n;
            n = (struct node *) malloc(sizeof(struct node));
            for(int j = 0; j < 27; j++)
                n->next_char[j] = NULL;
            n->is_word = false;
            crawler->next_char[idx] = n;
            crawler = n;
            /** TEST **/
            //printf("New char:%c\n", str[i]);
        }
        else {
            crawler = crawler->next_char[idx];
            /** TEST **/
            //printf("Already char:%c\n", str[i]);
    
        }    
    }
    crawler->is_word = true;
    /** TEST **/
    //printf("NEW WORD:%s\n", str);
    return;
}

void free_node(struct node *head) {
    struct node *crawler = head;
    for(int i = 0; i < 27; i++)
        if (crawler->next_char[i] != NULL)
            free_node(crawler->next_char[i]);
    free(crawler);
 }

bool search(struct node *head, const char *str) {
    struct node *crawler = head;

    for(int i = 0, len = strlen(str); i < len; i++)
    {
        int idx;
        (str[i] == '\'') ? (idx = 26) : (idx = tolower(str[i]) - 'a');
        
        if(crawler->next_char[idx] == NULL)
            return false;
        else crawler = crawler->next_char[idx];
    }
    if (crawler->is_word == true)
        return true;
    return false;
}
/*** End Trie.c ***/