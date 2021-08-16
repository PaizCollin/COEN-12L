#include <stdio.h>
#include "pqueue.h"
#include "pack.h"
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#define PARENT ((i-1)/2)
#define LEFT ((i*2)+1)
#define RIGHT ((i*2)+2)

struct node *createNode() //creates a blank  node from struct grabbed from pack.h
{
	struct node *leaf = malloc(sizeof(struct node));
	assert(leaf != NULL);
	leaf->parent = NULL;
	leaf->count = 0;
	return leaf;
}

static int nodecmp(struct node *i1, struct node *i2) //compares he count of the two given nodes
{
	assert(i1 != NULL);
	assert(i2 != NULL);
	return(i1->count < i2->count ? -1 : (i1->count > i2->count));
}

static int depth(struct node *leaf) //returns the height of the given leaf
{
	int height = 0;
	while(leaf != NULL)
	{
		height++;
		leaf = leaf->parent;
	}
	return height;
}

struct node *mkNode(int data, struct node *left, struct node *right) //returns a new node with the left and right pointing to it as the parent
{
	struct node *new = malloc(sizeof(struct node));
	assert(new != NULL);
	new->count = data;
	left->parent = new;
	right->parent = new;
	return new;
}

int main(int argc, const char *argv[])
{
	FILE *in;
	struct node *leaves[257] = {NULL};
	PQ *pq;
	
	if(argc < 2) //checks for arguments
	{
		printf("Too few arguments given\n");
		exit(1);
	}
	
	char *infile = argv[1];
	char *outfile = argv[2];

	in = fopen(infile, "r");
	
	if(infile == NULL)
	{
		printf("FIle is NULL\n");
		exit(1);
	}

	int character;

	while((character = fgetc(in)) != EOF) //adds leaves and counts the number of occurences of each character
	{
		if(leaves[character] == NULL)
		{
			leaves[character] = createNode();
		}
		leaves[character]->count++;
	}
	
	leaves[256] = createNode();
	pq = createQueue(nodecmp);
	
	int i;

	for(i=0; i<257; i++) //inserts leaves into a priority queue
	{
		if(leaves[i] != NULL)
		{
			addEntry(pq, leaves[i]);
		}
	}

	struct node *item1;
	struct node *item2;

	while(numEntries(pq) >1) //forms huffman tree by taking the two lowest nodes and inserting them back into the heap as a tree with their combined count as a parent
	{
		item1 = removeEntry(pq);
		item2 = removeEntry(pq);
		int combinedCount = item1->count + item2->count;
		struct node *combined = mkNode(combinedCount, item1, item2);
		addEntry(pq, combined);
	}

	for(character=0; character<257; character++) //prints each character with its count
	{
		if(leaves[character] != NULL)
		{
			int encodingLength = depth(leaves[character]);
			int characterCount = leaves[character]->count;

			if(isprint(character))
			{
				printf("'%c' : %d x %d bits = %d bits\n", character, characterCount, encodingLength, characterCount*encodingLength);
			}
			else
			{
				printf("%o: %d x %d bits = %d bits\n", character, characterCount, encodingLength, characterCount*encodingLength);
			}
		}
	}

	pack(infile, outfile, leaves);
	fclose(in);
	return 0;
}







