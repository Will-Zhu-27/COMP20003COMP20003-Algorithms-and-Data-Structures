/* priorityQueue.c */
/* use heap to store priority queue */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "priorityQueue.h"

void upHeap(struct priorityQueue *pq);
void downHeap(struct priorityQueue *pq);

struct priorityQueue *makePriorityQueue() {
	struct priorityQueue *ret = NULL;
	ret = (struct priorityQueue *) malloc(sizeof(struct priorityQueue));
	assert(ret);
	ret->capacity = 0;
	ret->dataList = NULL;
	ret->priority = NULL;
	return ret;
}

void enqueue(struct priorityQueue *pq, void *data, int priority) {
	
	pq->dataList = realloc(pq->dataList, sizeof(void *) * (pq->capacity + 1));
	assert(pq->dataList);
	pq->dataList[pq->capacity] = data;
	
	pq->priority = realloc(pq->priority, sizeof(int) * (pq->capacity + 1));
	assert(pq->priority);
	pq->priority[pq->capacity] = priority;
	
	pq->capacity++;
	upHeap(pq);
}

void *dequeue(struct priorityQueue *pq) {
	void *retValue = NULL;
	
	if(pq->capacity == 0) {
		printf("The priority queue is empty\n");
		return NULL;
	}
	retValue = pq->dataList[0];
	/* move the last to the top */
	pq->dataList[0] = pq->dataList[pq->capacity - 1];
	//free (pq->dataList[pq->capacity - 1]);
	pq->priority[0] = pq->priority[pq->capacity - 1];
	//free (pq->priority[pq->capacity - 1]);
	/* reallocate */
	pq->capacity--;
	pq->dataList = realloc(pq->dataList, sizeof(void *) * pq->capacity);
	pq->priority = realloc(pq->priority, sizeof(int) * pq->capacity);
		
	downHeap(pq);
	
	return retValue;
}

int empty(struct priorityQueue *pq) {
	return pq->capacity == 0;
}

void upHeap(struct priorityQueue *pq) {
	int i, j;
	void *tempData;
	int tempPriority;
	
	if (pq->capacity == 1) {
		return;
	}
	tempData = pq->dataList[pq->capacity - 1];
	tempPriority = pq->priority[pq->capacity - 1];
	i = pq->capacity - 1;
	j = ((i + 1) / 2) - 1;
	while (tempPriority > (pq->priority)[j]) {
		pq->priority[i] = pq->priority[j];
		pq->dataList[i] = pq->dataList[j];
		i = j;
		j = ((i + 1) / 2) - 1;
		if (j < 0) {
			break;
		}
	}
	pq->priority[i] = tempPriority;
	pq->dataList[i] = tempData;
}

void downHeap(struct priorityQueue *pq) {
	int i, j;
	void *tempData;
	int tempPriority;
	if (pq->capacity == 1 || pq->capacity == 0) {
		return;
	}
	i = 0;
	tempData = pq->dataList[0];
	tempPriority = pq->priority[0];
	while((i + 1) <= pq->capacity / 2) {
		j = (i + 1) * 2 - 1;
		if ( j < pq->capacity / 2 && pq->priority[j] < pq->priority[j + 1]) {
			j++;
		}
		if (tempPriority >= pq->priority[j]) {
			break;
		}
		pq->priority[i] = pq->priority[j];
		pq->dataList[i] = pq->dataList[j];
		i = j;
	}
	pq->priority[i] = tempPriority;
	pq->dataList[i] = tempData;
}

