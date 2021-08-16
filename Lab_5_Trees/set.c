#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "set.h"
#include <assert.h>
#include <stdbool.h>

#define DIV 20

struct set
{
	LIST **data;
	int length;
	int count;
	unsigned (*hash)();
};

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) //O(m) return a pointer to a new set using compare as its comparison function. hash table, no chaining
{
	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	int m = maxElts/DIV;
	sp->data = malloc(sizeof(LIST*)*m);
	assert(sp->data != NULL);
	sp->length = m;
	sp->count = 0;
	
	assert(compare != NULL);
	int i;
	
	for(i=0; i<sp->length; i++)
	{
		sp->data[i] = createList(compare);
	}
	
	assert(hash != NULL);
	sp->hash = hash;
	return sp;
}

void destroySet(SET *sp) //O(n) deallocate memory associated with the set pointed to by sp
{
	assert(sp != NULL);
	int i;

	for(i=0; i<sp->length; i++)
	{
		destroyList(sp->data[i]);
	}
	free(sp->data);
	free(sp);
}

int numElements(SET *sp) //O(1) return the number of items in the list pointed to by sp
{
	assert(sp != NULL);
	return sp->count;
}

void addElement(SET *sp, void *elt) //O(1) add item pointed to by the elt to the set pointed to by sp
{
	assert(sp != NULL);
	int hash = ((*sp->hash)(elt))%(sp->length);
	addLast(sp->data[hash], elt);
	sp->count++;
}

void removeElement(SET *sp, void *elt) //O(n) remove item pointed to by the elt to the set pointed to by sp
{
	assert(sp != NULL);
	int hash = ((*sp->hash)(elt))%(sp->length);
	if(findItem(sp->data[hash], elt) != NULL)
	{
		removeItem(sp->data[hash], elt);
		sp->count--;
	}
}

void *findElement(SET *sp, void *elt) //O(n) returns the element in the set pointed to by sp that matches the item pointed to by elt
{
	assert(sp != NULL);
	int hash = ((*sp->hash)(elt))%(sp->length);
	void *result = findItem(sp->data[hash], elt);
	return result;
}

void *getElements(SET *sp) //O(n) returns an array of all the elements in the set pointed to by sp
{
	assert(sp != NULL);
	void **elts = malloc(sizeof(void*)*sp->count);
	int addIndex = 0;
	int i;
	int j;

	for(i=0; i<sp->length; i++)
	{
		void **listElts = getItems(sp->data[i]);
		for(j=0; j<numItems(sp->data[i]); j++)
		{
			elts[addIndex+j] = listElts[j];
		}
		addIndex += numItems(sp->data[i]);
	}
	return elts;
}




	
