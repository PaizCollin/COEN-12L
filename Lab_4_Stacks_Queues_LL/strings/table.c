#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define EMPTY 0
#define FILLED 1
#define DELETED 2

typedef struct set
{
	char **data;
	int *flags;
	int length;
	int count;
} SET;

SET *createSet(int maxElts);

unsigned strhash(char *s);

static int search(SET *sp, char *elt, bool *found) //O(m) search through the set
{
	assert(sp != NULL);
	*found = false;
	unsigned hash = strhash(elt);

	int firstDeletedIndex = -1;
	int index;
	int i;

	for(i=0; i<sp->length; i++)
	{
		index = (hash+i) % sp->length;

		if(sp->flags[index] == FILLED)
		{
			if(strcmp(elt, sp->data[index]) == 0)
			{
				*found = true;
				return index;
			}
			else
			{
				continue;
			}
		}
	}

	if(sp->flags[index] == EMPTY)
	{
		if(firstDeletedIndex != -1)
		{
			return firstDeletedIndex;
		}
		else
		{
			return index;
		}
	}
	
	if(sp->flags[index] == DELETED)
	{
		if(firstDeletedIndex == -1)
		{
			firstDeletedIndex = index;
		}
	}
	return firstDeletedIndex;
}

unsigned strhash(char *s) //O(m) hash function given
{
	unsigned hash = 0;
	
	while(*s != '\0')
	{
		hash = 31 * hash + *s++;
	}
	return hash;
}

SET *createSet(int maxElts) //O(m) returns a pointer to a new set with a max capacity of maxElts
{
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->data = malloc(sizeof(char*)*maxElts);
	assert(sp->data!=NULL);

	sp->flags = malloc(sizeof(int)*maxElts);
	assert(sp->flags!=NULL);

	sp->length = maxElts;

	int i;

	for(i = 0; i < sp->length; i++)
	{
		sp->flags[i] = EMPTY;
	}

	sp->count = 0;
	return sp;
}

void destroySet(SET *sp) //O(m) deallocate memory associated with the set pointed to by sp
{
	assert(sp != NULL);
	
	int i;

	for(i = 0; i < sp->length; i++)
	{
		if(sp->flags[i] == FILLED)
		{
			free(sp->data[i]);
		}
	}

	free(sp->data);
	free(sp->flags);
	free(sp);
}

int numElements(SET *sp) //O(1) return the number of elements in the set pointed to by sp
{
	assert(sp != NULL);
	return sp->count;
}

void addElement(SET *sp, char *elt) //O(m) add elt to the set pointed to by sp
{
	bool found = false;

	int addIndex = search(sp, elt, &found);
	
	if(!found)
	{
		if(sp->count < sp->length)
		{
			sp->data[addIndex] = strdup(elt);
			sp->flags[addIndex] = FILLED;
			sp->count++;
			return;
		}
		printf("Max elements already in set");
	}
}

void removeElement(SET *sp, char *elt) //O(m) remove elt from the set pointed to by sp
{
	bool found;
	int rmvPtrLocation = search(sp, elt, &found);

	if(found)
	{
		free(sp->data[rmvPtrLocation]);
		sp->flags[rmvPtrLocation] = DELETED;
		sp->count--;
	}
}

char *findElement(SET *sp, char *elt) //O(m) if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
{
	bool found;
	int fndPtrLocation = search(sp, elt, &found);
	
	if(found)
	{
		return sp->data[fndPtrLocation];
	}
	return NULL;
}

char **getElements(SET *sp) //O(m) allocate and return an array of elements in the set pointed to by sp
{
	assert(sp != NULL);
	char **elts = malloc(sizeof(char *)*sp->count);
	int eltsIndex = 0;
	int i;

	for(i = 0; i < sp->length; i++)
	{
		if(sp->flags[i] == FILLED)
		{
			elts[eltsIndex++] = sp->data[i];
		}
	}
	return elts;
} 

