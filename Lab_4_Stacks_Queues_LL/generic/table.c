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
	void **data;
	int *flags;
	int length;
	int count;
	int (*compare)();
	unsigned (*hash)();
}SET;

SET *createSet(int maxElts, int (*compare)(), unsigned(*hash)());

static int search(SET *sp, void *elt, bool *found) //O(m) search the set
{
	*found = false;
	unsigned hash = (*sp->hash)(elt);
	int firstDeletedIndex = -1;
	int index;
	int i;
	
	for(i=0; i<sp->length; i++)
	{
		index = (hash+i) % sp->length;
		
		if(sp->flags[index] == FILLED)
		{
			if((*sp->compare)(elt, sp->data[index]) == 0)
			{
				*found = true;
				return index;
			}
			else
			{
				continue;
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
	}
	return firstDeletedIndex;
}

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) //O(m) return a pointer to a new set with a max capacity of maxElts
{
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->data = malloc(sizeof(void*)*maxElts);
	assert(sp->data != NULL);
	sp->flags = malloc(sizeof(int)*maxElts);
	assert(sp->flags != NULL);
	sp->length = maxElts;

	int i;

	for(i=0; i<sp->length; i++)
	{
		sp->flags[i] = EMPTY;
	}
	
	sp->count = 0;

	assert(compare != NULL);
	sp->compare = compare;
	assert(hash != NULL);
	sp->hash = hash;
	
	return sp;
}

void destroySet(SET *sp) //O(1) deallocate memory associated with the set pointed to by sp
{
	assert(sp != NULL);
	free(sp->data);
	free(sp->flags);
	free(sp);
}

int numElements(SET *sp) //O(1) return the number of elements in the set pointed to by sp
{
	return sp->count;
}

void addElement(SET *sp, void *elt) //O(m) add elt to the set pointed to by sp
{
	bool found = false;
	int addIndex = search(sp, elt, &found);
	
	if(!found)
	{
		if(sp->count < sp->length)
		{
			sp->data[addIndex] = elt;
			sp->flags[addIndex] = FILLED;
			sp->count++;
			return;
		}
		printf("Max elements already in set");
	}
}

void removeElement(SET *sp, void *elt) //O(m) remove the elt from the set pointed to by sp
{
	bool found;
	int rmvPtrLocation = search(sp, elt, &found);
	
	if(found)
	{
		sp->data[rmvPtrLocation] = NULL;
		sp->flags[rmvPtrLocation] = DELETED;
		sp->count--;
	}
}

void *findElement(SET *sp, void *elt) //O(m) if elt is present in the set pointed to by sp then return the matching element, otherwise return NULL
{
	bool found;
	int fndPtrLocation = search(sp, elt, &found);
	
	if(found)
	{
		return sp->data[fndPtrLocation];
	}
	return NULL;
}

void *getElements(SET *sp) //O(m) allocate and return an array of elements in the set pointed to by sp
{
	void **elts = malloc(sizeof(void *)*(sp->count));
	int eltsIndex = 0;
	int i;

	for(i=0; i<sp->length; i++)
	{
		if(sp->flags[i] == FILLED)
		{
			elts[eltsIndex++] = sp->data[i];
		}
	}
	return elts;
}

