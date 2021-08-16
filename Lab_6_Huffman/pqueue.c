#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"
#include <assert.h>

#define p(x) (((x)-1)/2)
#define l(x) ((x)*2+1)
#define r(x) ((x)*2+2)
#define INIT_LENGTH 10

struct pqueue
{
	int count;
	int length;
	void **data;
	int (*compare)();
};

PQ *createQueue(int (*compare)()) //O(1) return a pointer to a new priority queue using compare as its comparison function
{
	PQ *pq;
	assert(compare != NULL);
	pq = malloc(sizeof(PQ));
	assert(pq != NULL);
	pq->compare = compare;
	pq->length = INIT_LENGTH;
	pq->count = 0;
	pq->data = malloc(sizeof(void *)*pq->length);
	assert(pq->data != NULL);
	return pq;
}

void destroyQueue(PQ *pq) //O(1) deallocate memory associated with the priority queue pointed to by pq
{
	assert(pq != NULL);
	free(pq->data);
	free(pq);
}

int numEntries(PQ *pq) //O(1) return the number of entries in the priority queue pointed to by pq
{
	assert(pq != NULL);
	return pq->count;
}

void addEntry(PQ *pq, void *entry) //O(log(n)) add entry to the priority queue pointed to by pq
{
	if(pq->count == pq->length)
	{
		pq->length *= 2;
		pq->data = realloc(pq->data, sizeof(void *)*pq->length);
		assert(pq->data != NULL);
	}
	
	pq->data[pq->count] = entry;
	pq->count++;

	int i = pq->count-1;
	while(i >= 1)
	{
		if((*pq->compare)(entry, pq->data[p(i)]) < 0)
		{
			PQ *temp = pq->data[p(i)];
			pq->data[p(i)] = pq->data[i];
			pq->data[i] = temp;
			i = p(i);
		}
		else
		{
			break;
		}
	}
}

void *removeEntry(PQ *pq) //O(log(n)) remove and return the smallest entry from the priority queue pointed to by pq
{
	assert(pq->count != 0);
	void *root = pq->data[0];
	pq->data[0] = pq->data[pq->count-1];
	pq->count--;

	int i = 0;
	while(l(i) < pq->count)
	{
		int minChild;
		if(r(i) < pq->count && pq->compare(pq->data[r(i)], pq->data[l(i)]) < 0)
		{
			minChild = r(i);
		}
		else
		{
			minChild = l(i);
		}

		if(pq->compare(pq->data[i], pq->data[minChild]) >= 0)
		{
			PQ *temp = pq->data[minChild];
			pq->data[minChild] = pq->data[i];
			pq->data[i] = temp;
			i = minChild;
		}
		else
		{
			break;
		}
	}
	return root;
}
