// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 961;

// Hash table
node *table[N];
unsigned int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //get the word's hash
    unsigned int hashIndex = hash(word);

    node *trav = table[hashIndex];

    while ( trav != NULL )
    {
       if ( strcasecmp( trav->word, word) == 0 )
       {
            return true;
       }

       else if ( strcasecmp (trav->word, word) != 0 )
       {
            trav = trav->next;
       }

    }

    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
    {
        unsigned  hash = 5381;
        int c;

        while ((c = tolower(*word++)))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
     return hash % N;
   }

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
   FILE *file = fopen("dictionaries/large", "r");

    if ( file == NULL)
    {
        return false;
    }
    char str[LENGTH + 1];

    while (fscanf(file, "%s", str) != EOF)
    {
      node *n = malloc(sizeof(node));

      if (n == NULL) {

          return false;
      }

      strcpy(n->word, str);

      n->next = NULL;

      unsigned int hashIndex = hash(str);

      if (table[hashIndex] == NULL)
      {
          table[hashIndex] = n;
      }

      else
      {
          n->next = table[hashIndex];
          table[hashIndex] = n;
      }
    counter++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    if (counter > 0)
    {
        return counter;
    }

    else
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for ( int i = 0 ; i > N ; i++)
    {
      node *trav = table[i];

      if (trav == NULL)
      {
          return true;
      }
      else if ( trav->next == NULL)
      {
          free(trav);
      }
      else
      {
          trav = trav->next;
      }
    }
    return true;
}
