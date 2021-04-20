#include "threadpool.h"
#include "workqueue.h"
#include <string.h>
#include "handler.h"

pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int activeThreads = 0;


void *thread_func(void *args){

    

    while(1){
        int *pclient;
        pthread_mutex_lock(&mutex);
        if((pclient = dequeue()) == NULL){
            pthread_cond_wait(&cond_var, &mutex);

            pclient = dequeue();
            activeThreads++;
            
        }
        pthread_mutex_unlock(&mutex);

        if(pclient != NULL){
            handleConnection(pclient);

        }
    }

}

Threadpool *create_threadpool(int nthreads){
    Threadpool *tpool = NULL;
    int i,res;

    tpool = (Threadpool *)malloc(sizeof(Threadpool));

    if(tpool == NULL){
        perror("malloc");
        return NULL;
    }

    tpool->nthreads = nthreads;
    //tpool->qsize = qsize;

    tpool->threads = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);
    //tpool->queue = (THREAD_WORK *)malloc(sizeof(THREAD_WORK) * qsize);

    if(tpool->threads == NULL){
        perror("malloc");
        return NULL;
    }
    // if(tpool->threads == NULL || tpool->queue == NULL){
    //     perror("malloc");
    //     return NULL;
    // }

    for(i=0;i<nthreads;i++){
        res = pthread_create(&(tpool->threads[i]), NULL, thread_func, NULL);
    }

    return tpool;
}