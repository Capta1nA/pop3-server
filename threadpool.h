#ifndef THREADPOOL_H_
#define THREADPOOL_H_
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern pthread_mutex_t mutex;
extern pthread_cond_t cond_var;

// typedef struct threadpool_work_t{
//     void (*func)(void *);
//     void *args;
// }THREAD_WORK;

typedef struct threadpool_t{
    pthread_t *threads;
    int nthreads;
}Threadpool;



void *thread_func(void *args);
Threadpool *create_threadpool(int nthreads, int qsize);

#endif