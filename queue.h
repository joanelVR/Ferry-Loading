#include "status.h"

typedef void* QUEUE;


QUEUE queue_init_default(void); /*FIRST BOOK END (BOOK COVER)*/

/* enqueue_right is having the head with the first element, while moving the tail "enqueue_tail"*/
Status queue_enqueue(QUEUE hQueue, int item);

Status queue_service(QUEUE hQueue);

//Show the data of the front "head or left"
int queue_front(QUEUE hQueue, Status* pStatus);

Boolean queue_empty(QUEUE hQueue);

void queue_destroy(QUEUE* phQueue); /*SECOND BOOK END (BOOK END)*/