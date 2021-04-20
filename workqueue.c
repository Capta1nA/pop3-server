#include "workqueue.h"
#include "stdlib.h"

Node *head = NULL;
Node *tail = NULL;

void enqueue(int *csocket){
    
    Node *nnode = malloc(sizeof(Node));

    nnode->csocket = csocket;
    nnode->next = NULL;

    if(tail == NULL){
        head = nnode;
    }
    else{
        tail->next = nnode;
    }
    tail = nnode;
}

int *dequeue(){
    if(head == NULL){
        return NULL;
    }
    else{
        int *res = head->csocket;
        Node *temp = head;
        head = head->next;

        if(head == NULL){
            tail = NULL;
        }

        free(temp);

        return res;
    }
}