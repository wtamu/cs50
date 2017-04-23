#include "trie.h"

/* Inserts words into trie */
void insert(struct node *head, char str[]) {
    // temp node *crawler
    struct node *crawler = head;
    
    // iterate over whole word
    for(int i = 0, len = strlen(str) - 1; i < len; i++) 
    {
        // set node index value
        int idx;
        (str[i] == '\'') ? (idx = 26) : (idx = str[i] - 'a');
        
        // if empty node
        if(crawler->next_char[idx] == NULL)
        {
            // init new node
            struct node *n;
            n = (struct node *) malloc(sizeof(struct node));
            for(int j = 0; j < 27; j++)
                n->next_char[j] = NULL;
            n->is_word = false;
            
            // point to new node
            crawler->next_char[idx] = n;
            // advance head
            crawler = n;
            
            /** TEST **/
            //printf("New char:%c\n", str[i]);
        }
        // else advance head
        else {
            crawler = crawler->next_char[idx];
            
            /** TEST **/
            //printf("Already char:%c\n", str[i]);
        }    
    }
    // signal end of word
    crawler->is_word = true;
    /** TEST **/
    //printf("NEW WORD:%sLEN:%lu\n", str, strlen(str));
    
    return;
}

/* Frees trie nodes recursively */
void free_node(struct node *head) {
    // temp node *crawler
    struct node *crawler = head;
    
    // search for active nodes
    for(int i = 0; i < 27; i++)
        if (crawler->next_char[i] != NULL)
        {
            free_node(crawler->next_char[i]);
            /** TEST **/
            //printf("Free:%c\n", i + 'a');
        }
    // base case
    free(crawler);
 }
 
/* Search for word in trie */
bool search(struct node *head, const char *str) {
    // temp node *crawler
    struct node *crawler = head;
    int idx;
    
    for(int i = 0, len = strlen(str); i < len; i++)
    {
        // set node index value
        (str[i] == '\'') ? (idx = 26) : (idx = tolower(str[i]) - 'a');
        
        // if empty node
        if(crawler->next_char[idx] == NULL)
            return false;
            
        // else advance head
        else crawler = crawler->next_char[idx];
    }
    // word found
    if (crawler->is_word == true)
        return true;
    
    // catch all
    return false;
}