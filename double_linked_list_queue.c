#include "queue.h"
#include <limits.h>
#include <stdlib.h>

struct node;
typedef struct node Node;
struct node
{
	int data;
	Node* next;
	Node* prev;
};

struct queue 
{ 
	Node* head;
	Node* tail;
};
typedef struct queue Queue;

/*FIRST BOOK END (BOOK COVER)*/
QUEUE queue_init_default(void)
{
	Queue* pQueue;

	pQueue = (Queue*)malloc(sizeof(Queue));
	if (pQueue != NULL)
	{
		pQueue->head = NULL;
		pQueue->tail = NULL;
	}

	return (QUEUE)pQueue;
}

Status queue_enqueue(QUEUE hQueue, int item)
{
	Queue* pQueue = (Queue*)hQueue;
	Node* temp;

	temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
	{
		return FAILURE;
	}

	//Creating a new node
	temp->data = item; //
	temp->prev = NULL;
	temp->next = NULL;

	if (pQueue->tail == NULL || pQueue->head == NULL)
	{
		pQueue->head = temp; //The head pointer is pointing at whatever temp is
		pQueue->tail = temp; //The tail pointer...
	}
	else
	{
		pQueue->tail->next = temp;
		temp->prev = pQueue->tail;
		pQueue->tail = temp;
	}

	return SUCCESS;
}

Status queue_service(QUEUE hQueue)
{
	Queue* pQueue = (Queue*)hQueue;
	Node* temp;

	if (queue_empty(hQueue))
	{
		return FAILURE;
	}

	temp = pQueue->head; //Temp points to whatever head holds
	pQueue->head = pQueue->head->next; //Make head point to the next element
	free(temp); //Get rib of the previous element
	
	if (pQueue->head != NULL)
	{
		pQueue->head->prev = NULL;
	}

	return SUCCESS;
}

int queue_front(QUEUE hQueue, Status* pStatus)
{
	Queue* pQueue = (Queue*)hQueue;

	if (pQueue->head == NULL)
	{
		if (pStatus != NULL)
		{
			*pStatus = FAILURE;
		}
		return INT_MIN;
	}

	if (pStatus != NULL)
	{
		*pStatus = SUCCESS;
	}

	return pQueue->head->data;
}

Boolean queue_empty(QUEUE hQueue)
{
	Queue* pQueue = (Queue*)hQueue;

	if (pQueue->head == NULL)
	{
		return TRUE;
	}

	return FALSE;
}

/*SECOND BOOK END (BOOK END)*/
void queue_destroy(QUEUE* phQueue)
{
	Queue* pQueue = (Queue*)*phQueue;
	Node* head = pQueue->head;
	Node* temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}

	*phQueue = NULL;
}