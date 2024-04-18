#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
int count;
struct Trie *children[26]; //an array of 26 TrieNode pointers
};

// Initializes a trie structure
struct Trie *createTrie()
{
	// Create the struct, not a word.
    struct Trie* myTree = malloc(sizeof(struct Trie));
    myTree->count = 0;

    // Set each pointer to NULL.
    int i;
    for (i=0; i<26; i++)
        myTree->children[i] = NULL;

    // Return a pointer to the new root.
    return myTree;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
	struct Trie *current = pTrie;
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        int index = word[i] - 'a'; 
		// Assuming only lowercase letters
        if (!current->children[index])
        {
			// Create a new node if not already present
            current->children[index] = createTrie(); 
        }
        current = current->children[index];
    }
    // Mark the end of the word
    current->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
	struct Trie *current = pTrie;
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
		// Assuming only lowercase letters
        int index = word[i] - 'a'; 
        if (!current->children[index])
        {
            return 0;
        }
        current = current->children[index];
    }
	// Return the count of the last node
    return current->count; 
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
	// Find out if pTrie is NULL
    if (!pTrie)
        return NULL;

	// Recursively deallocate child nodes
    for (int i = 0; i < 26; i++)
    {
        deallocateTrie(pTrie->children[i]); 
    }

	// Free the memory allocated for the current node
    free(pTrie); 
    return NULL;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int numWords = 0;
    char word[256]; // Assuming maximum word length of 255 characters

	fscanf(file, "%d", &numWords);

	for (int i = 0; i < numWords; i++) {
		fscanf(file, "%s", word);
		pInWords[i] = strdup(word); // Copy the word into the array
	}

    printf("\n\n");
    fclose(file);
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
