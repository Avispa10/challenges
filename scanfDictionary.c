#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node
{
    char word[45];
    struct node *next;
}
node;

const int N = 961;

// Hash table
node *table[N];

// hash function
unsigned int hash(unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while ((c = *str++))
            hash = ((hash << 5) + hash) + c;

      return hash % N;
    }

//COUNT WORDS LOADED
unsigned int size(void)
{
    // TODO
    unsigned int counter = 0;
    // itereate through each link list of the hash table
    for ( int i = 0 ; i < N ; i++)
    {
        //iterate through all nodes of each linked list
        for ( node *tmp = table[i] ; tmp != NULL ; tmp = tmp->next )
        {
        counter++;
        }
    }
    printf("words: %u\n" , counter);
    return counter;
}


int main (void){

     FILE *file = fopen("pset5/speller/dictionaries/small", "r");
    if ( file == NULL)
    {
        return 1;
    }

    unsigned char *str = malloc(sizeof(char*));

    while (fscanf(file, "%s", str) != EOF)
    {
      fscanf(file,"[ˆ\n]%s", str);

      node *n = malloc(sizeof(node));

      if (n == NULL) {
          return 1;
      }

      strcpy(n->word, (const char*)str);
      n->next = NULL;

      //printf("words : %s address: %p\n", n->word, n->word);

      unsigned int hashIndex = hash(str);
      //printf("hash: %i\n", hashIndex);


      if (table[hashIndex] != NULL)
      {
          n->next = table[hashIndex];
          table[hashIndex] = n;
      }

      else
      {
          table[hashIndex] = n;
      }

     // printf("HashIndex: %i\n", hashIndex);

    free(n);
    }
    printf("qty of words loaded: %u\n", size());
    fclose(file);
    free(str);
    return 0;
    }
