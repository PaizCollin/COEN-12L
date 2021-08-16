#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>
#include <stdbool.h>

#define MAX_ELTS 10 //set max elements

typedef struct node //declare variables for the nodes
{
        void**data;
        struct node *prev;
        struct node *next;
        int count;
}NODE;

struct list //declare variables for the list
{
        int nodeCount;
        struct node *head;
        struct node *tail;
};

LIST *createList(void) //O(1) return a pointer to a new list
{
        LIST *lp = malloc(sizeof(LIST));
        assert(lp != NULL);
        lp->nodeCount = 0;
        lp->head = malloc(sizeof(NODE));
        lp->tail = malloc(sizeof(NODE));
        assert(lp->head != NULL);
        lp->head->next = NULL;
        lp->head->prev = NULL;
        lp->head->count = 0;
        lp->tail=lp->head;
        return lp;
}

void destroyList(LIST *lp) //O(n) deallocate memory associated with the list pointed to by lp
{
        assert(lp != NULL);
        NODE *head = lp->head;
        NODE *next;
        while(head != NULL) //iterate through each node, free as it goes
        {
                next = head->next;
                free(head);
                head = next;
        }

        free(lp);
        lp = NULL:
        lp->tail = lp->head;
}

int numItems(LIST *lp) //O(1) return the number of items in the list pointed to by lp
{
        assert(lp != NULL);
        int number = (lp->count * (lp->nodeCount - 1)) + lp->tail->count; //find the total number of items
        return number;
}         
         
void addFirst(LIST *lp, void *item) //O(n) add item as the first item in the list pointed to by lp
{        
        assert(lp != NULL);
        
        if(lp->head->count == MAX_ELTS) //if the node is full, create a new node previous to the first node
        {
                NODE *oldFirst = lp->head->next;
                NODE *newFirst = malloc(sizeof(NODE));
                assert(newFirst != NULL);
                newFirst->data[0] = item;
                newFirst->prev = NULL;
                newFirst->next = oldFirst; 
                oldFirst->prev = newFirst;
                lp->head = newFirst;
                lp->nodeCount++;
                newFirst->count++;
        } 
        else //shift all of the data up to add the item to the first value spot in the first node
        {
                NODE *current = lp->head;//shift array up (starting from the end of the list) and add to the beginning
                assert(current != NULL);
                int i;
                for(i=current->count; i>=0; i--)
                {
                        current->data[i] = current->data[i-1];
                }
                current->data[0] = item;
                current->count++;
        }
}

void addLast(LIST *lp, void *item) //O(1) add item as the last item in the list pointed to by lp
{
        assert(lp != NULL);

        if(lp->tail->count == MAX_ELTS) //if the node is full, create a new node at the end of the list
        {
                NODE *oldLast = lp->tail;
                NODE *newLast = malloc(sizeof(NODE)); //create new next node
                newLast->data[0] = item;
                newLast->prev = oldLast;
                newLast->next = NULL;
                oldLast->next = newLast;
                newLast->count++;
                lp->nodeCount++;
        }
        else //add the item at the end of the array in the last node
        {
                NODE *last = lp->tail;
                last->data[count] = item;
                last->count++;
        }
}

void *removeFirst(LIST *lp) //O(n) remove and return the first item in the list pointed to by lp; the list must not be empty
{
        assert(lp != NULL);
        assert(lp->nodeCount > 0);

        if(lp->head->count == 1) //if the first node only has one value, remove it and remove the node
        {
                assert(lp->count>0);
                NODE *oldFirst = lp->head;
                NODE *newFirst = oldFirst->next;
                void *oldFirstValue = oldFirst->data[0];
                lp->head->next = newFirst;
                newFirst->prev = lp->head;
                free(oldFirst);
                lp->nodeCount--;
                return oldFirstValue;
        }
        else //remove the first value in the array of the first node and shift all other values down
        {
                assert(lp->count > 0);
                NODE *first = lp->head;
                void *oldFirstValue = first->data[0];
                int i;
                for(i=0; i<first->count; i++)
                {
                        current->data[i] = current->data[i+1];
                }
                first->count--;
                return oldFirstValue;
        }
}

void *removeLast(LIST *lp) //O(1) remove and return the last item in the list pointed to by lp; the list must not by empty
{
        assert(lp != NULL);
        assert(lp->nodeCount > 0);

        if(lp->tail->count == 1] //if the last node has only one value in the array, free the entire array
        {
                assert(lp->count > 0);
                NODE *oldLast = lp->tail;
                NODE *newLast = oldLast->previous;
                void *oldLastValue = oldLast->data[0];
                lp->tail = newLast;
                newLast->next = NULL;
                free(oldLast);
                lp->count--;
                return oldLastValue;
        }       
        else //remove the last value in the array of the last node
        {       
                assert(lp->count > 0);
                NODE *last = lp->tail;
                void *oldLastValue = last->data[count-1];
                last->data[count-1] = NULL;
                last->count--;
                return oldLastValue;
        }
}       
        
void *getItem(LIST *lp, int index) //O(n) return the item at position index in the list pointed to by lp; the index must be within range
{               
        assert(lp!=NULL);
        void **item = malloc(sizeof(void*)*lp->count);
        NODE *current = lp->head;
                
        while(current->count < index) //iterate to the node that contains the index of the item
        {       
                index = index - lp->current->count;
                current = current->next;
        }
                
        return item[index]; //return item at the index according to the node it is placed in
}               
        
void setItem(LIST *lp, int index, void *item) //O(n) update the item at position index in the list pointed to by lp; the index must be within range
{
        assert(lp!=NULL);
        void **item = malloc(sizeof(void*)*lp->count);
        NODE *current = lp->head;
        while(current->count < index) //iterate to the node that contains the index of the item
        {
                index = index - lp->current->count;
                current = current->next;
        }       
                
        current->data[index] = item; //replace value with new item
                
}               
