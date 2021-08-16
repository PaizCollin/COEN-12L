#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
#include <assert.h>

typedef struct set //creates a structure SET with 3 values to be stored for each element
{
	char **data;
	int length;
	int count;

}SET;

static int searchSet(SET *sp, char *elt, int *found) //a function used to search for elements by comparing strings
{
	int i;
	int high = sp->count-1;
	int low = 0;
	int mid = 0;

	assert(sp != NULL);
	*found = 0;
	
	while(low <= high)
	{
		mid = (low + high)/2;

		if((strcmp(elt, sp->data[mid])) == 0)
		{
			*found = 1;
			return mid;
		}
		else if((strcmp(elt, sp->data[mid])) < 0)
		{
			high = mid - 1;
		}
		else
		{
			low = mid + 1;
		}
	}

	return low;
}

SET *createSet(int maxElts) //returns a pointer to a new set with a maximum capacity of maxElts
{
	SET *sp;

	sp = malloc(sizeof(SET));
	assert(sp != NULL);
	sp->data = malloc(sizeof(char *)*maxElts);
	assert(sp->data != NULL);
	sp->length = maxElts;
	sp->count = 0;
	return sp;
}

void destroySet(SET *sp) //deallocates memory associated with the set pointed to by sp
{
	int i;

	assert(sp != NULL);

	for(i=0; i<sp->count; i++)
	{
		free(sp->data[i]);
	}
	free(sp->data);
	free(sp);
}

int numElements(SET *sp) //returns the number of elements in the set pointed by sp
{
	assert(sp != NULL);
	return sp->count;
}

void addElement(SET *sp, char *elt) //adds an elt to the set pointed to by sp
{
	int found;
	int i;
	int add = searchSet(sp, elt, &found);

	if(found == 0)
	{
		if(sp->count < sp->length)
		{
			for(i=sp->count; i>add; i--)
			{
				sp->data[i] = sp->data[i-1];
			}

			sp->data[add] = strdup(elt);
			(sp->count)++;
			return;
		}

		printf("The maximum elements are already in the set");
	}
}

void removeElement(SET *sp, char *elt) //removes an elt from the set pointed to by sp
{
	int found;
	int i;
	int removeElement = searchSet(sp, elt, &found);
	
	if(found == 1)
	{
		free(sp->data[removeElement]);
		for(i=removeElement; i<sp->count; i++)
		{
			sp->data[i] = sp->data[i+1];
		}
		sp->count--;
	}
}

char *findElement(SET *sp, char *elt) //if elt is present in the set pointed to by sp, then return the matching element, otherwise return NULL
{
	int found;
	int findElement = searchSet(sp, elt, &found);

	if(found == 1)
	{
		return sp->data[findElement];
	}
	return NULL;
}

char **getElements(SET *sp) //allocate and return an array of elements in the set pointed to by sp
{
	int i;

	assert(sp != NULL);

	char **elts = malloc(sizeof(char *)*sp->count);

	for(i=0; i<sp->count; i++)
	{
		elts[i] = sp->data[i];
	}
	return elts;
}
