#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Declare trie node
typedef struct node {
    bool is_word;
    struct node *next_char[27];
}node;

// Function prototypes
void insert(struct node *head, char str[]);
void free_node(struct node *head);
bool search(struct node *head, const char *str);