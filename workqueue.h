#ifndef WORKQUEUE_H_
#define WORKQUEUE_H_

typedef struct node{
    struct node *next;
    int *csocket;
} Node;


void enqueue(int *csocket);
int *dequeue();
#endif