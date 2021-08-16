#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>
#include <stdbool.h>

typedef struct node
{
	void *data;
	struct node *prev;
	struct node *next;
}NODE;

struct list
{
	int count;
	struct node *head;
	int (*compare)();
};

LIST *createList(int (*compare)()) //O(1) return a pointer to a new list using compare as its comparison function which may be NULL
{
	LIST *lp = malloc(sizeof(LIST));
	assert(lp != NULL);
	lp->count = 0;
	lp->compare = compare;
	lp->head = malloc(sizeof(NODE));
	assert(lp->head != NULL);
	lp->head->prev = lp->head;
	lp->head->next = lp->head;
	return lp;
}

void destroyList(LIST *lp) //O(n) deallocate memory associated with the list pointed to by lp
{
	assert(lp != NULL);
	NODE *current = lp->head->next;
	NODE *next;
	while(current != lp->head)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(lp->head);
	free(lp);
}

int numItems(LIST *lp) //O(1) return the number of items in the list pointed to by lp
{
	assert(lp != NULL);
	return lp->count;
}

void addFirst(LIST *lp, void *item) //O(1) add item as the first item in the list pointed to by lp
{
	assert(lp != NULL);
	NODE *oldFirst = lp->head->next;
	NODE *newFirst = malloc(sizeof(NODE));
	assert(newFirst != NULL);
	newFirst->data = item;
	newFirst->prev = lp->head;
	newFirst->next = oldFirst;
	oldFirst->prev = newFirst;
	lp->head->next = newFirst;
	lp->count++;
}

void addLast(LIST *lp, void *item) //O(1) add item as the last item in the list pointed to by lp
{
	assert(lp != NULL);
	NODE *oldLast = lp->head->prev;
	NODE *newLast = malloc(sizeof(NODE));
	assert(newLast != NULL);
	newLast->data = item;
	newLast->prev = oldLast;
	newLast->next = lp->head;
	oldLast->next = newLast;
	lp->head->prev = newLast;
	lp->count++;
}

void *removeFirst(LIST *lp) //O(1) remove and return the first item in the list pointed to by the lp; the list must not be empty
{
	assert(lp != NULL);
	assert(lp->count > 0);
	NODE *oldFirst = lp->head->next;
	NODE *newFirst = oldFirst->next;
	void *oldFirstValue = oldFirst->data;
	lp->head->next = newFirst;
	newFirst->prev = lp->head;
	free(oldFirst);
	lp->count--;
	return oldFirstValue;
}

void *removeLast(LIST *lp) //O(1) remove and return the last item in the list pointed to by lp; the list must not be empty
{
	assert(lp != NULL);
	assert(lp->count > 0);
	NODE *oldLast = lp->head->prev;
	NODE *newLast = oldLast->prev;
	void *oldLastValue = oldLast->data;
	lp->head->prev = newLast;
	newLast->next = lp->head;
	free(oldLast);
	lp->count--;
	return oldLastValue;
}

void *getFirst(LIST *lp) //O(1) return, but do not remove, the first item in the list pointed to by lp; the list must not be empty
{
	assert(lp != NULL);
	assert(lp->count != 0);
	return lp->head->next->data;
}

void *getLast(LIST *lp) //O(1) return, but do not remove, the last item in the list pointed to by lp; the list must not be empty
{
	assert(lp != NULL);
	assert(lp->count != 0);
	return lp->head->prev->data;
}

void removeItem(LIST *lp, void *item) //O(n) if item is present in the list pointed to by lp, then remove it; the comparison function must not be NULL
{
	assert(lp != NULL);
	assert(lp->compare != NULL);
	NODE *current = lp->head->next;
	int i;

	for(i=0; i<lp->count; i++)
	{
		if(lp->compare(item, current->data) == 0)
		{
			current->prev->next = current->next;
			current->next->prev = current->prev;
			free(current);
			lp->count--;
			return;
		}
		current = current->next;
	}
}

void *findItem(LIST *lp, void *item) //O(n) if item is present in the list pointed to by lp then return the matching item, otherwise return NULL: the comparison function must not be NULL
{
	assert(lp != NULL);
	assert(lp->compare != NULL);
	NODE *current = lp->head->next;
	int i;

	for(i=0; i<lp->count; i++)
	{
		if(lp->compare(item, current->data) == 0)
		{
			return current->data;
		}
		current = current->next;
	}
	return NULL;
}

void *getItems(LIST *lp) //O(n) allocate and return an array of items in the list pointed to by lp
{
	assert(lp != NULL);
	void **items = malloc(sizeof(void*)*lp->count);
	NODE *current = lp->head->next;
	int i;

	for(i=0; i<lp->count; i++)
	{
		items[i] = current->data;
		current = current->next;
	}
	return items;
}




	
